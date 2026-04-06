#include "DrillWidgets.h"



void DrawDrillWidget(bool drill, uint8_t* tx_buf, uint16_t range, uint16_t value) {
    float bufRange = range;
    float bufValue = value;
    float buf = bufValue/bufRange * 100;
    uint16_t _value = (uint16_t)buf;
    
    if(drill)
        draw_bitmap_8bpp(tx_buf, &DRILL, 25, 5, 18, 29);
    else
        draw_bitmap_8bpp(tx_buf, &TAP, 20, 5, 35, 29);
    
    select_font(&FreeSansBold9pt7b);  
    uint32_t rpmValue = _value;  
    uint8_t* rpm = intToStr(rpmValue);  
    uint16_t valuePos = 256 - (strlenUTF8((char*)rpm) * 11 + 205);
    draw_text(tx_buf, rpm, valuePos, 50, 15);
  
    select_font(&Picopixel);  
    uint8_t* rpmTypeVal = (uint8_t*)"1/MIN"; 
    draw_text(tx_buf, rpmTypeVal, 23, 60, 15);
}

void DrawAbsIncWidget(uint8_t* tx_buf, uint16_t absValue, uint16_t incValue) {
    
    draw_bitmap_8bpp(tx_buf, &ABS, 85, 5, 33, 29);
    
    select_font(&FreeSansBold9pt7b);
    uint32_t prevDotValue = 10;
    uint8_t* prevDot = intToStr(prevDotValue);
    draw_text(tx_buf, prevDot, 83, 50, 15);
    draw_char(tx_buf, '.', 106, 50, 15);
    uint32_t postDotValue = 0;
    uint8_t* postDot = intToStr(postDotValue);
    draw_text(tx_buf, postDot, 112, 50, 15);
  
    select_font(&Picopixel);
    uint8_t* MM = (uint8_t*)"MM";
    draw_text(tx_buf, MM, 125, 60, 15);
    
    draw_bitmap_8bpp(tx_buf, &INC, 150, 5, 33, 29);
}

void DrawCntWidget(uint8_t* tx_buf, uint16_t value) {    
    draw_bitmap_8bpp(tx_buf, &CNT, 215, 5, 33, 29);         
}