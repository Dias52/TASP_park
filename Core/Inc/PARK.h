/*
 * PARK.h
 *
 *  Created on: 22/06/2022
 *      Author: joaod
 */

#ifndef INC_PARK_H_
#define INC_PARK_H_
#include "RFID.h"
#include <stdbool.h>
#include <string.h>

struct space{
	bool occupied;
	struct Tag *user;
};

enum state{p_ok = 0, p_alocated = 1, p_full = 2};

struct Tag* tmp;
bool pick;

void updateSpaces();
int checkSpaces(struct Tag *p);
int freeSpace(struct Tag *p);
int addSpace(struct Tag *p);
void callRobot();


#endif /* INC_PARK_H_ */
