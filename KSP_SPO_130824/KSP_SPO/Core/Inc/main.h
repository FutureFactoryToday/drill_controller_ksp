/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_dac.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_spi.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"

/* KSP_DRILL_BEGIN */
#include "SSD1322_API.h"
#include "SSD1322_GFX.h"
#include "SSD1322_HW_Driver.h"
#include "Motor/Motor.h"
#include "GUI/Widgets/DrillWidgets.h"
#include "Ruller.h"
#include "FlashParam.h"
#include "DrillingMachine.h"
/* KSP_DRILL_END */

#include "GUI/Events/eventController.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

extern const GFXfont Picopixel;
extern const GFXfont FreeSansBold9pt7b;
extern const GFXfont FreeMonoBold9pt7b;
extern const GFXfont FreeSerif6pt8b; //+
extern const GFXfont Cooper6pt8b; //+
extern const GFXfont CourierCyr6pt8b; //++

extern const unsigned short DRILL;
extern const unsigned short ABS;
extern const unsigned short INC;
extern const unsigned short INC_EDIT;
extern const unsigned short INC_WAIT;
extern const unsigned short CNT;
extern const unsigned short INC;
extern const unsigned short TAP;
extern const unsigned short KSP_LOGO;

/* USER CODE END ET */
extern uint8_t tx_buf[];
extern bool isOrigin;
extern uint32_t cntLine;
extern uint8_t tickCnt;

extern bool rpmChange;
extern bool absChange;
extern bool incChange;

extern bool rpmEdit;
extern bool absEdit;
extern bool incEdit;


/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void InitGui();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_TIM TIM8
#define MOT_TIM TIM7
#define KEY_TIM TIM6
#define KEY_LED_4_Pin LL_GPIO_PIN_13
#define KEY_LED_4_GPIO_Port GPIOC
#define KEY_LED_5_Pin LL_GPIO_PIN_14
#define KEY_LED_5_GPIO_Port GPIOC
#define LINE_Z_Pin LL_GPIO_PIN_2
#define LINE_Z_GPIO_Port GPIOA
#define LINE_Z_EXTI_IRQn EXTI2_IRQn
#define DAC_5_10V_Pin LL_GPIO_PIN_3
#define DAC_5_10V_GPIO_Port GPIOA
#define ENC_KEY_Pin LL_GPIO_PIN_5
#define ENC_KEY_GPIO_Port GPIOA
#define ENC_A_Pin LL_GPIO_PIN_6
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin LL_GPIO_PIN_7
#define ENC_B_GPIO_Port GPIOA
#define KEY1_Pin LL_GPIO_PIN_4
#define KEY1_GPIO_Port GPIOC
#define KEY1_EXTI_IRQn EXTI4_IRQn
#define KEY2_Pin LL_GPIO_PIN_5
#define KEY2_GPIO_Port GPIOC
#define KEY2_EXTI_IRQn EXTI9_5_IRQn
#define KEY3_Pin LL_GPIO_PIN_0
#define KEY3_GPIO_Port GPIOB
#define KEY3_EXTI_IRQn EXTI0_IRQn
#define KEY4_Pin LL_GPIO_PIN_1
#define KEY4_GPIO_Port GPIOB
#define KEY4_EXTI_IRQn EXTI1_IRQn
#define MODBUS_TRE_Pin LL_GPIO_PIN_2
#define MODBUS_TRE_GPIO_Port GPIOB
#define MODBUS_TX_Pin LL_GPIO_PIN_10
#define MODBUS_TX_GPIO_Port GPIOB
#define MODBUS_RX_Pin LL_GPIO_PIN_11
#define MODBUS_RX_GPIO_Port GPIOB
#define LED_Pin LL_GPIO_PIN_12
#define LED_GPIO_Port GPIOB
#define RK_HIGH_4_Pin LL_GPIO_PIN_13
#define RK_HIGH_4_GPIO_Port GPIOB
#define RK_HIGH_3_Pin LL_GPIO_PIN_14
#define RK_HIGH_3_GPIO_Port GPIOB
#define RK_HIGH_2_Pin LL_GPIO_PIN_15
#define RK_HIGH_2_GPIO_Port GPIOB
#define RK_HIGH_1_Pin LL_GPIO_PIN_6
#define RK_HIGH_1_GPIO_Port GPIOC
#define RK_LOW_4_Pin LL_GPIO_PIN_7
#define RK_LOW_4_GPIO_Port GPIOC
#define RK_LOW_3_Pin LL_GPIO_PIN_8
#define RK_LOW_3_GPIO_Port GPIOC
#define RK_LOW_2_Pin LL_GPIO_PIN_9
#define RK_LOW_2_GPIO_Port GPIOC
#define RK_LOW_1_Pin LL_GPIO_PIN_8
#define RK_LOW_1_GPIO_Port GPIOA
#define KEY_LED_1_Pin LL_GPIO_PIN_10
#define KEY_LED_1_GPIO_Port GPIOC
#define KEY_LED_2_Pin LL_GPIO_PIN_11
#define KEY_LED_2_GPIO_Port GPIOC
#define KEY_LED_3_Pin LL_GPIO_PIN_12
#define KEY_LED_3_GPIO_Port GPIOC
#define LCD_CS_Pin LL_GPIO_PIN_4
#define LCD_CS_GPIO_Port GPIOB
#define LCD_DS_Pin LL_GPIO_PIN_6
#define LCD_DS_GPIO_Port GPIOB
#define LCD_RES_Pin LL_GPIO_PIN_7
#define LCD_RES_GPIO_Port GPIOB
#define BOOT_Pin LL_GPIO_PIN_8
#define BOOT_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
