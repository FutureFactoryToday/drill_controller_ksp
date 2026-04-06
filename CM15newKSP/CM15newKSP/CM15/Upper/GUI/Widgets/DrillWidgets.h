#ifndef DRILLWIDGETS_H
#define DRILLWIDGETS_H

#include "main.h"

void DrawDrillWidget(bool drill, uint8_t* tx_buf, uint16_t range, uint16_t value);

void DrawAbsIncWidget(uint8_t* tx_buf, uint16_t absValue, uint16_t incValue);

void DrawCntWidget(uint8_t* tx_buf, uint16_t value);


#endif