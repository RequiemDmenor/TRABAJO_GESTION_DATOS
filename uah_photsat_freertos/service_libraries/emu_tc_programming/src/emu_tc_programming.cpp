/*
 * emu_tc_programming.cpp
 *
 *  Created on: Jan 13, 2017
 *
 *  Created on: Oct 26, 2024
 *      Author: Oscar Rodriguez Polo
 */

/****************************************************************************
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2
 *   of the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,USA.
 *
 *
 ****************************************************************************/



#include <public/emu_hw_timecode_drv_v1.h>
#include <public/emu_sc_channel_drv_v1.h>
#include <public/emu_gss_v1.h>

//TODO Complete FT_UAH_PHOTSAT_SERV_129_0010
//
// FT_UAH_PHO TSAT_SERV_129_0010:
//   Verifica que al enviar TC[129,1] con valores válidos (Yaw, Pitch y numImágenes),
//   la misión genera exactamente tantas telemetrías TM[129,4] como imágenes se pidieron.
//

void FT_UAH_PhotSat_SERV_129_0010(void)
{
    // ------------------------------------------------------------
    // 1) Definir valores de prueba para ThetaYaw, ThetaPitch y numImages
    // ------------------------------------------------------------
    int16_t  ThetaYaw   =  150;    // Ejemplo: 150' de arco
    int16_t  ThetaPitch = -120;    // Ejemplo: -120' de arco
    uint8_t  numImages  =   4;     // Pedimos 4 imágenes

    // ------------------------------------------------------------
    // 2) Construir el objeto TC[129,1] con esos parámetros
    // ------------------------------------------------------------
    uint32_t currentTime2YK = EmuHW_GetTimeCode();
    EmuGSS_TCProgram129_1 tc1291(
        currentTime2YK,
        "FT_129_0010",   // Descripción breve
        ThetaYaw,
        ThetaPitch,
        numImages
    );

    // ------------------------------------------------------------
    // 3) Enviar el telemando TC[129,1]
    // ------------------------------------------------------------
    if (!GSS_SendTC(&tc1291)) {
        // Si falla el envío, salimos inmediatamente
        return;
    }

    // ------------------------------------------------------------
    // 4) Esperar exactamente ‘numImages’ telemetrías TM[129,4]
    // ------------------------------------------------------------
    uint8_t       receivedCount = 0;
    EmuGSS_TMProgram129_4 tm1294;
    const uint32_t TIMEOUT_MS   = 2000;  // 2 segundos por cada TM[129,4]

    while (receivedCount < numImages) {
        // Bloqueante: espera una TM servicio=129, subservicio=4
        if (!GSS_WaitForTM(129, 4, &tm1294, TIMEOUT_MS)) {
            // Timeout o error antes de recibir la telemetría esperada
            break;
        }
        // Si llegó la TM, incrementamos el contador y continuamos
        receivedCount++;
    }

    // ------------------------------------------------------------
    // 5) Si recibimos exactamente ‘numImages’, la prueba pasa.
    //    En otro caso, la prueba falla (aquí simplemente salimos).
    // ------------------------------------------------------------
    if (receivedCount == numImages) {
        // OK: llegaron tantas TM[129,4] como imágenes pedimos
    }
    else {
        // FAIL: llegaron 'receivedCount' TM[129,4], se esperaban 'numImages'
    }
}



//TODO Complete FT_UAH_PHOTSAT_SERV_129_FDIR_0020
void FT_UAH_PhotSat_SERV_129_FDIR_0020(void)
{
    // ------------------------------------------------------------
    // 1) Leer telemetría TM[19,1] inicial para comprobar PID == 0
    // ------------------------------------------------------------
    EmuGSS_TMProgram19_1 tm19_initial;
    const uint32_t CTRL_TM_TIMEOUT_MS = 2000;  // 2 segundos

    if (!GSS_WaitForTM(19, 1, &tm19_initial, CTRL_TM_TIMEOUT_MS)) {
        // No llegó TM[19,1] de control inicial: falla la prueba
        return;
    }
    if (tm19_initial.getThetaPitch_W_ControlPID() != 0 ||
        tm19_initial.getThetaYaw_W_ControlPID()   != 0) {
        // Los parámetros PID no están a 0 al inicio: falla la prueba
        return;
    }

    // ------------------------------------------------------------
    // 2) Enviar TC[129,2] con Kp=0.5, Ki=0.5, Kd=0.5 para forzar exceso
    // ------------------------------------------------------------
    uint32_t tnow = EmuHW_GetTimeCode();
    EmuGSS_TCProgram129_2 tc1292(
        tnow,
        "FT_129_FDIR_0020",  // Descripción breve
        0.5f,  // Kp
        0.5f,  // Ki
        0.5f   // Kd
    );
    if (!GSS_SendTC(&tc1292)) {
        // No pudo enviarse TC[129,2]: falla la prueba
        return;
    }

    // ------------------------------------------------------------
    // 3) Esperar que salte el evento 0x4003 dentro de un timeout
    // ------------------------------------------------------------
    EmuGSS_Event event4003;
    const uint32_t EVENT_TIMEOUT_MS = 5000;  // 5 segundos

    if (!GSS_WaitForEvent(0x4003, &event4003, EVENT_TIMEOUT_MS)) {
        // No se recibió el evento 0x4003: falla la prueba
        return;
    }

    // ------------------------------------------------------------
    // 4) Verificar que la GSS emite automáticamente TC[129,3] (reset)
    // ------------------------------------------------------------
    const uint32_t TC_RESET_TIMEOUT_MS = 3000;  // 3 segundos
    if (!GSS_WaitForSentTC(129, 3, TC_RESET_TIMEOUT_MS)) {
        // No se envió TC[129,3] tras recibir el evento: falla la prueba
        return;
    }

    // ------------------------------------------------------------
    // 5) Leer TM[19,1] de control otra vez y comprobar que PID vuelve a 0
    // ------------------------------------------------------------
    EmuGSS_TMProgram19_1 tm19_after;
    if (!GSS_WaitForTM(19, 1, &tm19_after, CTRL_TM_TIMEOUT_MS)) {
        // No llegó TM[19,1] post-reset: falla la prueba
        return;
    }
    if (tm19_after.getThetaPitch_W_ControlPID() == 0 &&
        tm19_after.getThetaYaw_W_ControlPID()   == 0) {
        // OK: PID restaurado a 0 tras el reset
    }
    else {
        // FAIL: PID no volvió a 0 después del reset
    }
}

