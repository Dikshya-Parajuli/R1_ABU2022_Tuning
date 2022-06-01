/*
 * robooperation.cpp
 *
 *  Created on: May 7, 2022
 *      Author: fady
 */

#include <robooperation.h>

// int prev = 0;
// int currentSpeed = 0;

void roboPlay(RobotState* robot_state, JoystickState* joystick_state) {
	initAllMotors(robot_state);
	initTim(robot_state);
	initJoyStick(joystick_state);
	
	while(1) {
		// int now = HAL_GetTick();
		// if (now - prev >= 10) {
		runRollers(robot_state, 15  );
		joystick_state->joystick.parse_JoyData(robot_state);
		runAllMotors(robot_state);
		// prev = HAL_GetTick();
		// }
	}
}

void runAllMotors(RobotState* robot_state) {
	robot_state->roller[0].run();
	robot_state->roller[1].run();
	robot_state->pitchMotor.runGeared();
	robot_state->yawMotor.run();
}

void runRollers(RobotState* robot_state, int speed) {
	// int now = HAL_GetTick();
    // if (now - prev >= 5) {
    // 	if (currentSpeed < speed) currentSpeed += 500;
    // 	HAL_GPIO_WritePin(ROLLER1_DIR_GPIO_Port, ROLLER1_DIR_Pin, GPIO_PIN_RESET);
    // 	HAL_GPIO_WritePin(ROLLER2_DIR_GPIO_Port, ROLLER2_DIR_Pin, GPIO_PIN_SET);
    // 	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, currentSignal);
    // 	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, currentSignal);
    // 	prev = now;
    // }
	robot_state->roller[0].setSpeedDir(speed, ANTICLOCKWISE);
	robot_state->roller[1].setSpeedDir(speed, CLOCKWISE);
}

void initJoyStick(JoystickState* joystick_state) {
	joystick_state->gJoyStick.huart = &huart2;
	joystick_state->joystick.set_config(&(joystick_state->gJoyStick));
	joystick_state->joystick.init();
}
