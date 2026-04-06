#include "widgets.h"

void drawHandleBar(uint16_t value, char* unit)
{
    
    ST7565_DrawFilledRectangle(0, (STATUS_BAR_SIZER + MAIN_BAR_SIZER), HORIZONTAL_DISPLAY_SIZE, HANDLE_BAR_SIZER, PIX_ON );
    
    
    char* _value_timer = intToStr(_timer);
    uint16_t secValuePos = HORIZONTAL_DISPLAY_SIZE - (strlenUTF8(_value_timer) * 6 + 105);
    uint16_t secUnitPos = HORIZONTAL_DISPLAY_SIZE - (strlenUTF8(" с") * 6 + 92);
    
    ST7565_Print ( secValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), _value_timer, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );
    ST7565_Print ( secUnitPos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), " с", &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );
    
    
    char* _value = intToStr(value);
    uint16_t xValuePos = HORIZONTAL_DISPLAY_SIZE - (strlenUTF8(_value) * 6 + 50);
    uint16_t xUnitPos = HORIZONTAL_DISPLAY_SIZE - (strlenUTF8(unit) * 6 + 5);
    
    switch(mode)
    {
        case 1:
        {
            if(!motorSpin)
            {
                if(_cnt%2 == 0){
                    ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), _value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );
                    }  
                else{
                    ST7565_DrawFilledRectangle(xValuePos - 3, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 1), strlenUTF8(_value) * 6 + 4, HANDLE_BAR_SIZER - 3, PIX_OFF );
                    ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), _value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_ON );
                }
            }
            else{
                ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), _value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );
            }
            ST7565_Print ( xUnitPos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), unit, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );  
            ST7565_UpdateArea(0, 48, HORIZONTAL_DISPLAY_SIZE, 16);
            break;
        }
        case 2:
        {
            char* timer_value = intToStr(_timer);
            uint16_t xValuePos = HORIZONTAL_DISPLAY_SIZE - (strlenUTF8(_value) * 6 + 50);
            if(!motorSpin)
            {
                if(_cnt%2 == 0){
                    ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), timer_value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );
                    }  
                else{
                    ST7565_DrawFilledRectangle(xValuePos - 3, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 1), strlenUTF8(timer_value) * 6 + 4, HANDLE_BAR_SIZER - 3, PIX_OFF );
                    ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), timer_value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_ON );
                }
            }
            else{
                ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), timer_value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );
            }
            ST7565_Print ( xUnitPos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), " с", &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );  
            ST7565_UpdateArea(0, 48, HORIZONTAL_DISPLAY_SIZE, 16);
            break;
        }
//        case 3:
//        {
//            if(!motorSpin)
//            {
//                if(_cnt%2 == 0){
//                    ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), _value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );
//                    }  
//                else{
//                    ST7565_DrawFilledRectangle(xValuePos - 3, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 1), strlenUTF8(_value) * 6 + 4, HANDLE_BAR_SIZER - 3, PIX_OFF );
//                    ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), _value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_ON );
//                }
//            }
//            else{
//                ST7565_Print ( xValuePos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), _value, &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );
//            }
//            ST7565_Print ( xUnitPos, (STATUS_BAR_SIZER + MAIN_BAR_SIZER + 2), " x G", &Font_6x8, DISPLAY_COLOR_BLACK, PIX_OFF );  
//            ST7565_UpdateArea(0, 48, HORIZONTAL_DISPLAY_SIZE, 16);
//            break;
//        }
        default: break;
    }

}