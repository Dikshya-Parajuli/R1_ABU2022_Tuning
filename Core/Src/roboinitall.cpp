/*
 * roboinitall.cpp
 *
 *  Created on: May 6, 2022
 *      Author: fady
 */

#include <roboinitall.h>

void initAllMotors(RobotState* robot_state) {
	initRollers(robot_state);
	initPitchYaw(robot_state);
}

void initRollers(RobotState* robot_state) {
	robot_state->rollerConfig[0].dirPort = GPIOE;
	robot_state->rollerConfig[0].dirPin = GPIO_PIN_8;
	robot_state->rollerConfig[0].pwmTim = &htim1;
	robot_state->rollerConfig[0].pwmTimChannel = TIM_CHANNEL_1;
	robot_state->rollerConfig[0].pwmFullSignal = 65535;

	robot_state->roller[0].motorinit(&(robot_state->rollerConfig[0]));

	robot_state->rollerConfig[1].dirPort = GPIOE;
	robot_state->rollerConfig[1].dirPin = GPIO_PIN_10;
	robot_state->rollerConfig[1].pwmTim = &htim1;
	robot_state->rollerConfig[1].pwmTimChannel = TIM_CHANNEL_2;
	robot_state->rollerConfig[1].pwmFullSignal = 65535;

	robot_state->roller[1].motorinit(&(robot_state->rollerConfig[1]));
}

void initPitchYaw(RobotState* robot_state) {
	robot_state->pitchConfig.dirPort = GPIOE;
	robot_state->pitchConfig.dirPin = GPIO_PIN_12;
	robot_state->pitchConfig.pwmTim = &htim1;
	robot_state->pitchConfig.pwmTimChannel = TIM_CHANNEL_3;
	robot_state->pitchConfig.pwmFullSignal = 65535;

	robot_state->pitchEncoderConfig.ch1Port = GPIOA;
	robot_state->pitchEncoderConfig.ch1Pin = GPIO_PIN_15;
	robot_state->pitchEncoderConfig.ch2Port = GPIOA;
	robot_state->pitchEncoderConfig.ch2Pin = GPIO_PIN_1;
	robot_state->pitchEncoderConfig.encTimer = &htim2;
	robot_state->pitchEncoderConfig.ppr = 1000;

	float pitchGearRatio = 3.5;

	robot_state->pitchMotor.motorGearedInit(&(robot_state->pitchConfig), &(robot_state->pitchEncoderConfig), pitchGearRatio);



	robot_state->yawConfig.dirPort = GPIOE;
	robot_state->yawConfig.dirPin = GPIO_PIN_15;
	robot_state->yawConfig.pwmTim = &htim1;
	robot_state->yawConfig.pwmTimChannel = TIM_CHANNEL_4;
	robot_state->yawConfig.pwmFullSignal = 65535;
	
	robot_state->yawEncoderConfig.ch1Port = GPIOC;
	robot_state->yawEncoderConfig.ch1Pin = GPIO_PIN_6;
	robot_state->yawEncoderConfig.ch2Port = GPIOB;
	robot_state->yawEncoderConfig.ch2Pin = GPIO_PIN_5;
	robot_state->yawEncoderConfig.encTimer = &htim3;
	robot_state->yawEncoderConfig.ppr = 1000;

	float yawGearRatio = 250/24;

	robot_state->yawMotor.motorGearedInit(&(robot_state->yawConfig), &(robot_state->yawEncoderConfig), yawGearRatio);
}

void initTim(RobotState* robot_state) {
	// Start PWM signals for speed control(Rollers)
  	robot_state->roller[0].initTim();
  	robot_state->roller[1].initTim();

  	// Start Encoder Mode For Pitch Motor
  	robot_state->pitchMotor.initEncoderTim();

  	// Start Encoder Mode For Yaw Motor
	robot_state->yawMotor.initEncoderTim();

  	// Start PWM signal for Pitch Motor
  	robot_state->pitchMotor.initTim();
	
	// Start PWM Signal for Yaw Motor
	robot_state->yawMotor.initTim();
}

