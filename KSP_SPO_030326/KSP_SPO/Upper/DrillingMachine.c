#include "DrillingMachine.h"

/*Global parameters*/
tool_t currentTool;
mode_t currentMode;
mode_param_t modeParam;
position_t position;

void ModeParam_Init(void){
    if(!fp->isLoaded) {
        modeParam.drillSpeed = 1200;
        modeParam.tapSpeed = 50;
    }
    else {
        //FP_GetParam();
        modeParam.drillSpeed = fp->params.fp_drillSpeed;
        modeParam.tapSpeed = fp->params.fp_tapSpeed;
    }
    modeParam.drillInc = 0;
    modeParam.tapInc = 0;  
    modeParam.wasCheckPointForDrillCnt = false;
    modeParam.wasCheckPointForTapCnt = false;
    currentTool = DRILL_TOOL;
}