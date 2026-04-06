/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
bool motorSpin = false;
//bool openDoor = false;
//uint16_t _timer = 300;
//int dx = 1;
//uint8_t _cnt = 0;
//uint8_t mode = 1;
uint8_t tx_buf[256*64/2];
//uint32_t ris = 0;
//uint32_t fal = 0;
bool drill = true;
//uint16_t dacVal;
uint8_t motMode;
uint16_t cntPrevious = 0;
int16_t cntSecond = 0;
int32_t cntDelta = 0;
int32_t drillSpeed = 0;
int32_t tapSpeed = 0;
float drillInc = 0;
float tapInc = 0;

float linePrevious = 0;
float lineSecond = 0;
uint32_t cntLine = 0;
float lineDelta = 0;
float Line = 0;
int32_t realPoz;
float buf;

uint8_t modeCnt = 1;

bool isOrigin = false;
bool isMotorStart = false;
uint8_t tickCnt = 0;

bool rpmChange = true;
bool absChange = false;
bool incChange = false;

bool rpmEdit = false;
bool absEdit = false;
bool incEdit = false;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	motMode = 1;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* System interrupt init*/
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled
  */
  LL_GPIO_AF_Remap_SWJ_NOJTAG();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_DAC_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
	//LL_GPIO_TogglePin(SW2_GPIO_Port,SW2_Pin);
    LL_GPIO_SetOutputPin(DAC_5_10V_GPIO_Port, DAC_5_10V_Pin);
    EC_Init();
    MOT_Init();
    SSD1322_API_init();
    LL_TIM_EnableIT_UPDATE(LCD_TIM);
    LL_TIM_EnableCounter(LCD_TIM);
    LL_TIM_EnableIT_UPDATE(KEY_TIM);
    LL_TIM_EnableCounter(KEY_TIM);
    LL_TIM_EnableIT_UPDATE(MOT_TIM);
    LL_TIM_EnableCounter(MOT_TIM);
    LL_TIM_EnableCounter(TIM2);
    LL_TIM_EnableCounter(TIM3);
    
    //InitGui();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   
	LL_SYSTICK_EnableIT();
	uint8_t br = 0;
    
  while (1)
  {
//    if(){
//        select_font(&FreeMonoBold9pt7b);
//        draw_text(tx_buf, (uint8_t*)"ORIGIN", 35, 30, 15);
//        send_buffer_to_OLED(tx_buf, 0, 0);          
//    }
      
      
    if(drill) {
        LL_GPIO_SetOutputPin(key2Led1.port, key2Led1.pin);
        LL_GPIO_ResetOutputPin(key2Led2.port, key2Led2.pin);
    }
    else {
        LL_GPIO_SetOutputPin(key2Led2.port, key2Led2.pin);
        LL_GPIO_ResetOutputPin(key2Led1.port, key2Led1.pin);
    }
    
    if(isMotorStart) {
        LL_GPIO_SetOutputPin(key1Led.port, key1Led.pin);
    }
    else {
        LL_GPIO_SetOutputPin(key3Led.port, key3Led.pin);
    }
    
    if(isOrigin){
        LL_GPIO_SetOutputPin(key4Led.port, key4Led.pin);
    }
		
    cntSecond = LL_TIM_GetCounter(TIM3)/2;
    cntDelta = cntSecond - cntPrevious;
    cntPrevious = cntSecond;
      
    if(key2.backPulse)
    {
        if(!isMotorStart) {
            drill = !drill;
            modeCnt = 1;
            rpmChange = true;
            absChange = false;
            incChange = false;
            rpmEdit = false;
            absEdit = false;
            incEdit = false;
        }
        
        key2.backPulse = false;
    }
    if(encKey.backPulse)
    {
        if(modeCnt != 2){
            if(modeCnt == 1){
                rpmChange = false;
                rpmEdit = false;
                absChange = true;
            }
            if(modeCnt == 3){
                rpmChange = false;
                absChange = false;
                incChange = false;
                rpmEdit = false;
                absEdit = false;
                incEdit = false;
            }
            
            modeCnt++;
            if(modeCnt > 3) modeCnt = 1;
        }
        encKey.backPulse = false;
    }
    if(key4.backPulse)
    {
        if(modeCnt == 2){
            incChange = true;
            absChange = false;
            modeCnt = 3;
            isOrigin = !isOrigin;
            LL_TIM_SetCounter(TIM2, 0);
        }
        key4.backPulse = false;
    }
    if(cntDelta < 0 )
    {
        if(modeCnt == 1){
            if(drill){
                rpmEdit = true;
                if(drillSpeed < 2000)
                    drillSpeed += 100;
                if(drillSpeed > 2000)
                    drillSpeed = 2000;
            }
            else {
                rpmEdit = true;
                if(tapSpeed < 200)
                    tapSpeed += 10;
                if(tapSpeed > 200)
                    tapSpeed = 200;
            }
            cntDelta = 0;
            rpmEdit = false;
        }
        if(modeCnt == 3){
            if(drill) {
                incEdit = true;
                if(drillInc < 100)
                    drillInc += 0.1;
                if(drillInc > 100)
                    drillInc = 100;
            }
            else {
                incEdit = true;
                if(tapInc < 100)
                    tapInc += 0.1;
                if(tapInc > 100)
                    tapInc = 100; 
            }
            cntDelta = 0;
            incEdit = false;
        }
    }
    if(cntDelta > 0 )
    {
        if(modeCnt == 1){
            if(drill) {
                rpmEdit = true;
                if(drillSpeed > 0)
                    drillSpeed -= 100;
                if(drillSpeed < 0)
                    drillSpeed = 0;
            }
            else {
                rpmEdit = true;
                if(tapSpeed > 0)
                    tapSpeed -= 10;
                if(tapSpeed < 0)
                    tapSpeed = 0;
            }
            cntDelta = 0;
            rpmEdit = false;
        }
        if(modeCnt == 3){
            if(drill) {
                incEdit = true;
                if(drillInc > 0)
                    drillInc -= 0.1;
                if(drillInc < 0)
                    drillInc = 0;
            }
            else {
                incEdit = true;
                if(tapInc > 0)
                    tapInc -= 0.1;
                if(tapInc < 0)
                    tapInc = 0;
            }
            cntDelta = 0;
            incEdit = false;
        }
    }
    MOT_SetSpeed(drillSpeed);
    
    int speed = drill? drillSpeed : tapSpeed;
    
    DrawDrillWidget(drill, tx_buf, 2000, speed, rpmEdit);
    
    cntLine = LL_TIM_GetCounter(TIM2);
    
    if(cntLine > UINT16_MAX/2)
        realPoz = (UINT16_MAX - cntLine)*(-1);
    else
        realPoz = cntLine;
    
    buf = (float)realPoz;
    
    float inc = drill? drillInc : tapInc;
    
    DrawAbsIncWidget(tx_buf, buf, inc, absEdit, incEdit, modeCnt);
  
    DrawCntWidget(tx_buf, 0);
    
    send_buffer_to_OLED(tx_buf, 0, 0);
	//br = ~br;
		//MOT_ChangeDir(1);
	//LL_mDelay(1000);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(72000000);
  LL_SetSystemCoreClock(72000000);
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);
}

/* USER CODE BEGIN 4 */
void InitGui(){
    draw_bitmap_8bpp(tx_buf, &KSP_LOGO, 64, 6, 128, 49);   
    send_buffer_to_OLED(tx_buf, 0, 0); 
    draw_rect_filled(tx_buf, 0, 0, 256, 64, 0);
    for(int i = 0; i < 2; ++i) {
        LL_GPIO_SetOutputPin(key1Led.port, key1Led.pin);
        LL_GPIO_SetOutputPin(key2Led1.port, key2Led1.pin); 
        LL_GPIO_SetOutputPin(key2Led1.port, key2Led2.pin); 
        LL_GPIO_SetOutputPin(key3Led.port, key3Led.pin); 
        LL_GPIO_SetOutputPin(key4Led.port, key4Led.pin); 
        LL_mDelay(1000);
        LL_GPIO_ResetOutputPin(key1Led.port, key1Led.pin);
        LL_GPIO_ResetOutputPin(key2Led1.port, key2Led1.pin); 
        LL_GPIO_ResetOutputPin(key2Led1.port, key2Led2.pin); 
        LL_GPIO_ResetOutputPin(key3Led.port, key3Led.pin); 
        LL_GPIO_ResetOutputPin(key4Led.port, key4Led.pin); 
        LL_mDelay(1000);
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
