#include "eventController.h"

button_t upArrowBut, downArrowBut, runStopBut, openDoorBut, enterBut, limitSwitch;

update_flag_t updateFlg;

void ClearButtons(void){
     upArrowBut.isPressed = false;
     upArrowBut.isReleased = false;
     upArrowBut.wasPressed = false;
     upArrowBut.pressCnt = 0;
    
     downArrowBut.isPressed = false;
     downArrowBut.isReleased = false;
     downArrowBut.wasPressed = false;
     downArrowBut.pressCnt = 0;
    
     runStopBut.isPressed = false;
     runStopBut.isReleased = false;
     runStopBut.wasPressed = false;
     runStopBut.pressCnt = 0;
    
     openDoorBut.isPressed = false;
     openDoorBut.isReleased = false;
     openDoorBut.wasPressed = false;
     openDoorBut.pressCnt = 0;
    
     enterBut.isPressed = false;
     enterBut.isReleased = false;
     enterBut.wasPressed = false;
     enterBut.pressCnt = 0;
     
     limitSwitch.isPressed = false;
     limitSwitch.isReleased = false;
     limitSwitch.wasPressed = false;
     limitSwitch.pressCnt = 0;
}

void CheckButtons(void)
{
    if(LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_0)){
        upArrowBut.isPressed = false;
        upArrowBut.isReleased = true;
        upArrowBut.pressCnt = 0;
    }
    upArrowBut.wasPressed = false;
    
        
    
    if(downArrowBut.wasPressed == true){
        downArrowBut.isReleased = true;
    }
    downArrowBut.isPressed = false;
    downArrowBut.wasPressed = false;
    downArrowBut.pressCnt = 0;

    
    if(runStopBut.wasPressed == true){
        runStopBut.isReleased = true;
    }
    runStopBut.isPressed = false;
    runStopBut.wasPressed = false;
    runStopBut.pressCnt = 0;
    
    
    if(openDoorBut.wasPressed == true){
        openDoorBut.isReleased = true;
    }
    openDoorBut.isPressed = false;
    openDoorBut.wasPressed = false;
    openDoorBut.pressCnt = 0;
    
    
    if(enterBut.wasPressed == true){
        enterBut.isReleased = true;
    }
    enterBut.isPressed = false;
    enterBut.wasPressed = false;
    enterBut.pressCnt = 0;
    
    
    if(limitSwitch.wasPressed == true){
        limitSwitch.isReleased = true;
    }
    limitSwitch.isPressed = false;
    limitSwitch.wasPressed = false;
    limitSwitch.pressCnt = 0;
}