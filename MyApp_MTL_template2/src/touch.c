/*************************************************
*
* File defining functions for the detection of
* various touch movements on MTL screen
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// INCLUDES ///
#include "frame.h"
#include "touch.h"
#include "geometry.h"

/// CONSTANTS DEFINITION ///


/// VARIABLES DEFINITION ///

/// FUNCTIONS DEFINITION //////
// Touch_getRect: virtually splits the screen in height*width
// rectangles and send in which the coordinates were found
int TOUCH_getRect(POINT screenTouch,int Nheight, int Nwidth)
{
	// Return variable
	int rectNumber = 0;
	int returnVal = 0; // If still at 0 at return statement means touch was not found
	int isInRect = 0;
	RECT subRect = {0,0,0,0};
	
	for(int i=1;i<=Nheight;i++)
	{
		for(int j=1;j<=Nwidth;j++)
		{
			rectNumber++;
			// Check if the touch is in the current rectangle
			RectSet(&subRect,FRAME_WIDTH/Nwidth*(j-1),FRAME_WIDTH/Nwidth*j,FRAME_HEIGHT/Nheight*(i-1),FRAME_HEIGHT/Nheight*i);
			isInRect = IsPtInRect(&screenTouch,&subRect);
			// Check if the current rectangle is the right one
			if(isInRect)
			{
				// go straight to return
				returnVal = rectNumber;
				break;
			}
		}
	}
	return returnVal;
}

//////// Other detection functions may be defined below //////////
