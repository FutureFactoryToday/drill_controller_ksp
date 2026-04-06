/*Includes*/
#include "Motor.h"

/*Macro and defines*/
/*SETTINGS*/
#if defined (STM32F103xB)
#define MODBUS_CONTROL
#else 
#define MODBUS_CONTROL
#define DAC_CONTROL
#endif

/*MODBUS settings*/
#define MOT_ADR 0x01
#define CONTROL_REG 0x2000
#define STATUS_REG 0x6000
#define SPEED_REG 0x3000

#define MOT_STOP 0x0005
#define SPIN_FORWARD 0x0001
#define SPIN_BACKWARD 0x0002

/*MODBUS settings*/
#if defined (DAC_CONTROL)
	#define MOT_MAX_SPEED 3970 //Volts
#else
	#define MOT_MAX_SPEED 6000 //(60 / 0.01)Hz
#endif

/*Global parameters*/
mot_param_t motor, oldMotor;
gpio_t rk1low, rk2low, rk3low, rk4low, rk1hg, rk2hg, rk3hg, rk4hg;
gpio_t *forwardRK, *reverseRK;
int16_t oldEncVal;
int16_t newVal;
int32_t delta;
/*Local prototypes*/

/*Code*/
void MOT_Init(void){
	#if defined (DAC_CONTROL)
	rk1low.port = RK_LOW_1_GPIO_Port;
	rk1low.pin = RK_LOW_1_Pin;

	rk2low.port = RK_LOW_2_GPIO_Port;
	rk2low.pin = RK_LOW_2_Pin;

	rk3low.port = RK_LOW_3_GPIO_Port;
	rk3low.pin = RK_LOW_3_Pin;

	rk4low.port = RK_LOW_4_GPIO_Port;
	rk4low.pin = RK_LOW_4_Pin;
	
	rk1hg.port = RK_HIGH_1_GPIO_Port;
	rk1hg.pin = RK_HIGH_1_Pin;

	rk2hg.port = RK_HIGH_2_GPIO_Port;
	rk2hg.pin = RK_HIGH_2_Pin;

	rk3hg.port = RK_HIGH_3_GPIO_Port;
	rk3hg.pin = RK_HIGH_3_Pin;

	rk4hg.port = RK_HIGH_4_GPIO_Port;
	rk4hg.pin = RK_HIGH_4_Pin;
	
	#if defined (RK_TYPE_HIGH)
	forwardRK = &rk1hg;
	reverseRK = &rk2hg;
	#endif
	
	#if defined (RK_TYPE_LOW)
	forwardRK = &rk1low;
	reverseRK = &rk2low;
	#endif
	#else
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0001,0x02); //SD0.01, 2 (Modbus)
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0003,MOT_MAX_SPEED); //SD0.03, 60 Hz
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0004,MOT_MAX_SPEED); //SD0.04, 60 Hz
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0006,0x08); //SD0.06, 8 (Modbus)
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x000E,0); //SD0.14, 0 Normal spinning
	
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0201,0); //SD2.01, 0 (Async motor)
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0202,11); //SD2.02, 1.1 kW 
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0203,400); //SD2.03, 400 V
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0204,23); //SD2.04, 2.3A 
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0205,MOT_MAX_SPEED); //SD2.05, MOT_MAX_SPEED
	mmodbus_writeHoldingRegister16i(MOT_ADR,0x0206,3330); //SD2.06, 
	#endif
	MOT_Stop();
	
	oldEncVal = LL_TIM_GetCounter(TIM3);
	
	
	motor.speed = 0;
	
	motor.dir = FORWARD;
	motor.status = STOPPED;	
	motor.maxSpeed = MOT_MAX_SPEED;
	
	#if defined (DAC_CONTROL)
	LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);
	#endif
}
void MOT_Control(void){
	
//	if (motor.cmd == STOP){
//		
//	}
//	#warning "Move this to another place"
//	newVal = LL_TIM_GetCounter(TIM3);
//	delta = newVal - oldEncVal;
//	MOT_SetSpeed(motor.speed + delta*100);
//	/**/
//	
//	oldEncVal = newVal;
	
    if(keySpindleStart.backPulse)
    {
        MOT_Start();
        keySpindleStart.backPulse = false;
    }
    if(keySpindleStop.backPulse)
    {
        MOT_Stop();
        keySpindleStop.backPulse = false;
    }
}

void MOT_SetSpeed(int16_t speed){
//	if (speed >= 0){
		motor.speed = speed;
		if (motor.speed < 0){
			motor.speed = 0;
		}
		if (motor.speed > motor.maxSpeed){
			motor.speed = motor.maxSpeed;
		}
//	}
		#if defined (DAC_CONTROL)	
		LL_DAC_ConvertData12RightAligned(DAC,LL_DAC_CHANNEL_1,motor.speed);
		#else
		mmodbus_writeHoldingRegister16i(MOT_ADR,SPEED_REG,100*motor.speed/60); // rot/min /60 sec /0.01
		#endif
}
void MOT_SetDir (dir_t dir){
	if (motor.status == RUNNING){
		if (dir == FORWARD){
			#if defined (DAC_CONTROL)
			LL_GPIO_SetOutputPin(forwardRK->port, forwardRK->pin);
			LL_GPIO_ResetOutputPin(reverseRK->port, reverseRK->pin);
			#else 
			mmodbus_writeHoldingRegister16i(MOT_ADR,CONTROL_REG,SPIN_FORWARD);
			#endif
		} else {
			#if defined (DAC_CONTROL)
			LL_GPIO_ResetOutputPin(forwardRK->port, forwardRK->pin);
			LL_GPIO_SetOutputPin(reverseRK->port, reverseRK->pin);
			#else 
			mmodbus_writeHoldingRegister16i(MOT_ADR,CONTROL_REG,SPIN_BACKWARD);
			#endif
		}
	}
	motor.dir = dir;
	
}
void MOT_Start (void){
	motor.status = RUNNING;
	MOT_SetDir(motor.dir);
#if defined (DAC_CONTROL)
	LL_DAC_ConvertData12RightAligned(DAC,LL_DAC_CHANNEL_1, motor.speed);
#endif
	
}
void MOT_Stop (void){
#if defined (DAC_CONTROL)
	LL_GPIO_ResetOutputPin(forwardRK->port, forwardRK->pin);
	LL_GPIO_ResetOutputPin(reverseRK->port, reverseRK->pin);
#else 
	mmodbus_writeHoldingRegister16i(MOT_ADR,CONTROL_REG,MOT_STOP);
#endif
	motor.status = STOPPED;
}