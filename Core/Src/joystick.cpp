#include "joystick.h"
#include "array.h"
#include "tim.h"

#include <math.h>
#include <stdio.h>

#define JOYSTICK_START_BYTE (START_BYTE)
#define NUM_JOYSTICK_BYTES (8)


// JoyStick_Handle gJoyStick;
struct JoyStick_Data gJoy;
static JoyStick_Data gNull_JData;


// static uint8_t sending_byte[2];
static CRC_Hash gJoyStick_CRC(7);

static uint8_t gRx2Data;
static uint8_t gJoy_Data_Arr[NUM_JOYSTICK_BYTES];
static uint16_t gRx2_Data_num = 0;
static bool gStart_Byte_Rx2 = false;
static void fill_JoyData(JoyStick_Data *joy, uint8_t data[NUM_JOYSTICK_BYTES]);

bool isButtonPressed(int button, int data);

// Temporary (For testing Purposes)
static int angle = 0;
int prevTime = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
        __HAL_UART_FLUSH_DRREGISTER(huart);
        if (!gStart_Byte_Rx2) {
                if (gRx2Data == JOYSTICK_START_BYTE) {
                        gStart_Byte_Rx2 = true;
                }
        } else {
                if (gRx2_Data_num < NUM_JOYSTICK_BYTES) {      
                        gJoy_Data_Arr[gRx2_Data_num] = gRx2Data;
                        ++gRx2_Data_num;
                } else {
                        uint8_t rem = gRx2Data;
                        gStart_Byte_Rx2 = false;
                        gRx2_Data_num = 0;
                        uint8_t hash = gJoyStick_CRC.get_Hash(gJoy_Data_Arr, NUM_JOYSTICK_BYTES);
                        // printf("Hash = %d\n", hash);
                        if (hash == rem) {
                                fill_JoyData(&gJoy, gJoy_Data_Arr);
                                //gJoyStick.data.insert(gJoy);
                                // printf("#GRN#No Error!!\n");
                        } else {
                                printf("#RED#Error\n");
                        } 
                }
        }
}

void JoyStick::init() {
        gNull_JData.button1 = 0;
        gNull_JData.button2 = 0;
        gNull_JData.lt = 0;
        gNull_JData.rt = 0;
        gNull_JData.l_hatx = 0;
        gNull_JData.l_haty = 0;
        gNull_JData.r_hatx = 0;
        gNull_JData.r_haty = 0;
}

void fill_JoyData(JoyStick_Data *joy, uint8_t data[NUM_JOYSTICK_BYTES])
{
        joy->button1 = data[0];
        joy->button2 = data[1];
        joy->lt = data[2];
        joy->rt = data[3];
        joy->l_hatx = data[4];
        joy->l_haty = data[5];
        joy->r_hatx = data[6];
        joy->r_haty = data[7];
}



void JoyStick:: parse_JoyData(RobotState* robot_state) {
         HAL_UART_Receive_DMA(hjoy_->huart, &gRx2Data, 1);

        robot_state->pitchMotor.setAngle(15);
        // int now = HAL_GetTick();
        // if (now - prevTime >= 10) {
        // // printf("lt: %d  rt: %d  r_hatx: %d  r_haty: %d\n", gJoy.lt, gJoy.rt, gJoy.r_hatx, gJoy.r_haty);

        // if (isButtonPressed(B_X, gJoy.button1)) {
        // robot_state->pitchMotor.setAngle(10);
        // } else if (isButtonPressed(B_Y, gJoy.button1)) {
        //          robot_state->pitchMotor.setAngle(20);
        // } else if (isButtonPressed(B_A, gJoy.button1)) {
        //          robot_state->pitchMotor.setAngle(30);
        // } else if (isButtonPressed(B_Y, gJoy.button1)) {
        //          robot_state->pitchMotor.setAngle(40);
        // } else if (isButtonPressed(B_X, gJoy.button1)) {
        //          robot_state->pitchMotor.setAngle(50);
        // }

        // // if (gJoy.lt > 0) {
        // //         robot_state->yawMotor.setSpeedDir(gJoy.lt * 30 / 255, CLOCKWISE);
        // // } else if (gJoy.rt > 0) {
        // //         robot_state->yawMotor.setSpeedDir(gJoy.rt * 30 / 255, ANTICLOCKWISE);
        // // } else {
        // //         robot_state->yawMotor.setSpeedPercentage(0);
        // // }

        // else if (isButtonPressed(B_START, gJoy.button2)) {
        //         HAL_GPIO_WritePin(PNEU_1_GPIO_Port, PNEU_1_Pin, GPIO_PIN_SET);
        // } else if (isButtonPressed(B_BACK, gJoy.button2)) {
        //         HAL_GPIO_WritePin(PNEU_1_GPIO_Port, PNEU_1_Pin, GPIO_PIN_RESET);
        // }
        // else if (isButtonPressed(B_XBOX, gJoy.button2)) {
        //         robot_state->pitchMotor.setAngle(0);
        //         robot_state->pitchMotor.setSpeedDir(1, ANTICLOCKWISE);
        //         robot_state->pitchMotor.run();
        // }
        // else if (isButtonPressed(B_RB, gJoy.button1)) {
        //         HAL_GPIO_WritePin(PNEU_3_GPIO_Port, PNEU_3_Pin, GPIO_PIN_SET);
        // } else {
        //         HAL_GPIO_WritePin(PNEU_3_GPIO_Port, PNEU_3_Pin, GPIO_PIN_RESET);
        // }

        // int nowTime = HAL_GetTick();
        //         if (nowTime - prevTime <= 50){ 
        //                 angle+=2;
        //                 robot_state->yawMotor.setAngle(angle);
        //                 prevTime = HAL_GetTick();
        //         }
        printf("agle = %d\n", angle);

        // if (angle<0) angle = 0;
        // if (angle>160) angle = 160;

        // if (gJoy.lt >= 125 && angle >= 0 && angle <= 160) {
        //         // int nowTime = HAL_GetTick();
        //         // if (nowTime - prevTime <= 50){ 
        //                 angle-=1;
        //                 // if (angle < 0) angle = 0;
        //                 robot_state->yawMotor.setAngle(angle);
        //         //         prevTime = HAL_GetTick();
        //         // }
        // } else if (gJoy.rt >= 125 && angle >= 0 && angle <= 160) {
        //         // int nowTime = HAL_GetTick();
        //         // if (nowTime - prevTime <= 50){ 
        //                 angle+=1;
        //                 robot_state->yawMotor.setAngle(angle);
        //         //         prevTime = HAL_GetTick();
        //         // }
        // } else {
        //         robot_state->yawMotor.setAngle(angle);
        // }     
        // if (isButtonPressed(B_X, gJoy.button1)){
        // robot_state->yawMotor.setAngle(90);
        // // angle += 5;
        // // if (angle >= 20) angle = 20;
        // }
        // else if (isButtonPressed(B_Y, gJoy.button1)) {
        // // angle -= 5;
        // // if (angle <= 1) angle = 1;
        // // }
        // robot_state->yawMotor.setAngle(180);
        // } else if (isButtonPressed(B_A, gJoy.button1))
        //  robot_state->yawMotor.setAngle(270);
        // robot_state->yawMotor.setAngle(angle);
        // prevTime = HAL_GetTick();
        // }
        
}
 
bool isButtonPressed(int button, int data) {
        return ( data & _BV(button) ) != 0x00;
}