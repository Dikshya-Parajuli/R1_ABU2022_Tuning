/*
 * motorgeared.cpp
 *
 *  Created on: May 6, 2022
 *      Author: fady
 */

#include <motorgeared.h>
#include <stdio.h>
#include<pid.h>



motor_geared::motor_geared() {
	
}

motor_geared::motor_geared(Motor_config *m_config, Encoder_config *e_config, float gr) : motor_encoded(m_config, e_config) {
	this->gearRatio = gr;
}

int motor_geared::getAngleGeared() {
	return this->getEncoderPulses() * 360 * 2 / (this->m_encoderconfig->ppr * this->gearRatio);
}

int motor_geared::getGearedPulseNeeded(float angle) {
	return this->m_encoderconfig->ppr * this->gearRatio * angle / (360 * 2);
}

void motor_geared::runGeared() {
	int pulsesNeeded = getGearedPulseNeeded(this->m_encoderconfig->angle);
	int pulsesFound = getEncoderPulses();
	// setContinousPIDConstrain(1, 0, 0, 0, 500);
	// int output = c_pid.Compute(pulsesNeeded, pulsesFound);
	// setPulseFinal(output);
	// double output=c_pid.Compute(pulsesNeeded,pulsesFound);
	// c_p.SetTunings(1,0,0,0);
	printf("Angle = %d, PulsesNeeded = %d, PulsesFound = %d\n", (int)this->m_encoderconfig->angle, pulsesNeeded, (int)pulsesFound);

	
	if (pulsesFound == pulsesNeeded ) {
		this->setSpeedPercentage(0);
	}
	else if (pulsesFound >= pulsesNeeded * 1.1) {
		this->setSpeedDir(50, ANTICLOCKWISE);
	} else if (pulsesFound >= pulsesNeeded * 1.05) {
		this->setSpeedDir(30, ANTICLOCKWISE);
	} else if (pulsesFound >= pulsesNeeded * 1.03) {
		this->setSpeedDir(20, ANTICLOCKWISE);
	} else if (pulsesFound >= pulsesNeeded * 1.01) {
		this->setSpeedDir(10, ANTICLOCKWISE);
	} else if (pulsesFound >= pulsesNeeded * 1.005) {
		this->setSpeedDir(5, ANTICLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.9) {
		this->setSpeedDir(50, CLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.95) {
		this->setSpeedDir(30, CLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.97) {
		this->setSpeedDir(20, CLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.99) {
		this->setSpeedDir(10, CLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.99) {
		this->setSpeedDir(5, CLOCKWISE);
	} else {
		this->setSpeedPercentage(0);
	}
	this->run();
	angle = getAngle();
}

void motor_geared::setPulseFinal(int pulse) {
	int pulsesNeeded = pulse;
	int pulsesFound = getEncoderPulses();
	if (pulsesFound == pulsesNeeded ) {
		this->setSpeedPercentage(0);
	}
	else if (pulsesFound >= pulsesNeeded * 1.1) {
		this->setSpeedDir(50, ANTICLOCKWISE);
	} else if (pulsesFound >= pulsesNeeded * 1.05) {
		this->setSpeedDir(30, ANTICLOCKWISE);
	} else if (pulsesFound >= pulsesNeeded * 1.03) {
		this->setSpeedDir(20, ANTICLOCKWISE);
	} else if (pulsesFound >= pulsesNeeded * 1.01) {
		this->setSpeedDir(10, ANTICLOCKWISE);
	} else if (pulsesFound >= pulsesNeeded * 1.005) {
		this->setSpeedDir(5, ANTICLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.9) {
		this->setSpeedDir(50, CLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.95) {
		this->setSpeedDir(30, CLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.97) {
		this->setSpeedDir(20, CLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.99) {
		this->setSpeedDir(10, CLOCKWISE);
	} else if (pulsesFound <= pulsesNeeded * 0.99) {
		this->setSpeedDir(5, CLOCKWISE);
	} else {
		this->setSpeedPercentage(0);
	}
}

void motor_geared::motorGearedInit(Motor_config *m_config, Encoder_config *e_config, float gr) {
	this->motorEncodedInit(m_config, e_config);
	this->gearRatio = gr;
}

motor_geared::~motor_geared() {
	// TODO Auto-generated destructor stub
}

