/*************************************************
*
* Header file for gui.c
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// PRE-PROCESSOR LINES ///
#ifndef GUI_H_
#define GUI_H_

/// INCLUDES ///
#include "vip_fr.h"

/// CONSTANTS & MACRO DEFINITION ///

/// VARIABLES DEFINITION ///

/// FUNCTIONS DEFINITION //////
void GUI_simpleColorInit(VIP_FRAME_READER *pReader);
void GUI_simpleColorPrint(VIP_FRAME_READER *pReader, int touchZone);
void GUI_completeColorPrint(VIP_FRAME_READER *pReader, int touchZone);


#endif

