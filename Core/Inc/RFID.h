#ifndef INC_RFID_H_
#define INC_RFID_H_

#include "stm32f1_rc522.h"
#include "string.h"
#include <stdbool.h>

struct Tag{
	uint8_t name[MAX_LEN];
	uint8_t keyCard[5];
	uint8_t KEY[6];
	bool auth;
	bool setUp;
	struct Tag *next;
};

void addTag(struct Tag* tag);
uint8_t setupTag();

uint8_t checkTagPresence();
uint8_t checkTagAccess();
uint8_t authenticate(uint8_t);
uint8_t readTag(uint8_t);
uint8_t writeTag(uint8_t);
char* readName();
struct Tag* getTag();
#endif /* INC_RFID_H_ */
