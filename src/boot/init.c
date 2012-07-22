/* ----------------------------------------------------------------------------
 *		 
 *        mboot for Lophilo embedded system
 *		
 * ----------------------------------------------------------------------------
 */

#include <string.h>

#include "types.h"
#include "trace.h"
#include "option.h"
#include "mboot.h"
#include "media.h"
#include "sha204.h"

#include "sfr.h"
#include "board.h"
#include "system.h"
#include "twi.h"
#include "fpga.h"
#include "leds.h"
#include "uart.h"
#include "emac.h"
#include "rtc.h"

#include "init.h"

int main()
{
	GRID_RESET();
	rPIOD_PDR	= (1 << 12);
	rPIOD_BSR	= (1 << 12);
	rPIOE_PDR	= 0x80000000;
	rPIOE_BSR	= 0x80000000;
	
	
	rPIOC_PER	= 0x1F83;
	rPIOC_PDR	= 0xFFFFE07C;
	rPIOC_OER	= 0x0;
	rPIOC_ODR	= 0xFFFFFFFF;
	rPIOC_IFER	= 0x0;
	rPIOC_IFDR	= 0xFFFFFFFF;
	rPIOC_SODR	= 0x0;
	rPIOC_CODR	= 0x0;
	rPIOC_IER	= 0x0;
	rPIOC_IDR	= 0xFFFFFFFF;
	rPIOC_MDER	= 0x0;
	rPIOC_MDDR	= 0xFFFFFFFF;
	rPIOC_PUDR	= 0x0;
	rPIOC_PUER	= 0xFFFFFFFF;
	rPIOC_ASR	= 0xFFFFE07C;
	rPIOC_BSR	= 0x0;
	
	rSMC_SETUP(0) = (0 << 24) + (2 << 16) + (0 << 8) + (0 << 0);
	rSMC_PULSE(0) = (0 << 24) + (6 << 16) + (0 << 8) + (2 << 0);
	rSMC_CYCLE(0) = (0 << 23) + (8 << 16) + (0 << 7) + (6 << 0);
	rSMC_MODE(0) = (0 << 28) + (0 << 24) + (1 << 20) + (8 << 16) + (2 << 12) + (0 << 8) + (2 << 4) + (1 << 1) + (1 << 0);
	
	rSMC_SETUP(1) = (0 << 24) + (2 << 16) + (0 << 8) + (0 << 0);
	rSMC_PULSE(1) = (0 << 24) + (8 << 16) + (0 << 8) + (2 << 0);
	rSMC_CYCLE(1) = (0 << 23) + (10 << 16) + (0 << 7) + (6 << 0);
	rSMC_MODE(1) = (0 << 28) + (0 << 24) + (1 << 20) + (8 << 16) + (2 << 12) + (0 << 8) + (2 << 4) + (1 << 1) + (1 << 0);
	
	rSMC_SETUP(2) = (0 << 24) + (2 << 16) + (0 << 8) + (0 << 0);
	rSMC_PULSE(2) = (0 << 24) + (8 << 16) + (0 << 8) + (2 << 0);
	rSMC_CYCLE(2) = (0 << 23) + (10 << 16) + (0 << 7) + (6 << 0);
	rSMC_MODE(2) = (0 << 28) + (0 << 24) + (1 << 20) + (8 << 16) + (2 << 12) + (0 << 8) + (2 << 4) + (1 << 1) + (1 << 0);
	
	rSMC_SETUP(3) = (0 << 24) + (2 << 16) + (0 << 8) + (0 << 0);
	rSMC_PULSE(3) = (0 << 24) + (8 << 16) + (0 << 8) + (2 << 0);
	rSMC_CYCLE(3) = (0 << 23) + (10 << 16) + (0 << 7) + (6 << 0);
	rSMC_MODE(3) = (0 << 28) + (0 << 24) + (1 << 20) + (8 << 16) + (2 << 12) + (0 << 8) + (2 << 4) + (1 << 1) + (1 << 0);
	
	FPGA_CONF_P();
	GRID_RESET();
	
	BTNDIS_P();
	Init_LEDS();
	Init_TIMER();
	//Init_FPGA();
	Init_UART();
	//Init_TWI(100000);
	
	//mbootBanner();
	//Init_RTC();
	//Init_Media();
	//Init_SHA204();
	//Init_EMAC();
	SYS_UNRESET();
	GRID_UNRESET();
	//mboot();

	while(1)
	{
// 		*((volatile U32 *)(0x10000100)) = 0x22222222;
// 		*((volatile U32 *)(0x10000104)) = 0x33333333;
// 		*((volatile U32 *)(0x10000100)) = 0x44444444;
// 		*((volatile U32 *)(0x10000104)) = 0x55555555;
	}
}

