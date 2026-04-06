#ifndef DRILLWIDGETS_H
#define DRILLWIDGETS_H

#include "main.h"

void DrawDrillWidget(bool drill, uint8_t* tx_buf, uint16_t range, uint16_t value, bool edit);

void DrawAbsIncWidget(uint8_t* tx_buf, float absValue, float incValue, bool editAbs, bool editInc, uint8_t mode);

void DrawCntWidget(uint8_t* tx_buf, uint16_t value);


#endif