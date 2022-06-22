/*
 * FSM.h
 *
 *  Created on: Apr 11, 2022
 *      Author: joaod
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "gpio.h"
#include "tim.h"
#include "RFID.h"
#include <stdbool.h>
#include "i2cdisplay.h"
#include "PARK.h"

typedef enum ENUM_STATES{IDLE = 0, OPEN, HOLD, CLOSE} e_states;

void setNextState(e_states tmp);
e_states getState();

void encodeFSM();

#endif /* INC_FSM_H_ */
