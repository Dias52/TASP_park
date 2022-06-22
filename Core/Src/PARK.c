/*
 * PARK.c
 *
 *  Created on: 22/06/2022
 *      Author: joaod
 */
#include "PARK.h"

struct space spaces[4] = {{false, NULL},
						  {false, NULL},
						  {false, NULL},
						  {false, NULL}};

int cmpKeyCard(struct Tag *x, struct Tag *y){
	int tmp = 1;
	for (int i = 0; i < 6; i++){
		if (x->keyCard[i] != y->keyCard[i])
			tmp = 0;
	}
	return tmp;
}

void updateSpaces(){
	if (!HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8))
		spaces[0].occupied = true;
	if (!HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7))
			spaces[1].occupied = true;
	if (!HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9))
			spaces[2].occupied = true;
	if (!HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_1))
			spaces[3].occupied = true;
}

int checkSpaces(struct Tag *p){
	for (int i = 0; i < 4; i++){
		if (spaces[i].occupied == true && cmpKeyCard(spaces[i].user, p) == 1)
			return p_alocated;
	}
	return p_ok;
}

int freeSpace(struct Tag *p){
	for (int i = 0; i < 4; i++){
		if (cmpKeyCard(spaces[i].user, p) == 1){
			spaces[i].user = NULL;
			tmp = p;
			pick = 0;
		}
	}
	return p_ok;
}

int addSpace(struct Tag *p){
	for (int i = 0; i < 4; i++){
		if(spaces[i].occupied == false){
			spaces[i].user = p;
			tmp = p;
			pick = 1;
			return p_ok;
		}
	}
	return p_full;
}

void callRobot(){
	if (pick == 1){

	}
	else{

	}
}
