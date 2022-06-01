/*
 * motors.cpp
 *
 *  Created on: Apr 28, 2022
 *      Author: fady
 */

#include <motors.h>

motors::motors() {

}

motors::motors(Motor_config *m_config) {
	this->m_motorconfig = m_config;
}

void motors::motorinit(Motor_config* m_config) { 
	this->m_motorconfig = m_config;
}

void motors::setSpeedPercentage(int percentage){
	this->m_motorconfig->pwmSignal = this->m_motorconfig->pwmFullSignal * percentage / 100;
}

void motors::setDirection(Direction dir) {
	this->m_motorconfig->rotationDir = dir;    
}

void motors::setSpeedDir(int percentage, Direction dir) {
	this->setSpeedPercentage(percentage);
	this->setDirection(dir);
}

void motors::stop() {
	__HAL_TIM_SET_COMPARE(this->m_motorconfig->pwmTim, this->m_motorconfig->pwmTimChannel, 0);
}

void motors::run() {
	if (this->m_motorconfig->rotationDir == CLOCKWISE) {
		HAL_GPIO_WritePin(this->m_motorconfig->dirPort, this->m_motorconfig->dirPin, GPIO_PIN_SET);
	} else if (this->m_motorconfig->rotationDir == ANTICLOCKWISE) {
		HAL_GPIO_WritePin(this->m_motorconfig->dirPort, this->m_motorconfig->dirPin, GPIO_PIN_RESET);
	}
	__HAL_TIM_SET_COMPARE(this->m_motorconfig->pwmTim, this->m_motorconfig->pwmTimChannel, this->m_motorconfig->pwmSignal);
}

motors::~motors() {
	// TODO Auto-generated destructor stub
}

void motors::initTim() {
	HAL_TIM_PWM_Start(this->m_motorconfig->pwmTim, this->m_motorconfig->pwmTimChannel);
}

