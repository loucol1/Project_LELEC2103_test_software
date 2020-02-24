/*************************************************
*
* Template code with simple display functions
* given input touch coordinates
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// INCLUDES ///

#include <inttypes.h>

#include "../painter/terasic_lib/terasic_includes.h"
#include "../painter/vip_fr.h"
#include "../painter/graphic_lib/simple_graphics.h"
#include "../painter/frame.h"
#include "../painter/geometry.h"
#include "../painter/gesture.h"

#include "alt_clock_manager.h"
#include "alt_timers.h"
#include "alt_globaltmr.h"

/// LOCAL MACROS ///
#define NELEM(x)	(sizeof(x)/sizeof((x)[0]))

/// LOCAL TYPES DEFINITION ///
alt_u32 colorsVec[] = {
    BLACK_24,
    WHITE_24,
    0xF0F0F0,
    0x0000FF,
    0x00FF00,
    0xFF0000,
    0x00FFFF,
    0xFFFF00,
    0xFF00FF
    //0x7F7F7F
};


typedef struct{
    RECT rc;
    int  color;
} COLORED_RECT;

/// CONSTANTS DEFINITION ///

/// VARIABLES DEFINITION ///
 
// Create colored rectangles
COLORED_RECT rect1 = {{0,0,0,0},3};
COLORED_RECT rect2 = {{0,0,0,0},4};
COLORED_RECT rect3 = {{0,0,0,0},5};
COLORED_RECT rect4 = {{0,0,0,0},6};

/// FUNCTIONS DEFINITION ///
// GUI_simpleColorInit: initialize the screen display with the specified rectangles and colors
void GUI_simpleColorInit(VIP_FRAME_READER *pReader)
{
	// Set rectangles size and color
	RectSet(&rect1.rc,0,FRAME_WIDTH/2,0,FRAME_HEIGHT/2); 							//rect1.color = colorsVec[0];
	RectSet(&rect2.rc,FRAME_WIDTH/2+1,FRAME_WIDTH,0,FRAME_HEIGHT/2); 				//rect2.color = colorsVec[1];
	RectSet(&rect3.rc,0,FRAME_WIDTH/2,FRAME_HEIGHT/2+1,FRAME_HEIGHT); 				//rect3.color = colorsVec[1];
	RectSet(&rect4.rc,FRAME_WIDTH/2+1,FRAME_WIDTH,FRAME_HEIGHT/2+1,FRAME_HEIGHT); 	//rect4.color = colorsVec[0];

	// Display these initial rectangles
	vid_draw_box(rect1.rc.left, rect1.rc.top, rect1.rc.right, rect1.rc.bottom, colorsVec[rect1.color], DO_FILL, pReader);
	vid_draw_box(rect2.rc.left, rect2.rc.top, rect2.rc.right, rect2.rc.bottom, colorsVec[rect2.color], DO_FILL, pReader);
	vid_draw_box(rect3.rc.left, rect3.rc.top, rect3.rc.right, rect3.rc.bottom, colorsVec[rect3.color], DO_FILL, pReader);
	vid_draw_box(rect4.rc.left, rect4.rc.top, rect4.rc.right, rect4.rc.bottom, colorsVec[rect4.color], DO_FILL, pReader);
}

// GUI_simpleColorPrint: modify the color of the rectangles on screen based on the user input touch
void GUI_simpleColorPrint(VIP_FRAME_READER *pReader, int touchZone)
{
	// Update the rectangle color based on the touched zone on the screen
	switch(touchZone)
	{
		case 1:
			if(rect1.color == NELEM(colorsVec))
				rect1.color = 0; // Don't bypass white and black
			else
				rect1.color += 1;
			vid_draw_box(rect1.rc.left, rect1.rc.top, rect1.rc.right, rect1.rc.bottom, colorsVec[rect1.color], DO_FILL, pReader);
			break;
		case 2:
			if(rect2.color == NELEM(colorsVec))
				rect2.color = 2; // We bypass white and black
			else
				rect2.color += 1;
			vid_draw_box(rect2.rc.left, rect2.rc.top, rect2.rc.right, rect2.rc.bottom, colorsVec[rect2.color], DO_FILL, pReader);
			break;
		case 3:
			if(rect3.color == NELEM(colorsVec))
				rect3.color = 0; // Don't bypass white and black
			else
				rect3.color += 1;
			vid_draw_box(rect3.rc.left, rect3.rc.top, rect3.rc.right, rect3.rc.bottom, colorsVec[rect3.color], DO_FILL, pReader);
			break;
		case 4:
			if(rect4.color == NELEM(colorsVec))
				rect4.color = 2; // We bypass white and black
			else
				rect4.color += 1;
			vid_draw_box(rect4.rc.left, rect4.rc.top, rect4.rc.right, rect4.rc.bottom, colorsVec[rect4.color], DO_FILL, pReader);
			break;
		default: break;// NOTHING GETS UPDATED HERE
	}
}

// Update_image: local function used here in completeColorPrint
void Update_image(VIP_FRAME_READER *pReader,alt_u8 *pDesStart, int BmpH, int BmpW, int pixel)
{
	// Local variables
	int x; int y;
	alt_u8 *pDes;

	// Write a same input pixel over the whole BmpH x BmpW image
	for(y=0;y<BmpH;y++){
		pDes = pDesStart;
		for(x=0;x<BmpW;x++){
			*pDes = pixel;

			pDes += 4; // 4 bytes per pixel for the frame buffer
		}
		pDesStart += pReader->width*pReader->bytes_per_pixel;
	}
}

// GUI_completeColorPrint: same function as GUI_simpleColorPrint, without using pre-defined functions
void GUI_completeColorPrint(VIP_FRAME_READER *pReader, int touchZone)
{
	// Each rectangle has size (FRAME_HEIGHT/2,FRAME_WIDTH/2)
	const int BmpH = FRAME_HEIGHT/2;
	const int BmpW = FRAME_WIDTH/2;

	alt_u8 *pDesStart;
	
	switch(touchZone)
	{
		case 1: pDesStart =  (alt_u8 *) VIPFR_GetDrawFrame(pReader) + (0*pReader->width*pReader->bytes_per_pixel) + (0*pReader->bytes_per_pixel);
				if(rect1.color == NELEM(colorsVec))
					rect1.color = 2; // We bypass white and black
				else
					rect1.color += 1;
				Update_image(pReader,pDesStart,BmpH,BmpW,rect1.color);
				break;
		case 2: pDesStart =  (alt_u8 *) VIPFR_GetDrawFrame(pReader) + ((FRAME_HEIGHT/2)*pReader->width*pReader->bytes_per_pixel) + (0*pReader->bytes_per_pixel);
				if(rect2.color == NELEM(colorsVec))
					rect2.color = 2; // We bypass white and black
				else
					rect2.color += 1;
				Update_image(pReader,pDesStart,BmpH,BmpW,rect2.color);
				break;
		case 3: pDesStart =  (alt_u8 *) VIPFR_GetDrawFrame(pReader) + (0*pReader->width*pReader->bytes_per_pixel) + ((FRAME_WIDTH/2)*pReader->bytes_per_pixel);
				if(rect3.color == NELEM(colorsVec))
					rect3.color = 2; // We bypass white and black
				else
					rect3.color += 1;
				Update_image(pReader,pDesStart,BmpH,BmpW,rect3.color);
				break;
		case 4: pDesStart =  (alt_u8 *) VIPFR_GetDrawFrame(pReader) + ((FRAME_HEIGHT/2)*pReader->width*pReader->bytes_per_pixel) + ((FRAME_WIDTH/2)*pReader->bytes_per_pixel);
				if(rect4.color == NELEM(colorsVec))
					rect4.color = 2; // We bypass white and black
				else
					rect4.color += 1;
				Update_image(pReader,pDesStart,BmpH,BmpW,rect4.color);
				break;
		default: pDesStart = (alt_u8 *) VIPFR_GetDrawFrame(pReader); break; // Should not happen
	}
}
