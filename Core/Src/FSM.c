/*
 * FSM.c
 *
 *  Created on: Apr 11, 2022
 *      Author: joaod
 */
#include"FSM.h"

e_states state = CLOSE, nextState = IDLE;

void proc_IDLE();
void proc_OPEN();
void proc_HOLD();
void proc_CLOSE();

void MTR_Rotation(int i);

typedef void (*arrayfunc)(void);
arrayfunc selectState[] = {proc_IDLE, proc_OPEN, proc_HOLD, proc_CLOSE};

void setNextState(e_states tmp){
	nextState = tmp;
}

e_states getState(){
	return state;
}

void encodeFSM(){
	if (nextState != state){
		state = nextState;
		selectState[state]();
	}
}

void proc_IDLE(){
	//BTN implementado, falta o RFID
}

void proc_OPEN(){
	MTR_Rotation(0);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	//IFC_O implementado
}

void proc_HOLD(){
	//HAL_TIM_Base_Start_IT(&htim2);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	HAL_Delay(40000);
	nextState = CLOSE;
}

void proc_CLOSE(){
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
	MTR_Rotation(0);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	//IFC_C implementado e IV;
}

void MTR_Rotation(int i){
	if (i == 0){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 0);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 1);
	}
	else{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, 0);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, 1);
	}
}
