#include "DrillWidgets.h"
#include "stdlib.h"
#include "string.h"

uint8_t numBuf[11];
uint8_t* intToStr (uint32_t num);
uint16_t strlenUTF8( char* str );

uint8_t* intToStr (uint32_t num){
	for(int i = 0; i <sizeof(numBuf); i++){
		numBuf[i] = 0;
	}
	uint32_t modNum = num;
	uint8_t ch = 0;
	uint32_t mod = 1000000000;
	if (num == 0){
		numBuf[0] = 48;
		return numBuf;
	}
	uint8_t i = 0;
	while(modNum < mod){
		mod /= 10;
	}
	if (mod == 0) {
		mod = 1;
	}
	
	while (modNum > 0 || mod > 0){
		while (modNum>=mod){
			ch++;
			modNum -= mod;
		}
		numBuf[i++] = ch + 48;
		ch = 0;
		mod /= 10;
//		if (mod == 0) {
//		mod = 1;
//		}
	}
	return numBuf;
}

void DrawDrillWidget(bool drill, uint8_t* tx_buf, uint16_t range, uint16_t value, bool edit) {
    float buf = value;
    uint16_t _value = (uint16_t)buf;
    draw_rect_filled(tx_buf, 0, 5, 70, 55, 0);
    if(!drill)
    {
        draw_bitmap_8bpp(tx_buf, &DRILL, 25, 5, 18, 29);    
    }
    else
    {
        draw_bitmap_8bpp(tx_buf, &TAP, 20, 5, 35, 29);
    }
    
    select_font(&FreeSansBold9pt7b);  //FreeSansBold9pt7b
    uint32_t rpmValue = _value;  
    uint8_t* rpm = intToStr(rpmValue);  
    uint16_t valuePos = 256 - (strlenUTF8((char*)rpm) * 11 + 198);
    if(edit)
    {
        select_font(&FreeMonoBold9pt7b);
        draw_text(tx_buf, (uint8_t*)"----", 12, 50, 15);    
    }
    else
    {
        draw_text(tx_buf, rpm, valuePos, 50, 15);
    }
    select_font(&CourierCyr6pt8b);  //Picopixel
    uint8_t* rpmTypeVal = (uint8_t*)"1/РњРРќ"; 
    draw_text(tx_buf, rpmTypeVal, 14, 63, 15);
}

void DrawAbsIncWidget(uint8_t* tx_buf, float absValue, float incValue, bool editAbs, bool editInc, uint8_t mode) {
    if(mode == 1 || mode == 0)
        draw_rect_filled(tx_buf, 60, 5, 200, 55, 0);   
    if(mode == 2)
        draw_rect_filled(tx_buf, 60, 35, 200, 55, 0); 
    draw_bitmap_8bpp(tx_buf, &ABS, 85, 5, 33, 29);

    select_font(&FreeSansBold9pt7b); //FreeSansBold9pt7b
    
    uint16_t prevDotAbsValue;
    if(absValue < 0)
        prevDotAbsValue = -absValue;
    else
        prevDotAbsValue = absValue;
    uint8_t* prevDotAbs = intToStr(prevDotAbsValue);
    uint16_t valuePosAbs = 256 - (strlenUTF8((char*)prevDotAbs) * 11 + 148);
    if(absValue < 0)
        draw_char(tx_buf, '-', valuePosAbs - 8, 50, 15);
    draw_text(tx_buf, prevDotAbs, valuePosAbs, 50, 15);
    draw_char(tx_buf, '.', 109, 50, 15);
    float temp = (absValue - (int)absValue) * 10;
    uint32_t postDotAbsValue;
    if(temp < 0)
        postDotAbsValue = -temp;
    else
        postDotAbsValue = temp;
    uint8_t* postDotAbs = intToStr(postDotAbsValue);
    draw_text(tx_buf, postDotAbs, 115, 50, 15);
    
    if(editAbs){
        draw_bitmap_8bpp(tx_buf, &INC_WAIT, 150, 5, 33, 29);
    }
    
    if(editInc){
        draw_bitmap_8bpp(tx_buf, &INC_EDIT, 150, 5, 33, 29);
        select_font(&FreeMonoBold9pt7b);
        draw_text(tx_buf, (uint8_t*)"----", 143, 50, 15); 
    }
    if(!editAbs & !editInc) {      
        if(mode == 0)
            draw_bitmap_8bpp(tx_buf, &INC, 150, 5, 33, 29);   
    }
    if(!editInc){
        uint16_t prevDotIncValue = incValue;
        uint8_t* prevDotInc = intToStr(prevDotIncValue);
        uint16_t valuePosInc = 256 - (strlenUTF8((char*)prevDotAbs) * 11 + 83);
        draw_text(tx_buf, prevDotInc, valuePosInc, 50, 15);
        draw_char(tx_buf, '.', 174, 50, 15);
        float temp = (incValue - (int)incValue) * 10;
        uint32_t postDotIncValue = temp;
        uint8_t* postDotInc = intToStr(postDotIncValue);
        draw_text(tx_buf, postDotInc, 180, 50, 15);
    }
  
    select_font(&CourierCyr6pt8b); //Picopixel
    uint8_t* MM = (uint8_t*)"РњРњ";
    draw_text(tx_buf, MM, 125, 63, 15);
}

void DrawCntWidget(uint8_t* tx_buf, uint16_t value) {    
    
    draw_rect_filled(tx_buf, 217, 35, 255, 55, 0);
    
    draw_bitmap_8bpp(tx_buf, &CNT, 217, 5, 33, 29);   


    select_font(&FreeSansBold9pt7b); //FreeSansBold9pt7b
    uint16_t cntValue = value;
    uint8_t* cnt = intToStr(cntValue);
    uint16_t valuePos = 256 - (strlenUTF8((char*)cnt) * 11 + 6);
    draw_text(tx_buf, cnt, valuePos, 50, 15);

    
    select_font(&CourierCyr6pt8b); //Picopixel
    uint8_t* PSC = (uint8_t*)"РЁРў.";
    draw_text(tx_buf, PSC, 232, 63, 15);    
}

uint16_t strlenUTF8( char* str ){
	uint16_t i = 0;
	while( *str != '\0' ){
		if( (uint8_t)*str >= 0xC0 ){	// код 0xC0 соответствует символу кириллица 'A' по ASCII Win-1251
			str++;
		}
		
		i++;
		str++;
	}
	return i;
}