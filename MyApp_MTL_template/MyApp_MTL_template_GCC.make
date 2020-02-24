#
# File: MyApp_MTL_template_GCC.make
#
# Copyright (c) 2017-2018, Code-Time Technologies Inc.
# All rights reserved.
#

# NOTE:
# This Makefile includes "Common_GCC.make" which contains the common part of all makefiles
# It is done to simplify the work needed when something is changed for a target or for a demo #
#
# The symbol _STANDALONE_ is defined to build bare-metal apps although uAbassi is used and _UABASSI_
# is also defined.  _STANDALONE_ is only used in the drivers to select the RTOS/SAL include file and
# because it is the first conditional in a sequence of preprocessor ifs, it take precedence
# This configures the drivers to use the SAL RTO Sspoofing code instead fi uAbassi
# Refer to BareMetalApps.c for a more detailled dsescription
# ----------------------------------------------------------------------------------------------------

MAKE_NAME := MyApp_MTL_template_GCC.make            # For full re-build if I'm modified

# MTL type (select 1 or 2)
MTL_TYPE := 1
# Path to mAbassi folder. You may want to update it
PATH_TO_ABASSI := ../../
# PATHS FOR BUILD VARIABLES
SOCEDS_DEST_ROOT := C:/intelFPGA/18.1/embedded
FATFS        := ${PATH_TO_ABASSI}/mAbassi/FatFS-0.13a
LWIP         := ${PATH_TO_ABASSI}/mAbassi/lwip-1.4.1
LWIPIF       := ${PATH_TO_ABASSI}/mAbassi/lwip-if

# The path order of in VPATH is important
VPATH   := ../src                            # This is due to multiple file with same names
VPATH   += :../hwlib
VPATH   += :../painter
VPATH   += :../painter/fonts
VPATH   += :../painter/graphic_lib
VPATH   += :../painter/terasic_lib
VPATH   += :$(LWIPIF)/Abassi
VPATH   += :$(LWIPIF)/dw/RTOS
VPATH   += :${PATH_TO_ABASSI}/mAbassi/Abassi
VPATH   += :${PATH_TO_ABASSI}/mAbassi/Platform/src
VPATH   += :${PATH_TO_ABASSI}/mAbassi/Drivers/src
VPATH   += :${PATH_TO_ABASSI}/mAbassi/Share/src
VPATH   += :$(FATFS)/src
VPATH   += :$(FATFS)/src/option
VPATH   += :$(LWIP)/src/api
VPATH   += :$(LWIP)/src/core
VPATH   += :$(LWIP)/src/core/ipv4
VPATH   += :$(LWIP)/src/netif

C_SRC   :=                                    # C sources with/without thumb (see THUMB above)
C_SRC   += main_mAbassi.c
C_SRC   += myApp_MTL.c

C_SRC   += TIMERinit.c
C_SRC   += alt_gpio.c
C_SRC   += arm_acp.c
C_SRC   += arm_pl330.c
C_SRC   += dw_i2c.c
C_SRC   += dw_uart.c
C_SRC   += MediaIF.c
C_SRC   += SysCall_CY5.c
C_SRC   += dw_sdmmc.c

C_SRC   += ff.c
C_SRC   += ffunicode.c
C_SRC   += Abassi_FatFS.c
C_SRC   += Media_FatFS.c
C_SRC   += SysCall_FatFS.c

C_SRC   += tahomabold_20.c
C_SRC   += tahomabold_32.c
C_SRC	+= geometry.c
C_SRC   += gesture.c
C_SRC   += gui.c
C_SRC   += vip_fr.c
C_SRC	+= simple_graphics.c
C_SRC	+= simple_text.c
C_SRC	+= debug.c
C_SRC	+= queue.c
C_SRC   += gsensor.c
C_SRC	+= touch.c
# /// MTL-dependent includes ///
ifeq ($(MTL_TYPE),2)
	C_SRC	+= ../painter/terasic_lib/I2C.c
	C_SRC	+= ../painter/terasic_lib/I2C_core.c
	C_SRC	+= ../painter/terasic_lib/multi_touch2.c
else ifeq ($(MTL_TYPE),1)
	C_SRC	+= ../painter/terasic_lib/multi_touch.c
else
	# Launch error
endif

C_SRC   += alt_generalpurpose_io.c
C_SRC   += alt_globaltmr.c
C_SRC   += alt_clock_manager.c

C_SRC	+= netif_setup.c
C_SRC   += dw_ethernet.c
C_SRC   += api_lib.c
C_SRC   += api_msg.c
C_SRC   += autoip.c
C_SRC   += def.c
C_SRC   += dhcp.c
C_SRC   += dns.c
C_SRC   += err.c
C_SRC   += etharp.c
C_SRC   += ethernetif.c
C_SRC   += icmp.c
C_SRC   += igmp.c
C_SRC   += inet.c
C_SRC   += inet_chksum.c
C_SRC   += init.c
C_SRC   += ip.c
C_SRC   += ip_addr.c
C_SRC   += ip_frag.c
C_SRC   += mem.c
C_SRC   += memp.c
C_SRC   += netbuf.c
C_SRC   += netdb.c
C_SRC   += netif.c
C_SRC   += netifapi.c
C_SRC   += pbuf.c
C_SRC   += raw.c
C_SRC   += stats.c
C_SRC   += sys.c
C_SRC   += sys_arch.c
C_SRC	+= sockets.c
C_SRC   += tcp.c
C_SRC   += tcp_in.c
C_SRC   += tcp_out.c
C_SRC   += tcpip.c
C_SRC   += timers.c
C_SRC   += udp.c

# Assembly files
S_SRC   :=
# Object files
O_SRC   :=

AFLAGS   :=
CFLAGS   :=
LFLAGS   :=
LIBS     :=

# ----------------------------------------------------------------------------------------------------

C_INC   :=                                     # All "C" include files for dependencies
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Abassi/mAbassi.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Abassi/SysCall.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Platform/inc/Platform.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Platform/inc/HWinfo.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Platform/inc/AbassiLib.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Drivers/inc/alt_gpio.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Drivers/inc/arm_acp.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Drivers/inc/arm_pl330.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Drivers/inc/dw_i2c.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Drivers/inc/dw_uart.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Drivers/inc/dw_ethernet.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Drivers/inc/MediaIF.h

C_INC   += $(FATFS)/inc/diskio.h
C_INC   += $(FATFS)/inc/ff.h
C_INC   += $(FATFS)/inc/integer.h
C_INC   += ${PATH_TO_ABASSI}/mAbassi/Share/inc/ffconf.h

C_INC   += ${PATH_TO_ABASSI}/mAbassi/Drivers/inc/dw_sdmmc.h

C_INC	+= ../inc/myApp_MTL.h
C_INC   += ../inc/hps_0.h
C_INC   += ../inc/netif_setup.h

C_INC   += ../painter/geometry.h
C_INC   += ../painter/gesture.h
C_INC   += ../painter/vip_fr.h
C_INC   += ../painter/fonts/fonts.h
C_INC   += ../painter/graphic_lib/simple_graphics.h
C_INC   += ../painter/graphic_lib/simple_text.h
C_INC   += ../painter/terasic_lib/debug.h
C_INC   += ../painter/terasic_lib/queue.h
C_INC   += ../painter/terasic_lib/terasic_includes.h
C_INC   += ../src/gui.h
C_INC   += ../src/gsensor.h
# /// MTL-dependent includes
ifeq ($(MTL_TYPE),2)
	C_INC	+= ../painter/terasic_lib/I2C_core.h
	C_INC	+= ../painter/terasic_lib/I2C.h
	C_INC	+= ../painter/terasic_lib/multi_touch2.h
else ifeq ($(MTL_TYPE),1)
	C_INC	+= ../painter/terasic_lib/multi_touch.h
else
	# Launch error
endif

C_INC   += ${PATH_TO_ABASSI}/mAbassi/Share/inc/lwipopts.h
C_INC   += $(LWIPIF)/Abassi/sys_arch.h
C_INC   += $(LWIPIF)/dw/RTOS/ethernetif.h
C_INC   += $(LWIP)/src/include/lwip/api.h
C_INC   += $(LWIP)/src/include/lwip/api_msg.h
C_INC   += $(LWIP)/src/include/lwip/arch.h
C_INC   += $(LWIP)/src/include/lwip/debug.h
C_INC   += $(LWIP)/src/include/lwip/def.h
C_INC   += $(LWIP)/src/include/lwip/dhcp.h
C_INC   += $(LWIP)/src/include/lwip/dns.h
C_INC   += $(LWIP)/src/include/lwip/err.h
C_INC   += $(LWIP)/src/include/lwip/init.h
C_INC   += $(LWIP)/src/include/lwip/mem.h
C_INC   += $(LWIP)/src/include/lwip/memp.h
C_INC   += $(LWIP)/src/include/lwip/memp_std.h
C_INC   += $(LWIP)/src/include/lwip/netbuf.h
C_INC   += $(LWIP)/src/include/lwip/netdb.h
C_INC   += $(LWIP)/src/include/lwip/netif.h
C_INC   += $(LWIP)/src/include/lwip/netifapi.h
C_INC   += $(LWIP)/src/include/lwip/opt.h
C_INC   += $(LWIP)/src/include/lwip/pbuf.h
C_INC   += $(LWIP)/src/include/lwip/raw.h
C_INC   += $(LWIP)/src/include/lwip/sio.h
C_INC   += $(LWIP)/src/include/lwip/sockets.h
C_INC   += $(LWIP)/src/include/lwip/snmp.h
C_INC   += $(LWIP)/src/include/lwip/snmp_asn1.h
C_INC   += $(LWIP)/src/include/lwip/snmp_msg.h
C_INC   += $(LWIP)/src/include/lwip/snmp_structs.h
C_INC   += $(LWIP)/src/include/lwip/sys.h
C_INC   += $(LWIP)/src/include/lwip/tcp.h
C_INC   += $(LWIP)/src/include/lwip/tcp_impl.h
C_INC   += $(LWIP)/src/include/lwip/tcpip.h
C_INC   += $(LWIP)/src/include/lwip/timers.h
C_INC   += $(LWIP)/src/include/lwip/udp.h
C_INC   += $(LWIP)/src/include/ipv4/lwip/autoip.h
C_INC   += $(LWIP)/src/include/ipv4/lwip/icmp.h
C_INC   += $(LWIP)/src/include/ipv4/lwip/igmp.h
C_INC   += $(LWIP)/src/include/ipv4/lwip/inet.h
C_INC   += $(LWIP)/src/include/ipv4/lwip/inet_chksum.h
C_INC   += $(LWIP)/src/include/ipv4/lwip/ip.h
C_INC   += $(LWIP)/src/include/ipv4/lwip/ip_addr.h
C_INC   += $(LWIP)/src/include/ipv4/lwip/ip_frag.h
C_INC   += $(LWIP)/src/include/netif/etharp.h
C_INC   += $(LWIP)/src/include/netif/ppp_oe.h
C_INC   += $(LWIP)/src/include/netif/slipif.h

# Compiler command line options. The -I order is important
CFLAGS  += -g -O3 -Wall
CFLAGS  += -I ../inc
CFLAGS  += -I ../painter
CFLAGS  += -I ../painter/fonts
CFLAGS  += -I ../painter/graphic_lib
CFLAGS  += -I ../painter/terasic_lib

CFLAGS  += -I${PATH_TO_ABASSI}/mAbassi/Abassi
CFLAGS  += -I${PATH_TO_ABASSI}/mAbassi/Platform/inc
CFLAGS  += -I${PATH_TO_ABASSI}/mAbassi/Drivers/inc
CFLAGS  += -I${PATH_TO_ABASSI}/mAbassi/Share/inc

CFLAGS  += -I$(FATFS)/inc
CFLAGS  += -I../../Drivers/inc

CFLAGS  += -I ${SOCEDS_DEST_ROOT}/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av
CFLAGS  += -I ${SOCEDS_DEST_ROOT}/ip/altera/hps/altera_hps/hwlib/include

CFLAGS  += -DOS_START_STACK=8192
CFLAGS  += -DOS_SYS_CALL=1
CFLAGS  += -DSYS_CALL_DEV_I2C=1
CFLAGS  += -DSYS_CALL_DEV_TTY=1
CFLAGS  += -DSYS_CALL_TTY_EOF=4
CFLAGS  += -DI2C_DEBUG=0
CFLAGS  += -DI2C_OPERATION=0x00707
CFLAGS  += -DI2C_USE_MUTEX=1
CFLAGS  += -DMEDIA_DEBUG=1
CFLAGS  += -DSDMMC_BUFFER_TYPE=SDMMC_BUFFER_CACHED
CFLAGS  += -DSDMMC_NUM_DMA_DESC=64
CFLAGS  += -DSDMMC_USE_MUTEX=1
CFLAGS  += -DUART_FULL_PROTECT=1
CFLAGS  += -DMEDIA_MDRV_SIZE=-1
CFLAGS  += -D_VOLUMES=2
CFLAGS  += -DSYS_CALL_N_DRV=2
CFLAGS  += -DMEDIA_AUTO_SELECT=0
CFLAGS  += -DMEDIA_SDMMC0_IDX=0
CFLAGS  += -DMEDIA_SDMMC0_DEV=SDMMC_DEV
CFLAGS  += -DMEDIA_MDRV_IDX=1
CFLAGS  += -DDEMO_USE_SDMMC=1

CFLAGS  += -D soc_cv_av
CFLAGS  += -D MYAPP_MTL

CFLAGS  += -I$(LWIPIF)
CFLAGS  += -I$(LWIPIF)/dw/RTOS
CFLAGS  += -I$(LWIPIF)/Abassi
CFLAGS  += -I$(LWIP)/src/include
CFLAGS  += -I$(LWIP)/src/include/lwip
CFLAGS  += -I$(LWIP)/src/include/ipv4
CFLAGS  += -I$(LWIP)/src/include/netif

CFLAGS  += -DLWIP_SOCKET=1
CFLAGS	+= -DETH_DEBUG=1

# Assembler command line options
AFLAGS  += -g

NMB_DRV := 2

# ----------------------------------------------------------------------------------------------------

include ${PATH_TO_ABASSI}/mAbassi/Common_GCC.make

# EOF


