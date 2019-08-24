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

CanClass can;
void main_cpp(void) {
	GPIOB->BSRR = GPIO_BSRR_BS0;//green
	GPIOB->BSRR = GPIO_BSRR_BS1;//yellow
	GPIOB->BSRR = GPIO_BSRR_BS2;//red
	GPIOA->BSRR = GPIO_BSRR_BS11;//led_can

	HAL_Delay(500);

	GPIOB->BSRR = GPIO_BSRR_BR0;
	GPIOB->BSRR = GPIO_BSRR_BR1;
	GPIOB->BSRR = GPIO_BSRR_BR2;
	GPIOA->BSRR = GPIO_BSRR_BR11;

	can.init();

    while(1){
    	//can.send(X,0x205);
    	//can.send(Y,0x206);
    	//can.led_process();
		//HAL_Delay(50);
    }

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	can.receive(cmd, 0x5e2);

	int i = 0;
	while(i < 8)
	{
		if((cmd& 0x01) == 0x00)
		{
			switch(i)
			{
			case 0:
				GPIOA ->BSRR = GPIO_BSRR_BS8;
				break;
			case 1:
				GPIOA ->BSRR = GPIO_BSRR_BS9;
				break;
			case 2:
				GPIOA ->BSRR = GPIO_BSRR_BS10;
				break;
			case 3:
				GPIOA ->BSRR = GPIO_BSRR_BS12;
				break;
			case 4:
				GPIOA ->BSRR = GPIO_BSRR_BS2;
				break;
			case 5:
				GPIOA ->BSRR = GPIO_BSRR_BS3;
				break;
			case 6:
				GPIOA ->BSRR = GPIO_BSRR_BS5;
				break;
			case 7:
				GPIOB ->BSRR = GPIO_BSRR_BS5;
				break;
			}
		}
		else
		{
			switch(i)
			{
			case 0:
				GPIOA ->BSRR = GPIO_BSRR_BR8;
				break;
			case 1:
				GPIOA ->BSRR = GPIO_BSRR_BR9;
				break;
			case 2:
				GPIOA ->BSRR = GPIO_BSRR_BR10;
				break;
			case 3:
				GPIOA ->BSRR = GPIO_BSRR_BR12;
				break;
			case 4:
				GPIOA ->BSRR = GPIO_BSRR_BR2;
				break;
			case 5:
				GPIOA ->BSRR = GPIO_BSRR_BR3;
				break;
			case 6:
				GPIOA ->BSRR = GPIO_BSRR_BR5;
				break;
			case 7:
				GPIOB ->BSRR = GPIO_BSRR_BR5;
				break;
						}

		}
		cmd >>= 1;
		i++;
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
		__NOP();
	}

	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	GPIOB->BSRR = GPIO_BSRR_BS1;
	can.endit();//割り込み終了
}


