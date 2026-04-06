#ifndef _COEF_H_
#define _COEF_H_

/*Uncomment for the required hardware configuration*/
//#define CM_PROP
#define CS_PROP

#include "main.h"

#ifdef CM_PROP

#define MINIMUM_RPM 800
#define MAXIMUM_RPM 6000

#endif

#ifdef CS_PROP

#define MINIMUM_RPM 100
#define MAXIMUM_RPM 4000

#endif

#endif