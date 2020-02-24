/*************************************************
*
* Header file for gsensor.c
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// PRE-PROCESSOR LINES ///
#ifndef GSENSOR_H_
#define GSENSOR_H_

/// INCLUDES ///

/// CONSTANTS DEFINITION ///

/// VARIABLES DEFINITION ///

/// FUNCTIONS DEFINITION ///
int XL345init(void);
int XL345read(int *Xaxis, int *Yaxis, int *Zaxis);

#endif
