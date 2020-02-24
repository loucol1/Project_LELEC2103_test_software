/*************************************************
*
* Header file for touch.c
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// PRE-PROCESSOR LINES ///
#ifndef TOUCH_H_
#define TOUCH_H_

/// INCLUDES ///
#include "../painter/geometry.h"
#include "../painter/terasic_lib/terasic_includes.h"
#ifdef IS_MTL2
	#include "../painter/terasic_lib/multi_touch.h"
#else
	#include "../painter/terasic_lib/multi_touch2.h"
#endif

/// CONSTANTS & MACROS DEFINITION ///

/// VARIABLES DEFINITION ///

/// FUNCTIONS DEFINITION //////
int TOUCH_getRect(POINT screenTouch, int height, int width);

#endif
