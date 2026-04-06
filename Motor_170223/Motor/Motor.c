/*Includes*/
#include "Motor.h"

/*Macro and defines*/

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
	
	MOT_Stop();
	
	motor.speed = 0;
	motor.maxSpeed = 3970;
	motor.dir = FORWARD;
	motor.status = STOPPED;
	
	oldEncVal = LL_TIM_GetCounter(TIM3);
	
	LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);
}
void MOT_Control(void){
	
//	if (motor.cmd == STOP){
//		
//	}
	#warning "Move this to another place"
	newVal = LL_TIM_GetCounter(TIM3);
	delta = newVal - oldEncVal;
	MOT_SetSpeed(motor.speed + delta*100);
	/**/
	
	oldEncVal = newVal;
	
	if (key1.frontPulse){ //Start/stop
		if (motor.status == RUNNING){
			MOT_Stop();
		} else {
			MOT_Start();
		}
		key1.frontPulse = false;
	}
		if (key2.frontPulse){ //Dir
			if (motor.dir == FORWARD){
				MOT_SetDir(REVERSE);
			} else {
				MOT_SetDir(FORWARD);
			}
		
		key2.frontPulse = false;
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
	LL_DAC_ConvertData12RightAligned(DAC,LL_DAC_CHANNEL_1,motor.speed);
}
void MOT_SetDir (dir_t dir){
	if (motor.status == RUNNING){
		if (dir == FORWARD){
			LL_GPIO_SetOutputPin(forwardRK->port, forwardRK->pin);
			LL_GPIO_ResetOutputPin(reverseRK->port, reverseRK->pin);
		} else {
			LL_GPIO_ResetOutputPin(forwardRK->port, forwardRK->pin);
			LL_GPIO_SetOutputPin(reverseRK->port, reverseRK->pin);
		}
	}
	motor.dir = dir;
	
}
void MOT_Start (void){
	motor.status = RUNNING;
	MOT_SetDir(motor.dir);
	LL_DAC_ConvertData12RightAligned(DAC,LL_DAC_CHANNEL_1, motor.speed);
	
}
void MOT_Stop (void){
	LL_GPIO_ResetOutputPin(forwardRK->port, forwardRK->pin);
	LL_GPIO_ResetOutputPin(reverseRK->port, reverseRK->pin);
	motor.status = STOPPED;
}