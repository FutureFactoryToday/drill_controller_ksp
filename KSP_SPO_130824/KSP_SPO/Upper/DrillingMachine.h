#ifndef _DRILLING_MACH_H_
#define _DRILLING_MACH_H_
#include "main.h"
typedef enum {
    DRILL_TOOL,
    TAP_TOOL
} tool_t;

typedef enum {
    SET_SPINDLE_RPM,
    SET_ABSOLUTE_ORIGIN,
    SET_INCREMENTAL_ORIGIN
} mode_t;

typedef struct {
    int32_t drillSpeed;
    int32_t tapSpeed;
    int32_t drillInc;
    int32_t tapInc;  
    uint8_t drillCnt;
    uint8_t tapCnt;
    bool wasCheckPointForDrillCnt;
    bool wasCheckPointForTapCnt;
} mode_param_t;

typedef struct {
    float realPositionInFloat;
    float incrementalPositionInFloat;
} position_t;

extern tool_t currentTool;
extern mode_t currentMode;
extern mode_param_t modeParam;
extern position_t position;

void ModeParam_Init(void);
#endif
