/*
 * robooperation.h
 *
 *  Created on: May 7, 2022
 *      Author: fady
 */

#ifndef INC_ROBOOPERATION_H_
#define INC_ROBOOPERATION_H_

#include "roboinitall.h"
#include "joystick.h"

typedef struct
{
    JoyStick_Handle gJoyStick;
    JoyStick joystick;
} JoystickState;

void initJoyStick(JoystickState*);
void roboPlay(RobotState*, JoystickState*);
void runAllMotors(RobotState*);
void runRollers(RobotState*, int);

#endif /* INC_ROBOOPERATION_H_ */
