/*
 * emu_sc_pus_service3.cpp
 *
 *  Created on: Jan 13, 2017
 *      Author: user
 */

#include <stdio.h>


#include "public/emu_gss_v1.h"

#define TC_129_1_APPDATA_LENGTH 5
#define TC_129_2_APPDATA_LENGTH 12
#define TC_129_3_APPDATA_LENGTH 0

//TODO complete EmuGSS_TCProgram129_1 constructor
EmuGSS_TCProgram129_1::EmuGSS_TCProgram129_1(uint32_t uniTime2YK,
                                             const char * brief,
                                             int16_t ThetaYaw,
                                             int16_t ThetaPitch,
                                             uint8_t num_of_samples)
  : EmuGSS_TCProgram(uniTime2YK, 129, 1, TC_129_1_APPDATA_LENGTH, brief)
{
    // Asignamos los valores recibidos a los atributos privados tal y como está declarado en el .h
    mThetaYaw     = ThetaYaw;
    mThetaPitch   = ThetaPitch;
    mNumOfSamples = num_of_samples;

    // Marcamos este TCProgram como “nuevo”
    NewProgram(this);
}

//TODO complete EmuGSS_TCProgram129_1::BuildTCAppData code
void EmuGSS_TCProgram129_1::BuildTCAppData(tc_mem_descriptor_t &tc_descriptor)
{
	// 1) Reservamos exactamente 5 bytes (2 para mThetaYaw, 2 para mThetaPitch, 1 para mNumOfSamples)
	    uint8_t *appbuf = new uint8_t[TC_129_1_APPDATA_LENGTH];

	    // 2) Empaquetamos mThetaYaw (int16_t) en big‐endian en los primeros 2 bytes:
	    //    Al desplazar 8 bits y enmascarar, obtenemos MSB y LSB por separado.
	    appbuf[0] = (uint8_t)((mThetaYaw >> 8) & 0xFF);
	    appbuf[1] = (uint8_t)( mThetaYaw       & 0xFF);

	    // 3) Empaquetamos mThetaPitch (int16_t) en big‐endian en los bytes 2..3:
	    appbuf[2] = (uint8_t)((mThetaPitch >> 8) & 0xFF);
	    appbuf[3] = (uint8_t)( mThetaPitch       & 0xFF);

	    // 4) El último byte (índice 4) es mNumOfSamples (uint8_t) sin conversión:
	    appbuf[4] = mNumOfSamples;

	    // 5) Asignamos el puntero y la longitud al descriptor
	    tc_descriptor.ucData    = appbuf;
	    tc_descriptor.uiDataLen = TC_129_1_APPDATA_LENGTH;

}



//TODO complete EmuGSS_TCProgram129_2 constructor
EmuGSS_TCProgram129_2::EmuGSS_TCProgram129_2(uint32_t uniTime2YK,
                                             const char * brief,
                                             float Kp,
                                             float Ki,
                                             float Kd)
  : EmuGSS_TCProgram(uniTime2YK, 129, 2, TC_129_2_APPDATA_LENGTH, brief)
{
    // Guardamos los tres parámetros PID en los atributos privados
    mKp = Kp;
    mKi = Ki;
    mKd = Kd;

    // Marcamos este TCProgram como “nuevo”
    NewProgram(this);
}


//TODO complete EmuGSS_TCProgram129_2::BuildTCAppData code
void EmuGSS_TCProgram129_2::BuildTCAppData(tc_mem_descriptor_t &tc_descriptor)
{
    // 1) Reservamos 12 bytes (3 floats × 4 bytes c/u)
    uint8_t *appbuf = new uint8_t[TC_129_2_APPDATA_LENGTH];

    // Para empacar cada float en big‐endian, usamos un union que nos permite
    // leer el bit‐pattern de cada float como uint32_t y luego extraer byte a byte.

    union { float f; uint32_t u; } conv;

    // --- Empaquetar mKp en bytes [0..3] ---
    conv.f = mKp;
    appbuf[0] = (uint8_t)((conv.u >> 24) & 0xFF);
    appbuf[1] = (uint8_t)((conv.u >> 16) & 0xFF);
    appbuf[2] = (uint8_t)((conv.u >>  8) & 0xFF);
    appbuf[3] = (uint8_t)( conv.u        & 0xFF);

    // --- Empaquetar mKi en bytes [4..7] ---
    conv.f = mKi;
    appbuf[4] = (uint8_t)((conv.u >> 24) & 0xFF);
    appbuf[5] = (uint8_t)((conv.u >> 16) & 0xFF);
    appbuf[6] = (uint8_t)((conv.u >>  8) & 0xFF);
    appbuf[7] = (uint8_t)( conv.u        & 0xFF);

    // --- Empaquetar mKd en bytes [8..11] ---
    conv.f = mKd;
    appbuf[8]  = (uint8_t)((conv.u >> 24) & 0xFF);
    appbuf[9]  = (uint8_t)((conv.u >> 16) & 0xFF);
    appbuf[10] = (uint8_t)((conv.u >>  8) & 0xFF);
    appbuf[11] = (uint8_t)( conv.u        & 0xFF);

    // 2) Asignamos puntero y longitud al descriptor
    tc_descriptor.ucData    = appbuf;
    tc_descriptor.uiDataLen = TC_129_2_APPDATA_LENGTH;
}



EmuGSS_TCProgram129_3::EmuGSS_TCProgram129_3(uint32_t uniTime2YK,
                         const char * brief)
                        :EmuGSS_TCProgram(uniTime2YK,129,3,
                        		TC_129_3_APPDATA_LENGTH,brief){

    NewProgram(this);
}

EmuGSS_TCProgram129_3::EmuGSS_TCProgram129_3()
                        :EmuGSS_TCProgram(0,129,3,TC_129_3_APPDATA_LENGTH,"NULL"){

	//No Program
    // NewProgram(this);
}


void EmuGSS_TCProgram129_3::BuildTCAppData(tc_mem_descriptor_t &tc_descriptor){
	 // No hay datos de aplicación, así que longitud = 0 y puntero = NULL
	 tc_descriptor.ucData    = NULL;
	 tc_descriptor.uiDataLen = 0;


}


