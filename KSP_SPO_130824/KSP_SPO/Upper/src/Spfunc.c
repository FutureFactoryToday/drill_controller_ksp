#include "Spfunc.h"

uint8_t numBuf[11] = {0};
uint32_t setPWM = 0;

uint8_t* intToStr (uint32_t num){
	for(int i = 0; i <sizeof(numBuf); i++){
		numBuf[i] = 0;
	}
	uint32_t modNum = num;
	uint8_t ch = 0;
	uint32_t mod = 1000000000;
	if (num == 0){
		numBuf[0] = 48;
		return numBuf;
	}
	uint8_t i = 0;
	while(modNum < mod){
		mod /= 10;
	}
	if (mod == 0) {
		mod = 1;
	}
	
	while (modNum > 0 || mod > 0){
		while (modNum>=mod){
			ch++;
			modNum -= mod;
		}
		numBuf[i++] = ch + 48;
		ch = 0;
		mod /= 10;
//		if (mod == 0) {
//		mod = 1;
//		}
	}
	return numBuf;
}