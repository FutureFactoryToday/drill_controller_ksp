/**
  ******************************************************************************
  * @file    FlashParam.h
  * @brief   This file contains all the function prototypes for
  *          the FlashParam.c file
  ******************************************************************************
  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _FLASH_PARAM_H_
#define _FLASH_PARAM_H_

/*Includes */
#include "main.h"

/*Public defines */
#define USER_FLASH_START 0x0801FC00
#define START_FP_FLAG 0x12345678
#define END_FP_FLAG 0x87654321

//#define FL_KEY1 0x45670123
//#define FL_KEY2 0xCDEF89AB
#define USER_FLASH_PAGE 
/*Global params*/
typedef struct {
	uint32_t startLoadFlag;
	uint32_t cnt;
    int32_t fp_drillSpeed;
    int32_t fp_tapSpeed;
//    int32_t fp_drillInc;
//    int32_t fp_tapInc;  
//    uint8_t fp_drillCnt;
//    uint8_t fp_tapCnt;
	uint32_t endLoadFlag;
} stored_params_t;

typedef struct {
	bool isLoaded;
	bool needToSave; 
	stored_params_t params;
}flash_params_t;

extern flash_params_t* fp;
	
#define FIRST_ELEMENT startLoadFlag
/*Prototypes */
flash_params_t* FP_GetParam(void);
uint8_t FP_SaveParam(void);
uint8_t FP_DeleteParam(void);
//uint8_t FP_SaveOneParam(uint32_t data, uint32_t adr);
#endif /* __FLASH_PARAM_H__ */

