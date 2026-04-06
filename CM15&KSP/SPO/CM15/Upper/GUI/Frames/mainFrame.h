#ifndef _MAINFRAME_GUI_CM15_H
#define _MAINFRAME_GUI_CM15_H

#include "main.h"

extern const unsigned char logo[];

void InitGUI();

void ShowMainFrame();

void TranslateEvtMSG();

//void RefrashFrame();

void ProtocolStartMotor();

void ProtocolStopMotor();

void ProtocolAnimateMotor(uint8_t cnt);

void ProtocolAnimateOpenDoor(uint8_t cnt);

void DrawOpenDoor(enum PixelStatus pixelStatus);

#endif 