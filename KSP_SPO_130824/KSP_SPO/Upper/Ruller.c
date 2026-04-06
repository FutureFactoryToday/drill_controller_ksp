#include "Ruller.h"
#define STEP 0.00390625
#define POLE_STEP 4
#define STEP_NUM 1024

int32_t relativePosition = 0;
int16_t oldPoz = 0;	
int32_t relMM, relUM;

void RUL_modifRelativePosition(int16_t poz){
	//int16_t test = poz;
	int32_t deltaPoz = poz - oldPoz;
	
	relativePosition += deltaPoz;
	oldPoz = poz;
}

void RUL_convertIntToMM(void){
	bool sign = (relativePosition >= 0);
	relMM = relativePosition>>8; //Impulse count devided by 256 to convert into mm (1024/4)
	uint32_t tempUM, temp2;
	tempUM = sign?relativePosition:(-relativePosition);
	tempUM &= 0x000000FF;
	tempUM *= 100;
	tempUM >>= 8;
	temp2 = tempUM/10;
	if (tempUM - temp2*10 >= 5){
		tempUM = tempUM/10 + 1;
	} else {
		tempUM = tempUM/10;
	}
	relUM = tempUM;
}