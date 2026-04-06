#ifndef _MOTOR_H_
#define _MOTOR_H_

/*Includes*/
#include "main.h"
//#define RK_TYPE_HIGH
#define RK_TYPE_LOW
/*Typedef*/
typedef struct{
	GPIO_TypeDef* port;
	uint32_t pin;
} gpio_t;

typedef enum {
	START = 0,
	STOP
} mot_cmd_t;

typedef enum {
	FORWARD = 0,
	REVERSE
} dir_t;

typedef enum {
	RUNNING,
	STOPPED, 
	STROLLING
} mot_status_t;

typedef struct {
	int32_t speed; //Volts
	uint16_t maxSpeed; //Volts
	dir_t dir;
	mot_status_t status;
	mot_cmd_t cmd;
} mot_param_t;







/*Extern parameters*/
extern mot_param_t motor;
/*Prototypes*/
void MOT_Control(void);
void MOT_SetSpeed(int16_t speed);
void MOT_SetDir (dir_t dir);
void MOT_Start (void);
void MOT_Stop (void);
void MOT_Init(void);
#endif //_MOTOR_H_