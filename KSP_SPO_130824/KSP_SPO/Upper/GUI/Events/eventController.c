#include "eventController.h"

button_t keySpindleStart, keyToolChange, keySpindleStop, openDoorBut, keyAbsoluteOriginSet, limitSwitch, encKey;
led_t ledKeySpindleStart, ledKeyAbsoluteOriginSet, ledKeySpindleStop, ledActiveDrillMode, ledActiveTapMode;
update_flag_t updateFlg;
enc_cnt_t encCnt;

button_t* buttons[] = {&keySpindleStart,&keyToolChange,&keySpindleStop,&keyAbsoluteOriginSet, &encKey};
led_t *leds[] = {&ledKeySpindleStart, &ledKeyAbsoluteOriginSet, &ledKeySpindleStop, &ledActiveDrillMode, &ledActiveTapMode};
void ClearButtons(void){
}

void EC_CheckButtons(void){
	uint8_t butNum = sizeof(buttons)/sizeof(button_t*);
	button_t *curBut;
	bool pinStatus;
	for(uint8_t i = 0; i < butNum; i++){
		curBut = *(buttons + i);
		pinStatus = !LL_GPIO_IsInputPinSet(curBut->port,curBut->pin);
		if (pinStatus == curBut->oldValue){
			curBut->pressCnt++;
		 if (curBut->pressCnt >= PRESS_DELAY){
			 curBut->pressCnt--;
			 if(pinStatus != curBut->isPressed){ 
				 if (pinStatus){
					 curBut->frontPulse = true;
					 curBut->isPressed = true;
					}	else {
					 curBut->backPulse = true;
					 curBut->isPressed = false;
					}		 
				}
			}
		} else {
			curBut->pressCnt = 0;
		}
		curBut->oldValue = pinStatus;
	}
}
void EC_Init(void){
	keySpindleStart.port = KEY1_GPIO_Port;
	keySpindleStart.pin = KEY1_Pin;
	keySpindleStart.isPressed = false;
	
	keySpindleStart.backPulse = false;
	keySpindleStart.frontPulse = false;
	keySpindleStart.pressCnt = 0;
	
	keyToolChange.port = KEY2_GPIO_Port;
	keyToolChange.pin = KEY2_Pin;
	keyToolChange.isPressed = false;
	
	keyToolChange.backPulse = false;
	keyToolChange.frontPulse = false;
	keyToolChange.pressCnt = 0;
	
	keySpindleStop.port = KEY3_GPIO_Port;
	keySpindleStop.pin = KEY3_Pin;
	keySpindleStop.isPressed = false;

	keySpindleStop.backPulse = false;
	keySpindleStop.frontPulse = false;
	keySpindleStop.pressCnt = 0;
	
	keyAbsoluteOriginSet.port = KEY4_GPIO_Port;
	keyAbsoluteOriginSet.pin = KEY4_Pin;
	keyAbsoluteOriginSet.isPressed = false;

	keyAbsoluteOriginSet.backPulse = false;
	keyAbsoluteOriginSet.frontPulse = false;
	keyAbsoluteOriginSet.pressCnt = 0;
	
	encKey.port = ENC_KEY_GPIO_Port;
	encKey.pin = ENC_KEY_Pin;
	encKey.isPressed = false;
	encKey.backPulse = false;
	encKey.frontPulse = false;
	encKey.pressCnt = 0;
	
	ledKeySpindleStart.button = &keySpindleStart;
	ledKeySpindleStart.port = KEY_LED_1_GPIO_Port;
	ledKeySpindleStart.pin = KEY_LED_1_Pin;
	
	ledActiveDrillMode.button = &keyToolChange;
	ledActiveDrillMode.port = KEY_LED_2_GPIO_Port;
	ledActiveDrillMode.pin = KEY_LED_2_Pin;
	
	ledActiveTapMode.button = &encKey;
	ledActiveTapMode.port = KEY_LED_3_GPIO_Port;
	ledActiveTapMode.pin = KEY_LED_3_Pin;
	
	ledKeySpindleStop.button = &keySpindleStop;
	ledKeySpindleStop.port = KEY_LED_4_GPIO_Port;
	ledKeySpindleStop.pin = KEY_LED_4_Pin;
	
	ledKeyAbsoluteOriginSet.button = &keyAbsoluteOriginSet;
	ledKeyAbsoluteOriginSet.port = KEY_LED_5_GPIO_Port;
	ledKeyAbsoluteOriginSet.pin = KEY_LED_5_Pin;
}
void EC_LightKeyLeds(void){
	uint8_t ledNum = sizeof(leds)/sizeof(led_t*);
	led_t *curLed;
	for(uint8_t i = 0; i < ledNum; i++){
		curLed = *(leds + i);
		if(curLed->button->isPressed){
			LL_GPIO_SetOutputPin(curLed->port,curLed->pin);
		} else {
			LL_GPIO_ResetOutputPin(curLed->port,curLed->pin);
		}
	}
}

void EC_UpdateEncCnt(void) {
    encCnt.cntSecond = LL_TIM_GetCounter(TIM3)/2;
    encCnt.cntDelta = encCnt.cntSecond - encCnt.cntPrevious;
    encCnt.cntPrevious = encCnt.cntSecond;
}
void EC_ResetEncCnt(void) {
    encCnt.cntDelta = 0;
}