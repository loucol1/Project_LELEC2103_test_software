/*************************************************
*
* Custom library for Gsensor usage
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// INCLUDES ///
#include "mAbassi.h"
#include "Platform.h"
#include "HWinfo.h"
#include "SysCall.h"

#include "../painter/terasic_lib/terasic_includes.h"

/// FUNCTIONS VARIABLES ///

/// FUNCTIONS DEFINITION ///
// Initialize the Gsensor //
int XL345init(void)
{
char Buffer[2];
int  RetVal;

	Buffer[0]  = XL345_REG_DATA_FORMAT;
	Buffer[1]  = (XL345_RANGE_2G)					/* +- 2G range, 10 bit resolution				*/
	           | (XL345_FULL_RESOLUTION);			/* This delivers results of 4mg per bit			*/
	RetVal     = i2c_send(I2C_XL345_DEVICE, I2C_XL345_ADDR, &Buffer[0], 2);

	Buffer[0]  = XL345_REG_BW_RATE;
	Buffer[1]  = XL345_RATE_3200;					/* Conversion rate is 12.5 Hz (once every 80ms)	*/
	RetVal    |= i2c_send(I2C_XL345_DEVICE, I2C_XL345_ADDR, &Buffer[0], 2);

	Buffer[0]  = XL345_REG_INT_ENABLE;
	Buffer[1]  = XL345_DATAREADY;					/* Enable the interrupt for data ready			*/
	RetVal    |= i2c_send(I2C_XL345_DEVICE, I2C_XL345_ADDR, &Buffer[0], 2);

	Buffer[0]  = XL345_REG_POWER_CTL;
	Buffer[1]  = XL345_STANDBY;						/* Stop the measurements						*/
	RetVal    |= i2c_send(I2C_XL345_DEVICE, I2C_XL345_ADDR, &Buffer[0], 2);

 	return(RetVal);
}

// Read data from the Gsensor //
int XL345read(int *Xaxis, int *Yaxis, int *Zaxis)
{
char Buffer[7];
int  RetVal;

	Buffer[0]  = XL345_REG_POWER_CTL;
	Buffer[1]  = XL345_MEASURE;						/* Start the measurements						*/
	RetVal     = i2c_send(I2C_XL345_DEVICE, I2C_XL345_ADDR, &Buffer[0], 2);

	TSKsleep(OS_MS_TO_TICK(10));					/* Wait for the measurement to be done			*/

	do {											/* Check to make sure is done					*/
		Buffer[0] = XL345_REG_INT_SOURCE;
		RetVal = i2c_send_recv(I2C_XL345_DEVICE, I2C_XL345_ADDR, &Buffer[0], 1, &Buffer[0], 1);
	} while (((XL345_DATAREADY & (int)Buffer[0]) == 0)
	  &&      (RetVal == 0));

	Buffer[0] = 0x32;								/* Read the data; *4 because 0.004g/bit			*/
	RetVal |= i2c_send_recv(I2C_XL345_DEVICE, I2C_XL345_ADDR, &Buffer[0], 1, &Buffer[0], 6);

	if (RetVal == 0) {
		*Xaxis = 4*((((int)(signed char)Buffer[1])<<8) + (0xFF & ((int)Buffer[0])));
		*Yaxis = 4*((((int)(signed char)Buffer[3])<<8) + (0xFF & ((int)Buffer[2])));
		*Zaxis = 4*((((int)(signed char)Buffer[5])<<8) + (0xFF & ((int)Buffer[4])));
	}

	Buffer[0]  = XL345_REG_POWER_CTL;
	Buffer[1]  = XL345_STANDBY;						/* Stop the measurements						*/
	RetVal |= i2c_send(I2C_XL345_DEVICE, I2C_XL345_ADDR, &Buffer[0], 2);

	return(RetVal);
}
