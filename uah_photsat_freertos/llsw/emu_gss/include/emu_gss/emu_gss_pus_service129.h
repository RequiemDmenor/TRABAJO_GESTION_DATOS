/*
 * emu_sc_pus_service5.h
 *
 *  Created on: Jan 16, 2024
 *      Author: user
 */

#ifndef EMU_SC_PUS_SERVICE129_H_
#define EMU_SC_PUS_SERVICE129_H_

class EmuGSS_TCProgram129_1:public EmuGSS_TCProgram{

	//TODO 	Add required attributes
private:
    int16_t  mThetaYaw;      // Angulo Yaw en min de arco
    int16_t  mThetaPitch;    // Angulo Pitch en min de arco
    uint8_t  mNumOfSamples;  // Nº de imágenes a tomar


public:

	EmuGSS_TCProgram129_1(uint32_t uniTime2YK,
                 const char * brief,int16_t ThetaYaw,int16_t ThetaPitch
				 , uint8_t num_of_samples);

	virtual void BuildTCAppData(tc_mem_descriptor_t &tc_descriptor);
};


class EmuGSS_TCProgram129_2:public EmuGSS_TCProgram{

	//TODO   Add required attributes
private:
    float mKp;  // Parámetro proporcional PID
    float mKi;  // Parámetro integral PID
    float mKd;  // Parámetro derivativo PID


public:

	EmuGSS_TCProgram129_2(uint32_t uniTime2YK,
                 const char * brief,float Kp,float Kpi, float Kd);

	virtual void BuildTCAppData(tc_mem_descriptor_t &tc_descriptor);
};


class EmuGSS_TCProgram129_3:public EmuGSS_TCProgram{

	friend class EmuGSS_TCProgram19_1_Action_129_3;

	virtual void BuildTCAppData(tc_mem_descriptor_t &tc_descriptor);

public:

	EmuGSS_TCProgram129_3(uint32_t uniTime2YK,
                 const char * brief);

	//Constructor for event action
	EmuGSS_TCProgram129_3();
};






#endif /* EMU_SC_PUS_SERVICE9_H_ */
