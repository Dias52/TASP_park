#include "RFID.h"

uint8_t status;
uint8_t str[MAX_LEN];

uint8_t serNum[5];

uint8_t key;

struct Tag* head = NULL;
struct Tag* current;
struct Tag* p;

uint8_t test;
uint8_t W[16];
uint8_t R[16];

void addTag(struct Tag* tag){
	if (head == NULL){
		head = tag;
	}
	else{
		current = head;
		while(current->next != NULL)
			current = current->next;
		current->next = tag;
	}
	if (tag->setUp == false){
		p = tag;
		setupTag(tag);
		tag->setUp = true;
		p = NULL;
	}
}

uint8_t setupTag(struct Tag* tag){
	while(checkTagPresence() != MI_OK && (serNum[0] != tag->keyCard[0] || serNum[1] != tag->keyCard[1] || serNum[2] != tag->keyCard[2] || serNum[3] != tag->keyCard[3] || serNum[4] != tag->keyCard[4]));
	authenticate(4);
	memcpy(W, tag->name, 16);
	writeTag(4);
	readTag(4);
	return MI_OK;
}

uint8_t checkTagPresence(){
	status = MFRC522_Request(PICC_REQIDL, str);
	status = MFRC522_Anticoll(str);
	memcpy(serNum, str, 5);
	return status;
}

uint8_t checkTagAccess(){
	int flag = 0;
	current = head;
	while(current != NULL){
		for (int i = 0; i < 5; i++){
			if (serNum[i] != current->keyCard[i])
				flag = 1;
		}
		if (flag == 1){
			current = current->next;
			flag = 0;
		}
		else {
			p = current;
			return MI_OK;
		}
	}
	return MI_NOTAGERR;
}

uint8_t authenticate(uint8_t bAddr){
	MFRC522_SelectTag(str);
	test = MFRC522_Auth(PICC_AUTHENT1A, bAddr, p->KEY, serNum);
	if (test == MI_OK){
		p->auth = true;
		return MI_OK;
	}
	return MI_ERR;
}

uint8_t readTag(uint8_t bAddr){
	if (p->auth == true){
		status = MFRC522_Read(bAddr, R);
		return status;
	}
	return MI_ERR;
}

uint8_t writeTag(uint8_t bAddr){
	if (p->auth == true){
		status = MFRC522_Write(bAddr, W);
		return status;
	}
	return MI_ERR;
}
