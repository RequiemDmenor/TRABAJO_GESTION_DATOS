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

//TODO DONE complete EmuGSS_TCProgram129_1 constructor (A PARTIR DEL emu_gss_pus DEL SERVICIO 20)
EmuGSS_TCProgram129_1::EmuGSS_TCProgram129_1(uint32_t uniTime2YK,
                                             const char * brief,
                                             int16_t ThetaYaw,
                                             int16_t ThetaPitch,
                                             uint8_t num_of_samples)
                                             : EmuGSS_TCProgram(uniTime2YK, 129, 1, TC_129_1_APPDATA_LENGTH, brief){
    // Asignamos los valores recibidos a los atributos tal y como está declarado en el .h
    mThetaYaw     = ThetaYaw;
    mThetaPitch   = ThetaPitch;
    mnum_of_samples = num_of_samples;

    // Marcamos este TCProgram como “nuevo”
    NewProgram(this);
}

//TODO DONE complete EmuGSS_TCProgram129_1::BuildTCAppData code (A PARTIR DEL emu_gss_pus DEL SERVICIO 20)
void EmuGSS_TCProgram129_1::BuildTCAppData(tc_mem_descriptor_t &tc_descriptor)
{
	SetNextUInt8(1);
	SetNextInt16(mThetaYaw);
	SetNextInt16(mThetaPitch);
	SetNextUInt8(mnum_of_samples);

}



//TODO DONE complete EmuGSS_TCProgram129_2 constructor (A PARTIR DEL emu_gss_pus DEL SERVICIO 20)
EmuGSS_TCProgram129_2::EmuGSS_TCProgram129_2(uint32_t uniTime2YK,
                                             const char * brief,
                                             float Kp,
                                             float Ki,
                                             float Kd)
                                             : EmuGSS_TCProgram(uniTime2YK, 129, 2, TC_129_2_APPDATA_LENGTH, brief){
    // Guardamos los tres parámetros PID en los atributos
    mKp = Kp;
    mKpi = Ki;
    mKd = Kd;

    // Marcamos este TCProgram como “nuevo”
    NewProgram(this);
}


//TODO DONE complete EmuGSS_TCProgram129_2::BuildTCAppData code (A PARTIR DEL emu_gss_pus DEL SERVICIO 20)
void EmuGSS_TCProgram129_2::BuildTCAppData(tc_mem_descriptor_t &tc_descriptor)
{
	SetNextUInt8(1);
	SetNextFloat(mKp);
	SetNextFloat(mKpi);
	SetNextFloat(mKd);
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


}


