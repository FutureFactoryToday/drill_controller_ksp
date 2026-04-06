#ifndef _RULLER_H_
#define _RULLER_H_
	#include "main.h"
	extern int32_t relativePosition;
	extern int32_t relMM, relUM;
	void RUL_modifRelativePosition(int16_t poz);
	void RUL_convertIntToMM(void);
#endif
