/*
 * main.cpp
 *
 *  Created on: Aug 11, 2020
 *      Author: ryu
 */
#include "main.h"
#include "CanClass.hpp"

namespace {
	CanClass can;
	uint8_t receive_data;
	uint8_t send_data = 1;
}

extern "C" {
	void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
	{
		can.receive(receive_data, 0x500);
		can.endit();//割り込み終了
	}
};

void main_cpp(void)
{
	can.init(0x4c0);
	while(1){
		HAL_Delay(1000);
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
		can.send(send_data, 0x508);
		can.send(send_data,0x4c4);
		can.led_process();
	}

}






