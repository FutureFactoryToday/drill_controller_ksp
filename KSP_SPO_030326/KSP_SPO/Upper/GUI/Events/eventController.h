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

typedef struct {
    uint16_t    cntPrevious;
    int16_t     cntSecond;
    int32_t     cntDelta;
} enc_cnt_t;

extern button_t* buttons[];
extern button_t keySpindleStart, keyToolChange, keySpindleStop, openDoorBut, keyAbsoluteOriginSet, limitSwitch, encKey;
extern led_t ledKeySpindleStart, ledKeyAbsoluteOriginSet, ledKeySpindleStop, ledActiveDrillMode, ledActiveTapMode;
extern update_flag_t updateFlg;
extern enc_cnt_t encCnt;

void EC_CheckButtons(void);

void EC_ClearButtons(void);

void EC_Init(void);
void EC_LightKeyLeds(void);

void EC_UpdateEncCnt(void);
void EC_ResetEncCnt(void);
#endif