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

//TODO DONE Complete FT_UAH_PHOTSAT_SERV_129_0010

#define FT_UAH_PHOTSAT_SERV_129_0010

#ifdef FT_UAH_PHOTSAT_SERV_129_0010

#define FT_UAH_PHOTSAT_SERV_129_0010_step0  (OBT_AFTER_POWER_ON + 5)


// STEP0 - Lanzamos una solicitud de observacion
EmuGSS_TCProgram129_1 prog_FT_UAH_PHOTSAT_SERV_129_0010_step0(FT_UAH_PHOTSAT_SERV_129_0010_step0,
    "FT_UAH_PHOTSAT_SERV_129_0010_step0, Solicita la Observacion mediante la toma de dos imagenes con yaw=15*60 y pitch 15*60", 900, 900, 2);


#endif


//TODO DONE Complete FT_UAH_PHOTSAT_SERV_129_FDIR_0020

#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020

#ifdef FT_UAH_PHOTSAT_SERV_129_FDIR_0020

#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step0  (OBT_AFTER_POWER_ON + 5)
#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step1  (OBT_AFTER_POWER_ON + 8)
#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step2  (OBT_AFTER_POWER_ON + 11)
#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step3  (OBT_AFTER_POWER_ON + 14)
#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step4  (OBT_AFTER_POWER_ON + 17)
#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step5  (OBT_AFTER_POWER_ON + 20)
#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step6  (OBT_AFTER_POWER_ON + 23)
#define FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step7  (OBT_AFTER_POWER_ON + 26)

// STEP0 - Definimos el monitor PID 13
EmuGSS_TCProgram12_5_Value_UINT8 prog_FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step0(FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step0,
    "FT_UAH_PHOTSAT_SERV_129_FDIR_0020 step 0, Configurar PMODID 1 para PID 13",
    1, 13, 2, 1, 0xFF, 0, 0X4003);

// STEP1 - Definimos el monitor PID 14
EmuGSS_TCProgram12_5_Value_UINT8 prog_FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step1(FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step1,
    "FT_UAH_PHOTSAT_SERV_129_FDIR_0020 step 1, Configurar PMODID 2 para PID 14",
    2, 14, 2, 1, 0xFF, 0, 0X4003);

// STEP2 - Habilitamos el monitor del PID 13
EmuGSS_TCProgram12_1 prog_FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step2(FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step2,
    "FT_UAH_PHOTSAT_SERV_129_FDIR_0020 step 2, Habilitamps PMODID 1 para PID 13",1);

// STEP3 - Habilitamos el monitor del PID 14
EmuGSS_TCProgram12_1 prog_FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step3(FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step3,
    "FT_UAH_PHOTSAT_SERV_129_FDIR_0020 step 3, Habilitamps PMODID 2 para PID 14",2);

// STEP4 - Configura una acción de reinicio
EmuGSS_TCProgram19_1_Action_129_3 prog_FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step4(FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step4,
    "FT_UAH_PHOTSAT_SERV_129_FDIR_0020 step 4, Se detecta el EvID",0X4003);

// STEP5 - Habilitamos dicha acción
EmuGSS_TCProgram19_4 prog_FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step5(FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step5,
    "FT_UAH_PHOTSAT_SERV_129_FDIR_0020 step 5, Habilitamos dicha acción",0X4003);

// STEP6 - Determina el valor de Kp, Ki y Kd
EmuGSS_TCProgram129_2 prog_FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step6(FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step6,
    "FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step6, Determina el valor de Kp=Ki=Kd=0,5", 0.5, 0.5, 0.5);

// STEP7 - Solicitud nueva observacion
EmuGSS_TCProgram129_1 prog_FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step7(FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step7,
    "FT_UAH_PHOTSAT_SERV_129_FDIR_0020_step7, Solicita la Observacion mediante la toma de dos imagenes con yaw=30*60 y pitch 30*60", 1800, 1800, 2);



#endif
