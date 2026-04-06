#ifndef _EVT_CONTROLLER_H_
#define _EVT_CONTROLLER_H_

#include "main.h"

typedef struct {
    bool isPressed;
	bool isReleased;
	bool wasPressed;
    uint32_t pressCnt;
} button_t;

typedef struct {
    bool sec;
} update_flag_t;


extern button_t upArrowBut, downArrowBut, runStopBut, openDoorBut, enterBut, limitSwitch;

extern update_flag_t updateFlg;

void CheckButtons(void);

void ClearButtons(void);

#endif