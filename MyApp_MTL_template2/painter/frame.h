/*************************************************
*
* Header file with frame information
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// PRE-PROCESSOR LINES ///
#ifndef FRAME_H_
#define FRAME_H_

/// INCLUDES ///

/// CONSTANTS DEFINITION ///

// Frame buffer information
#define FR_FRAME_0  0x20000000
#define FR_FRAME_1 (0x20000000 + FRAME_WIDTH*FRAME_HEIGHT*4)
// MTL screen size
#define FRAME_WIDTH  800
#define FRAME_HEIGHT 480

#endif
