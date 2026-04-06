#ifndef _EVT_CONTROLLER_H_
#define _EVT_CONTROLLER_H_

#include "main.h"
#define PRESS_DELAY 10

typedef struct {
	GPIO_TypeDef* port;
	uint32_t pin;
	bool oldValue;
    bool isPressed;
	bool backPulse;
	bool frontPulse;
    uint32_t pressCnt;
} button_t;

typedef struct{
	GPIO_TypeDef* port;
	uint32_t pin;
	button_t *button;
} led_t;

typedef struct {
    bool sec;
} update_flag_t;

extern button_t* buttons[];
extern button_t key1, key2, key3, openDoorBut, key4, limitSwitch, encKey;
extern led_t key1Led, key4Led, key3Led, key2Led1, key2Led2;
extern update_flag_t updateFlg;

void EC_CheckButtons(void);

void EC_ClearButtons(void);

void EC_Init(void);
void EC_LightKeyLeds(void);
#endif