/*
 * wrapper.cpp
 *
 *  Created on: May 29, 2019
 *      Author: ryu
 */
#include "stm32f1xx_hal.h"
#include "wrapper.hpp"
#include "CanClass.hpp"
uint8_t cmd;
bool shutdown_cmd = false;

CanClass can;
void main_cpp(void) {
	//この電磁弁駆動基板はマイコンの出力が反転されるため、最初に電磁弁への出力を初期化する
	GPIOA ->BSRR = GPIO_BSRR_BS8;

	HAL_Delay(500);

	GPIOB->BSRR = GPIO_BSRR_BS0;//green
	GPIOB->BSRR = GPIO_BSRR_BS1;//yellow
	GPIOB->BSRR = GPIO_BSRR_BS2;//red
	GPIOA->BSRR = GPIO_BSRR_BS11;//led_can

	HAL_Delay(100);

	GPIOB->BSRR = GPIO_BSRR_BR0;
	GPIOB->BSRR = GPIO_BSRR_BR1;
	GPIOB->BSRR = GPIO_BSRR_BR2;
	GPIOA->BSRR = GPIO_BSRR_BR11;

	can.init();

    while(1){

/*    	if((GPIOA->IDR & GPIO_IDR_IDR14) == 0)
  	  {
    		GPIOB->BSRR = GPIO_BSRR_BR1;
    		GPIOB->BSRR = GPIO_BSRR_BS2;
    		GPIOA ->BSRR = GPIO_BSRR_BS8;
  	  }
  	  else
  	  {
  	  }*/

    }

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	can.receive(cmd, 0x5e2);
	if(shutdown_cmd == true)
	{
	switch(cmd)
	{
	case 0x00://shutdown
		GPIOB->BSRR = GPIO_BSRR_BR1;
		GPIOB->BSRR = GPIO_BSRR_BS2;
		GPIOA ->BSRR = GPIO_BSRR_BS8;
		shutdown_cmd = false;
		break;
	case 0x01:
		GPIOA ->BSRR = GPIO_BSRR_BR8;
		break;
	default:
		GPIOA ->BSRR = GPIO_BSRR_BS8;
		break;
	}
	}

	if(cmd == 0x10)//enable
	{
		GPIOB->BSRR = GPIO_BSRR_BS1;
		GPIOB->BSRR = GPIO_BSRR_BR2;
		shutdown_cmd = true;
	}
	can.endit();//割り込み終了
}


