/*
 * wrapper.cpp
 *
 *  Created on: May 29, 2019
 *      Author: ryu
 */
#include "stm32f1xx_hal.h"
#include "wrapper.hpp"
#include "CanClass.hpp"
double X = 6.28;
double Y = 0.0;
double Z = 0.0;
CanClass can;
void main_cpp(void) {
	can.init();
    while(1){
    	can.send(X,0x205);
    	can.send(Y,0x206);
    	can.led_process();
		HAL_Delay(50);
    }

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	can.receive(Z, 0x4e2);
	can.receive(Y, 0x4e1);
	can.endit();//割り込み終了
}


