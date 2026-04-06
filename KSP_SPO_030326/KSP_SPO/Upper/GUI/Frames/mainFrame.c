#include "mainFrame.h"

uint16_t rpm_value = MINIMUM_RPM;
uint16_t dxRpm_value = 100;
uint16_t set_rpm = 0;

volatile char* valueStr;

uint16_t xValuePosition = 0;
uint16_t X = 10;
uint16_t dX = 1;



void InitGUI()
{
    ST7565_DrawBitmap( 0, 4, &logo, 128, 56, PIX_ON );
    ST7565_Update();
    LL_mDelay(3000);
    
    //drawHandleBar(rpm_value, "об/мин");
}

void ShowMainFrame()
{    
    //RefrashFrame();
    
    while(1)
    {
        TranslateEvtMSG();
        
        if(motorSpin) {
            ProtocolStartMotor();
        }
        else if(!motorSpin) {
            ProtocolStopMotor();
        }
        
        ST7565_DrawFilledRectangle(0, STATUS_BAR_SIZER, HORIZONTAL_DISPLAY_SIZE, MAIN_BAR_SIZER, PIX_OFF );
        
        valueStr = intToStr(set_rpm);
        
        xValuePosition = HORIZONTAL_DISPLAY_SIZE - (strlenUTF8(valueStr) * 16 + RIGHT_VALIE_SPACER);
        
        ST7565_Print ( xValuePosition, Y_VALIE_SPACER, valueStr, &Font_16x28, 1, PIX_ON );
        
        ST7565_UpdateArea(0, STATUS_BAR_SIZER, HORIZONTAL_DISPLAY_SIZE, 32);
        
        LL_TIM_OC_SetCompareCH1(TIM3, setPWM/2);
    }
    
}

void TranslateEvtMSG()
{
    /*Systick*/
    if(updateFlg.sec == true)
    {
        if(_timer > 0 && (_cnt%2 == 0) && motorSpin){
            --_timer;
           }
        else if (_timer == 0){
            motorSpin = false;
            _timer = 10;
        }     
             
        drawHandleBar(rpm_value, "об/мин");
        ++_cnt;
        if(_cnt == 4)
        {
            _cnt = 0;
        }
            
        ProtocolAnimateMotor(_cnt);
        ProtocolAnimateOpenDoor(_cnt);
        
        //valueStr = intToStr(ris); 
        
        updateFlg.sec = false;
    }
    
    /*Button pressed*/
    if(upArrowBut.isPressed == true){
    
        upArrowBut.isPressed = false;
    }
    if(downArrowBut.isPressed == true){
    
        downArrowBut.isPressed = false;
    }
    if(runStopBut.isPressed == true){
    
        runStopBut.isPressed = false;
    }
    if(openDoorBut.isPressed == true){
    
        openDoorBut.isPressed = false;
    }
    if(enterBut.isPressed == true){
    
        enterBut.isPressed = false;
    }
    
    /*Buttons releases*/
    if(upArrowBut.isReleased == true){
        switch (mode){
            case 1:
            {
                rpm_value += dxRpm_value;
                if(rpm_value > MAXIMUM_RPM)
                    rpm_value = MINIMUM_RPM;
                
                drawHandleBar(rpm_value, "об/мин");
                break;
            }
            case 2:
            {
                _timer += 1;
                if(_timer > 30)
                    _timer = 5;
                drawHandleBar(rpm_value, "об/мин");
                break;
            }
        }
        
        upArrowBut.isReleased = false;
        upArrowBut.pressCnt = 0;
    }
    if(downArrowBut.isReleased == true){
        switch (mode){
            case 1: 
            {
                rpm_value -= dxRpm_value;
                if(rpm_value < MINIMUM_RPM)
                    rpm_value = MAXIMUM_RPM;
                
                drawHandleBar(rpm_value, "об/мин");
                break;
            }
            case 2: 
            {
                _timer -= 1;
                if(_timer < 5)
                    _timer = 30;
                drawHandleBar(rpm_value, "об/мин");
                break;
            }
        }
        
        downArrowBut.isReleased = false;
        downArrowBut.pressCnt = 0;
    }
    if(runStopBut.isReleased == true){
        if (motorSpin) {
            motorSpin = false;
        }
        else if (!motorSpin) {
            motorSpin = true;
        }
        runStopBut.isReleased = false;
        runStopBut.pressCnt = 0;
    }
    if(openDoorBut.isReleased == true){
        if (openDoor) {
            openDoor = false;
        }
        else if (!openDoor) {
            openDoor = true;
        }
        openDoorBut.isReleased = false;
        openDoorBut.pressCnt = 0;
    }
    if(enterBut.isReleased == true){
        ++mode;
        if(mode > 2)
            mode = 1;
        enterBut.isReleased = false;
        enterBut.pressCnt = 0;
    }
    
    
    /*Buttons hold*/
    if(upArrowBut.pressCnt > 2)
    {
        switch (mode) {
            case 1:
            {
                rpm_value += dxRpm_value;
                if(rpm_value > MAXIMUM_RPM)
                    rpm_value = MINIMUM_RPM;
                
                drawHandleBar(rpm_value, "об/мин");
                break;
            }
            case 2:
            {
                _timer += 1;
                if(_timer > 30)
                    _timer = 5;
                drawHandleBar(rpm_value, "об/мин");
                break;
            }
        }
    }
    
    if(downArrowBut.pressCnt > 2)
    {
        switch (mode) {
            case 1:
            {
                rpm_value -= dxRpm_value;
                if(rpm_value < MINIMUM_RPM)
                    rpm_value = MAXIMUM_RPM;
              
                drawHandleBar(rpm_value, "об/мин");
                break;
            }
            case 2:
            {
                _timer -= 1;
                if(_timer < 5)
                    _timer = 30;
                drawHandleBar(rpm_value, "об/мин");
                break;
            }
            
        }
    }
}

//void RefrashFrame()
//{
//    ClearButtons();
//    ST7565_DrawFilledRectangle(0, STATUS_BAR_SIZER , HORIZONTAL_DISPLAY_SIZE, MAIN_BAR_SIZER, PIX_OFF );
//    
//    xValuePosition = HORIZONTAL_DISPLAY_SIZE - (strlenUTF8(valueStr) * 16 + RIGHT_VALIE_SPACER);
//    ST7565_Print ( xValuePosition, Y_VALIE_SPACER, valueStr, &Font_16x28, 1, PIX_ON );
//    ST7565_UpdateArea(0, STATUS_BAR_SIZER, HORIZONTAL_DISPLAY_SIZE, 32);
//}

void ProtocolStartMotor()
{
    if(set_rpm < rpm_value) {
        if(set_rpm < 2000) {
            set_rpm += dX * dxRpm_value;
            //setPWM = set_rpm;
            LL_mDelay(50);
        }
        else if(set_rpm > 2000 && set_rpm < 6000) {
            set_rpm += dX * dxRpm_value;
            //setPWM = set_rpm;
            LL_mDelay(2);
        }
        else {
            set_rpm += dX * dxRpm_value;
            //setPWM = set_rpm;
        }
    }
    else if(set_rpm > rpm_value){ 
        if(set_rpm > 2000) {
            set_rpm -= dX * dxRpm_value;
            //setPWM = set_rpm;
            LL_mDelay(50);
        }
        else if(set_rpm > 2000 && set_rpm < 6000) {
            set_rpm -= dX * dxRpm_value;
            //setPWM = set_rpm;
            LL_mDelay(2);
        }
        else {
            set_rpm -= dX * dxRpm_value;
            //setPWM = set_rpm;
        }
    }
    setPWM = set_rpm;
}

void ProtocolStopMotor()
{
    if(set_rpm > 0) {
        if(set_rpm > 6000) {
            set_rpm -= dX * 900;
            setPWM = set_rpm;
            LL_mDelay(10);
        }
        else if(set_rpm > 2000 && set_rpm < 6000) {
            set_rpm -= dX * 500;
            setPWM = set_rpm;
        }
        else if(set_rpm < 300) {
            set_rpm -= dX * 10;
            setPWM = set_rpm;
        }
        else {
            set_rpm -= dX * 200;
            setPWM = set_rpm;
        }
    }
}

void ProtocolAnimateMotor(uint8_t cnt)
{
    if(motorSpin) {
        if(cnt == 0){
            ST7565_DrawCircleHelper(116, 9, 5, 1, PIX_ON);
            ST7565_DrawCircleHelper(116, 9, 6, 1, PIX_ON);
            ST7565_UpdateArea(0, 0, HORIZONTAL_DISPLAY_SIZE, 16);
            ST7565_DrawFilledRectangle(64, 0, HORIZONTAL_DISPLAY_SIZE-64, STATUS_BAR_SIZER, PIX_OFF );
        }
        
        if(cnt == 1) {
            ST7565_DrawCircleHelper(116, 9, 5, 2, PIX_ON);
            ST7565_DrawCircleHelper(116, 9, 6, 2, PIX_ON);
            ST7565_UpdateArea(0, 0, HORIZONTAL_DISPLAY_SIZE, 16);
            ST7565_DrawFilledRectangle(64, 0, HORIZONTAL_DISPLAY_SIZE-64, STATUS_BAR_SIZER, PIX_OFF );
        }
        
        if(cnt == 2) {
            ST7565_DrawCircleHelper(116, 9, 5, 4, PIX_ON);
            ST7565_DrawCircleHelper(116, 9, 6, 4, PIX_ON);
            ST7565_UpdateArea(0, 0, HORIZONTAL_DISPLAY_SIZE, 16);
            ST7565_DrawFilledRectangle(64, 0, HORIZONTAL_DISPLAY_SIZE-64, STATUS_BAR_SIZER, PIX_OFF );
        }
        
        if(cnt == 3) {
            ST7565_DrawCircleHelper(116, 9, 5, 8, PIX_ON);
            ST7565_DrawCircleHelper(116, 9, 6, 8, PIX_ON);
            ST7565_UpdateArea(0, 0, HORIZONTAL_DISPLAY_SIZE, 16);
            ST7565_DrawFilledRectangle(64, 0, HORIZONTAL_DISPLAY_SIZE-64, STATUS_BAR_SIZER, PIX_OFF );
        }
    }
    else if(!motorSpin) {
        ST7565_DrawFilledRectangle(0, 0, HORIZONTAL_DISPLAY_SIZE, STATUS_BAR_SIZER, PIX_OFF );
        ST7565_UpdateArea(0, 0, HORIZONTAL_DISPLAY_SIZE, 16);
    }    
}

void ProtocolAnimateOpenDoor(uint8_t cnt)
{
    if(openDoor){
        switch(cnt)
        {
            case 0:
            {
                DrawOpenDoor(PIX_OFF);
                break;
            }
            case 1:
            {
                DrawOpenDoor(PIX_ON);
                break;
            }
            case 2:
            {
                DrawOpenDoor(PIX_OFF);
                break;
            }
            case 3:
            {
                DrawOpenDoor(PIX_ON);
                break;
            }
            default: break;
        }
    }
    else if(!openDoor){
        ST7565_DrawFilledRectangle(0, 0, HORIZONTAL_DISPLAY_SIZE - 64, STATUS_BAR_SIZER, PIX_OFF );
        ST7565_UpdateArea(0, 0, HORIZONTAL_DISPLAY_SIZE - 64, 16);
    }
}

void DrawOpenDoor(enum PixelStatus pixelStatus)
{
    ST7565_DrawFilledRectangle(5, 8, 10, 4, pixelStatus );
    ST7565_DrawLine(5, 6, 13, 2, pixelStatus);
    ST7565_UpdateArea(0, 0, HORIZONTAL_DISPLAY_SIZE - 64, 16);
}