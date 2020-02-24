/*************************************************
*
* File containing all mAbassi tasks definitions
* authors : A. Kneip & M. Xhonneux
* date:		01/13/2020
*
*************************************************/

/// INCLUDES ///
#include "../inc/myApp_MTL.h"
#include <lwip/sockets.h>

#include "mAbassi.h"
#include "Platform.h"                               // Everything about the target processor is here
#include "HWinfo.h"                                 // Everything about the target hardware is here    */
#include "SysCall.h"                                // System Call layer stuff                        */

#include "arm_pl330.h"
#include "dw_i2c.h"
#include "cd_qspi.h"
#include "dw_sdmmc.h"
#include "dw_spi.h"
#include "dw_uart.h"
#include "alt_gpio.h"
#include "math.h"

#include "vip_fr.h"
#include "simple_graphics.h"
#include "gui.h"
#include "touch.h"
#include "../painter/geometry.h"
#include "../painter/terasic_lib/terasic_includes.h"
#ifdef IS_MTL2
	#include "../painter/terasic_lib/multi_touch2.h"
#else
	#include "../painter/terasic_lib/multi_touch.h"
#endif


/// BUILD-TIME CONSTANTS DEFINITION ///
// --- Comment following line for single-frame buffering + adapt code ---
#define DUAL_FRAME_BUFFER

#define OS_TIMER_US 1000
#define PI 3.1415
#define MTC_REG_INT_ACK      1     // write only (write any value to ack)

/// CONSTANTS DEFINITION ///
// --- Define whether to print some of the results ---
const int PRINT_EN=0;
// --- Define the max. update frequency of the screen for the test application ---
const int update_rate = 100;

/// VARIABLES DEFINITION ///
#ifdef IS_MTL2
	MTC2_INFO 			*myTouch;
#else
	MTC_INFO			*myTouch;
#endif
VIP_FRAME_READER 	*pReader;
uint32_t 			*myFrameBuffer;

/// TASKS DEFINITION ///
// Task_TXRX: send data to then receive data from another DE10 HPS through Ethernet connection //

#define SENDING 0
#define SERVER_PORT_NUM 6000
#define SENDER_PORT_NUM 6000
#define SERVER_IP_ADDRESS "192.168.1.42"
#define SENDER_IP_ADDR "192.168.1.43"
void Task_TXRX(void)
{

	MTX_t    *PrtMtx;
	PrtMtx = MTXopen("Printf Mtx");

	int socket_fd;
	struct sockaddr_in sa,isa;

	/* Creates an TCP socket (SOCK_STREAM) with Internet Protocol Family (PF_INET).
	 * Protocol family and Address family related. For example PF_INET Protocol Family and AF_INET family are coupled.
	*/

	socket_fd = socket(PF_INET, SOCK_STREAM, 0);

	if ( socket_fd < 0 )
	{
		MTXlock(PrtMtx,-1);
	    printf("socket call failed");
		MTXunlock(PrtMtx);
	    exit(0);

	}

	memset(&sa, 0, sizeof(struct sockaddr_in));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
	sa.sin_port = htons(SERVER_PORT_NUM);

#if SENDING
	int recv_data; char data_buffer[80];


	MTXlock(PrtMtx,-1);
	printf("start TXRX task !\n");
	MTXunlock(PrtMtx);
	int success = -1;
	int isConnected = -1;

	// Prevent socket connection before stable link
	int counter = 0;
	int connectState;
	while (counter < 10)
	{
		connectState = ETH_LinkStatus(1);
		MTXlock(PrtMtx,-1);
		printf("ETH_LinkStatus is at %d\n",connectState);
		MTXunlock(PrtMtx);

		if(connectState != 0)
			counter++;
		else
			counter = 0;

		TSKsleep(OS_MS_TO_TICK(2000));

		MTXlock(PrtMtx,-1);
		printf("stability counter is at %d\n",counter);
		MTXunlock(PrtMtx);
	}

	int err = connect(socket_fd,(struct sockaddr_in*)&sa,sizeof(struct sockaddr_in));

	//if(success != 0)
	if (err < 0)
	{

		MTXlock(PrtMtx,-1);
		printf("connect failed: %d \n", err);
		//printf("connect failed: %d \n", isConnected);
	    MTXunlock(PrtMtx);
	    close(socket_fd);
	    exit(2);

	}


	MTXlock(PrtMtx,-1);
	printf("waiting\n");
	MTXunlock(PrtMtx);
	recv_data = recv(socket_fd,data_buffer,sizeof(data_buffer),0);
	if(recv_data < 0)
	{

		MTXlock(PrtMtx,-1);
	    printf("recv failed \n");
	    MTXunlock(PrtMtx);
	    close(socket_fd);
	    exit(2);

	}
	data_buffer[recv_data] = '\0';

	MTXlock(PrtMtx,-1);
	printf("got %d bytes\n", recv_data);
	printf("received data: %s\n",data_buffer);
	MTXunlock(PrtMtx);
#else
	int addr_size,sent_data, accept_fd; char data_buffer[80];


	if (bind(socket_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) == -1)
	{
	printf("Bind to Port Number %d ,IP address %s failed\n",SENDER_PORT_NUM,SENDER_IP_ADDR);
	close(socket_fd);
	exit(1);
	}

	listen(socket_fd,5);
	addr_size = sizeof(isa);
	accept_fd = accept(socket_fd, (struct sockaddr*)&isa,&addr_size);
	if(accept_fd < 0)
	{

	    printf("accept failed\n");
	    close(socket_fd);
	    exit(2);

	}
	strcpy(data_buffer,"Hello World\n");
	sent_data = send(accept_fd, data_buffer,sizeof("Hello World",0), MSG_OOB);

	if(sent_data < 0 )
	{

	    printf("send failed\n");
	    close(socket_fd);
	    exit(3);

	}

#endif
	close(socket_fd);
}

// Task_MTL: sense touches on the MTL screen and act on the display based on these touches
void Task_MTL(void)
{
	// Local variables 
	MTX_t				*PrtMtx;

    TSKsleep(OS_MS_TO_TICK(500));

	// Initialize global timer
    assert(ALT_E_SUCCESS == alt_globaltmr_init());
    assert(ALT_E_SUCCESS == alt_globaltmr_start());
    
	// --- Start by initializing MTL ---
	// Open print Mutex during init, preventing printdata corruption (see Week 4 in INGI2315)
	if(PRINT_EN)
	{
		PrtMtx = MTXopen("Printf Mtx");
		MTXlock(PrtMtx,-1);
		printf("Starting MTL initialization...\n");
	}
	// Perform initialization 
	#ifdef IS_MTL2
    	oc_i2c_init(fpga_i2c);
		myTouch = MTC2_Init(fpga_i2c, fpga_mtc, LCD_TOUCH_INT_IRQ);
	#else
		myTouch = MTC_Init(fpga_i2c, fpga_mtc, LCD_TOUCH_INT_IRQ);
	#endif
	
	// Enable MTL IRQs
	OSisrInstall(GPT_MTC_IRQ, (void *) &mtc_CallbackInterrupt);
	GICenable(GPT_MTC_IRQ, 128, 1);
	// Enable interruptMask & edgeCapture of PIO core
	alt_write_word(PIOinterruptmask_fpga_MTL, 0x3);
	alt_write_word(PIOedgecapture_fpga_MTL, 0x3);
	
	if(PRINT_EN)
	{
		// Close Mutex after print
		printf("MTL initialization completed !\n");
		MTXunlock(PrtMtx);
	}
	
	// --- Frame reader pointer creation ---
	#ifdef DUAL_FRAME_BUFFER
		pReader =  VIPFR_Init((alt_u32 *)(ALT_LWFPGASLVS_OFST + ALT_VIP_VFR_0_BASE), (void *)FR_FRAME_0, (void *)FR_FRAME_1, FRAME_WIDTH, FRAME_HEIGHT);
	#else
		pReader =  VIPFR_Init((alt_u32 *)(ALT_LWFPGASLVS_OFST + ALT_VIP_VFR_0_BASE), (void *)FR_FRAME_0, (void *)FR_FRAME_0, FRAME_WIDTH, FRAME_HEIGHT);
	#endif // DUAL_FRAME_BUFFER
	VIPFR_Go(pReader, TRUE);

	// Clean screen
	vid_clean_screen(pReader, BLACK_24);
	VIPFR_ActiveDrawFrame(pReader);
	vid_clean_screen(pReader, BLACK_24);
	VIPFR_ActiveDrawFrame(pReader);
	TSKsleep(OS_MS_TO_TICK(500));
	// Draw welcome screen
	vid_draw_box(0,0,FRAME_WIDTH,FRAME_HEIGHT,WHITE_24,DO_FILL,pReader);
	vid_print_string_alpha(280, 220, BLACK_24, WHITE_24, tahomabold_20, pReader, "Welcome to ELEC2103 !");
	printf("SALUUT\n");
	VIPFR_ActiveDrawFrame(pReader);
	vid_draw_box(0,0,FRAME_WIDTH,FRAME_HEIGHT,WHITE_24,DO_FILL,pReader);
	vid_print_string_alpha(280, 220, BLACK_24, WHITE_24, tahomabold_20, pReader, "Welcome to ELEC2103 !");
	VIPFR_ActiveDrawFrame(pReader);
	TSKsleep(OS_MS_TO_TICK(5000));

	// Launch demo screen
	char str[80];
	for(int i=4;i>0;i--)
	{
		sprintf(str,"Scree demo will launch in %d",i-1);
		vid_clean_screen(pReader, BLACK_24);
		vid_draw_box(0,0,FRAME_WIDTH,FRAME_HEIGHT,BLACK_24,DO_FILL,pReader);
		vid_print_string_alpha(280, 220, WHITE_24, BLACK_24, tahomabold_20, pReader, str);
		VIPFR_ActiveDrawFrame(pReader);
		vid_clean_screen(pReader, BLACK_24);
		vid_draw_box(0,0,FRAME_WIDTH,FRAME_HEIGHT,BLACK_24,DO_FILL,pReader);
		vid_print_string_alpha(280, 220, WHITE_24, BLACK_24, tahomabold_20, pReader, str);
		VIPFR_ActiveDrawFrame(pReader);
		// Wait 1 Second between each number
		TSKsleep(OS_MS_TO_TICK(1000));
		printf("Test0\n");

	}

	// Initialize the 4-ways display
	GUI_simpleColorInit(pReader);
	VIPFR_ActiveDrawFrame(pReader);
	GUI_simpleColorInit(pReader);
	VIPFR_ActiveDrawFrame(pReader);
	TSKsleep(OS_MS_TO_TICK(100));
	
	
	// Touch coordinates
	POINT screenTouch;
	printf("Test1\n");

	int touchZone = 0;
	// Start endless processing & display loop
	int isTouched;
	int X=-1, Y=-1;
	int Xnew, Ynew;
	for(;;)
	{
		// MTL touch reading
		#ifdef IS_MTL2
			isTouched = MTC2_GetStatus(myTouch, NULL, NULL, &Xnew, &Ynew, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
		#else
			isTouched = MTC_GetStatus(myTouch, NULL, NULL, &Xnew, &Ynew, NULL, NULL);
		#endif
		// Print touch coordinate (Mutex lock required)
		if(isTouched && (Xnew!=X && Ynew !=Y))
		{
			printf("Test2\n");
			X=Xnew; Y=Ynew;
			PtSet(&screenTouch,X,Y);
			if(PRINT_EN)
			{
				printf("Test3\n");
				MTXlock(PrtMtx,-1);
				printf("MTL touch detected in X=%d, Y=%d !\n",Xnew,Ynew);
				MTXunlock(PrtMtx);
			}
			// Here, we set touchZone based on the quadrant touched on the screen
			touchZone = TOUCH_getRect(screenTouch,2,2);
			// MTL display function based on the touched zone on the screen
			GUI_simpleColorPrint(pReader,touchZone);
			VIPFR_ActiveDrawFrame(pReader);
			GUI_simpleColorPrint(pReader,touchZone);
			VIPFR_ActiveDrawFrame(pReader);
			TSKsleep(OS_MS_TO_TICK(update_rate)); // Sets delay between 2 color updates
		}
		else	// Reset touchZone
			touchZone = 0;
		TSKsleep(OS_MS_TO_TICK(5));
	}	
}

// Task Gsensor: read the accelerometer data and send it to another task
void Task_GSENSOR(void)
{
	// ACCELEROMETER HAS TO BE USED IN THE PROJECT !
	// Refer to INGI2315 material to help you
}

/**************************************************************/
/*		 DON'T TOUCH SECTIONS DELIMITED BY dashed LINES		  */
/**************************************************************/

/*-----------------------------------------------------------*/

//delay_us: used by i2C_core.c
void delay_us(uint32_t us) {
    uint64_t start_time = alt_globaltmr_get64();
    uint32_t timer_prescaler = alt_globaltmr_prescaler_get() + 1;
    uint64_t end_time;
    alt_freq_t timer_clock;
    
    assert(ALT_E_SUCCESS == alt_clk_freq_get(ALT_CLK_MPU_PERIPH, &timer_clock));
    end_time = start_time + us * ((timer_clock / timer_prescaler) / ALT_MICROSECS_IN_A_SEC);

    while(alt_globaltmr_get64() < end_time);
}


/* Align on cache lines if cached transfers */
static char g_Buffer[9600] __attribute__ ((aligned (OX_CACHE_LSIZE)));

void load_picture(int height, int width, int bpp, PICT_STRUCT* pict_struct,int FdSrc){
	int       Nrd;
	int       i;

	pict_struct->height = height;
	pict_struct->width = width;
	pict_struct->bytes_per_pixel = bpp;
	pict_struct->pixel_data = malloc((height*width*bpp + 1)*sizeof(unsigned char));
	unsigned char* ptr_des = pict_struct->pixel_data;
	if (FdSrc >= 0) {
		int j=0;
	    do {
	    	Nrd = read(FdSrc, &g_Buffer[0], sizeof(g_Buffer));
	        i=0;
	        while(i < Nrd) {
	        	ptr_des[j+2] = g_Buffer[i];
	            ptr_des[j+1] = g_Buffer[i+1];
	            ptr_des[j] = g_Buffer[i+2];
	            i += 3;
	            j+=3;
	        }
	    } while (Nrd >= sizeof(g_Buffer));
	}
}

/*-----------------------------------------------------------*/

void mtc_CallbackInterrupt(uint32_t icciar, void *context)
{
	#ifdef IS_MTL2
		//printf("INFO: IRQ from MTC2\r\n");
		// Clear the interruptmask of PIO core
		alt_write_word(PIOinterruptmask_fpga_MTL, 0x0);
		mtc2_QueryData(myTouch);
	#else
		//printf("INFO: IRQ from MTC\n");
		mtc_QueryData(myTouch);
		
		// Clear the interrupt (in i2c core)
		alt_write_word(fpga_i2c + (MTC_REG_INT_ACK*4), 0x0);
		// Clear the interruptmask of PIO core
		alt_write_word(PIOinterruptmask_fpga_MTL, 0x0);
	#endif
	// Enable the interruptmask and edge register of PIO core for new interrupt
	alt_write_word(PIOinterruptmask_fpga_MTL, 0x1);
	alt_write_word(PIOedgecapture_fpga_MTL, 0x1);
}

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

void toogle_hps_led()
{
    uint32_t hps_led_value = alt_read_word(ALT_GPIO1_SWPORTA_DR_ADDR);
    hps_led_value >>= HPS_LED_PORT_BIT;
    hps_led_value = !hps_led_value;
    hps_led_value <<= HPS_LED_PORT_BIT;
    alt_gpio_port_data_write(HPS_LED_PORT, HPS_LED_MASK, hps_led_value);
}

/*-----------------------------------------------------------*/

void button_CallbackInterrupt (uint32_t icciar, void *context)
{
    SEM_t    *PtrSem;
    uint32_t button;

    button = alt_read_word(PIOdata_fpga_button);

    // Clear the interruptmask of PIO core
    alt_write_word(PIOinterruptmask_fpga_button, 0x0);

    // Enable the interruptmask and edge register of PIO core for new interrupt
    alt_write_word(PIOinterruptmask_fpga_button, 0x3);
    alt_write_word(PIOedgecapture_fpga_button, 0x3);

    PtrSem = SEMopen("MySemaphore");
    SEMpost(PtrSem);

    if (button == 1) {
        PtrSem = SEMopen("MySem_DisplayFile");
        SEMpost(PtrSem);
    }
}

/*-----------------------------------------------------------*/
void button_ConfigureInterrupt( void )
{
    OSisrInstall(GPT_BUTTON_IRQ, (void *) &button_CallbackInterrupt);
    GICenable(GPT_BUTTON_IRQ, 128, 1);

    // Enable interruptmask and edgecapture of PIO core for buttons 0 and 1
    alt_write_word(PIOinterruptmask_fpga_button, 0x3);
    alt_write_word(PIOedgecapture_fpga_button, 0x3);
}

/*-----------------------------------------------------------*/

void setup_hps_gpio()
{
    uint32_t hps_gpio_config_len = 2;
    ALT_GPIO_CONFIG_RECORD_t hps_gpio_config[] = {
        {HPS_LED_IDX  , ALT_GPIO_PIN_OUTPUT, 0, 0, ALT_GPIO_PIN_DEBOUNCE, ALT_GPIO_PIN_DATAZERO},
        {HPS_KEY_N_IDX, ALT_GPIO_PIN_INPUT , 0, 0, ALT_GPIO_PIN_DEBOUNCE, ALT_GPIO_PIN_DATAZERO}
    };

    assert(ALT_E_SUCCESS == alt_gpio_init());
    assert(ALT_E_SUCCESS == alt_gpio_group_config(hps_gpio_config, hps_gpio_config_len));
}


/*-----------------------------------------------------------*/

void Task_HPS_Led(void)
{
    MTX_t    *PrtMtx;       // Mutex for exclusive access to printf()
    MBX_t    *PrtMbx;
    intptr_t *PtrMsg;

    setup_hps_gpio();   // This is the Adam&Eve Task and we have first to setup the gpio
    button_ConfigureInterrupt();

    PrtMtx = MTXopen("Printf Mtx");
    MTXlock(PrtMtx, -1);
    printf("\n\nDE10-Nano - MyApp_MTL\n\n");
    printf("Task_HPS_Led running on core #%d\n\n", COREgetID());
    MTXunlock(PrtMtx);

    PrtMbx = MBXopen("MyMailbox", 128);

	for( ;; )
	{
        if (MBXget(PrtMbx, PtrMsg, 0) == 0) {  // 0 = Never blocks
            MTXlock(PrtMtx, -1);
            printf("Receive message (Core = %d)\n", COREgetID());
            MTXunlock(PrtMtx);
        }
        toogle_hps_led();

        TSKsleep(OS_MS_TO_TICK(500));
	}
}

/*-----------------------------------------------------------*/
