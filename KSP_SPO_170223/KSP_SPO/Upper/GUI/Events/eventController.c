#include "eventController.h"

button_t key1, key2, key3, openDoorBut, key4, limitSwitch, encKey;
led_t key1Led, key4Led, key3Led, key2Led1, key2Led2;
update_flag_t updateFlg;

button_t* buttons[] = {&key1,&key2,&key3,&key4, &encKey};
led_t *leds[] = {&key1Led, &key4Led, &key3Led, &key2Led1, &key2Led2};
void ClearButtons(void){
//     key1.isPressed = false;
//     key1.isReleased = false;
//     key1.wasPressed = false;
//     key1.pressCnt = 0;
//    
//     key2.isPressed = false;
//     key2.isReleased = false;
//     key2.wasPressed = false;
//     key2.pressCnt = 0;
//    
//     key3.isPressed = false;
//     key3.isReleased = false;
//     key3.wasPressed = false;
//     key3.pressCnt = 0;
//    
//     openDoorBut.isPressed = false;
//     openDoorBut.isReleased = false;
//     openDoorBut.wasPressed = false;
//     openDoorBut.pressCnt = 0;
//    
//     key4.isPressed = false;
//     key4.isReleased = false;
//     key4.wasPressed = false;
//     key4.pressCnt = 0;
//     
//     limitSwitch.isPressed = false;
//     limitSwitch.isReleased = false;
//     limitSwitch.wasPressed = false;
//     limitSwitch.pressCnt = 0;
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
	key1.port = KEY1_GPIO_Port;
	key1.pin = KEY1_Pin;
	key1.isPressed = false;
	
	key1.backPulse = false;
	key1.frontPulse = false;
	key1.pressCnt = 0;
	
	key2.port = KEY2_GPIO_Port;
	key2.pin = KEY2_Pin;
	key2.isPressed = false;
	
	key2.backPulse = false;
	key2.frontPulse = false;
	key2.pressCnt = 0;
	
	key3.port = KEY3_GPIO_Port;
	key3.pin = KEY3_Pin;
	key3.isPressed = false;

	key3.backPulse = false;
	key3.frontPulse = false;
	key3.pressCnt = 0;
	
	key4.port = KEY4_GPIO_Port;
	key4.pin = KEY4_Pin;
	key4.isPressed = false;

	key4.backPulse = false;
	key4.frontPulse = false;
	key4.pressCnt = 0;
	
	encKey.port = ENC_KEY_GPIO_Port;
	encKey.pin = ENC_KEY_Pin;
	encKey.isPressed = false;
	encKey.backPulse = false;
	encKey.frontPulse = false;
	encKey.pressCnt = 0;
	
	key1Led.button = &key1;
	key1Led.port = KEY_LED_1_GPIO_Port;
	key1Led.pin = KEY_LED_1_Pin;
	
	key2Led1.button = &key2;
	key2Led1.port = KEY_LED_2_GPIO_Port;
	key2Led1.pin = KEY_LED_2_Pin;
	
	key2Led2.button = &encKey;
	key2Led2.port = KEY_LED_3_GPIO_Port;
	key2Led2.pin = KEY_LED_3_Pin;
	
	key3Led.button = &key3;
	key3Led.port = KEY_LED_4_GPIO_Port;
	key3Led.pin = KEY_LED_4_Pin;
	
	key4Led.button = &key4;
	key4Led.port = KEY_LED_5_GPIO_Port;
	key4Led.pin = KEY_LED_5_Pin;
	
//	openDoorBut.port = KEY1_GPIO_Port;
//	openDoorBut.pin = KEY1_Pin;
//	openDoorBut.isPressed = false;
//	openDoorBut.wasPressed = false;
//	openDoorBut.backPulse = false;
//	openDoorBut.frontPulse = false;
//	openDoorBut.pressCnt = 0;
//	
//	limitSwitch.port = KEY1_GPIO_Port;
//	limitSwitch.pin = KEY1_Pin;
//	limitSwitch.isPressed = false;
//	limitSwitch.wasPressed = false;
//	limitSwitch.backPulse = false;
//	limitSwitch.frontPulse = false;
//	limitSwitch.pressCnt = 0;
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