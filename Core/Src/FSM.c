/*
 * FSM.c
 *
 *  Created on: Apr 11, 2022
 *      Author: joaod
 */
#include"FSM.h"

uint8_t clear[20] = "                   ";

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
	if (stateSetup == false){
		lcd_write_pos(0, 2, clear);
		lcd_write_pos(0, 0, clear);
		lcd_write_pos(15, 3, clear);
		lcd_write_pos(0, 0, "WELCOME!");
		lcd_write_pos(15, 3, "IDLE");
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, 0);
		stateSetup = true;
	}
	if (checkTagPresence() == MI_OK){
		lcd_write_pos(0, 1, clear);
		lcd_write_pos(0,2, clear);
		if (checkTagAccess() == MI_OK){
			updateSpaces();
			if (checkSpaces(getTag()) == p_ok){
				if (addSpace(getTag()) == p_full)
					lcd_write_pos(0, 1, "Park is full");
			}
			else{
				freeSpace(getTag());
			}
			lcd_write_pos(0, 2, readName());
			setNextState(OPEN);
		}
		else {
			lcd_write_pos(0, 2, "ACCESS DENIED");
		}
	}
}

void proc_OPEN(){
	if (stateSetup == false){
		lcd_write_pos(0, 0, clear);
		lcd_write_pos(15, 3, clear);
		lcd_write_pos(0, 0, "OPENING!");
		lcd_write_pos(15, 3, "OPEN");
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, 1);
		MTR_Rotation(0);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		stateSetup = true;
		//IFC_O implementado
	}
}

void proc_HOLD(){
	if (stateSetup == false){
		lcd_write_pos(0, 0, clear);
		lcd_write_pos(15, 3, clear);
		lcd_write_pos(15, 3, "HOLD");
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, 1);
		HAL_TIM_Base_Start_IT(&htim2);
		stateSetup = true;
	}
}

void proc_CLOSE(){
	if (stateSetup == false){
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 1){
			lcd_write_pos(15, 3, clear);
			lcd_write_pos(0, 0, "CLOSING!");
			lcd_write_pos(15, 3, "CLOSE");
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, 1);
			MTR_Rotation(1);
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			stateSetup = true;
		}
		else
			setNextState(IDLE);
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
