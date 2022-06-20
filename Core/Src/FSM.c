/*
 * FSM.c
 *
 *  Created on: Apr 11, 2022
 *      Author: joaod
 */
#include"FSM.h"

e_states state = CLOSE, nextState = CLOSE;
bool stateSetup = false;

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
	if (state != nextState)
		stateSetup = false;
	state = nextState;
	selectState[state]();
}

void proc_IDLE(){
	if (checkTagPresence() == MI_OK){
		if (checkTagAccess() == MI_OK){
			//writeDisplay(line, getRFIDData());
			setNextState(OPEN);
		}
	}
}

void proc_OPEN(){
	if (stateSetup == false){
		MTR_Rotation(0);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		stateSetup = true;
		//IFC_O implementado
	}
}

void proc_HOLD(){
	if (stateSetup == false){
		HAL_TIM_Base_Start_IT(&htim2);
		stateSetup = true;
	}
}

void proc_CLOSE(){
	if (stateSetup == false){
		MTR_Rotation(1);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		stateSetup = true;
	}
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
