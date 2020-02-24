//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////// SOFTWARE README ////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

This README file describes the structure of the template software provided and how to switch from MTL-1 to MTL-2
libraries by changing but 2 variables.

1. /// Software structure ///

The provided template consists in a full DS-5 project for using the MTL screen within the mAbassi OS framework.
The folder structure is as follows:
- /src: contains the main file main_mAbassi.c as well as the top-level sofware file myApp_MTL.c. It also
	provides custom files with display and touch functions used by the template application.
- /inc: contains the main header myApp_MTL.h and the hardware description header hps_0.h
- /painter: contains custom and ip display and touch libraries.
- /hwlib: contains useful hardware-related libraries (do not touch).
- /preloader: contains scripts called by the debugger (do not touch).
- /output: contains the header Makefile called during compilation as well as the different outputs.

Besides, file MyApp_MTL_template_GCC.make, called by the Makefile, allows you to update your list of compiled
and referenced files. Path variables in this file should be adapted to your installation.

2. /// MTL-type choice ///

Depending on whether you have an MTL-1 or MTL-2 screen, you should properly set compilation flags to reference
the adequate software libraries. Do not forget to load the proper hardware onto your FPGA first !

You should update the following flags:
- In file MyApp_MTL_template_GCC.make, choose 1 or 2 for variable MTL_TYPE depending on your screen type.
- In file inc/myApp_MTL.h, comment the definition of the pre-processor constant IS_MTL2 if you have an MTL 1 screen.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// THAT'S IT, YOU'RE READY TO GO ! //////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
