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

#include "grid.h"


int main()
{
	U32 i;
	
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

U32 j, k, a;

	while(1)
	{
		if((gSYS_ID == 0x1)&&(gSYS_ID_FLAG == 0xEA68)){
			grid_func_led_set(0, 0, 0x60, 0x15);
			grid_func_led_set(1, 0, 0x60, 0x15);
			grid_func_led_set(2, 0x60, 0, 0x15);
			grid_func_led_set(3, 0x60, 0, 0x15);
			
			grid_shield_a_lo_en();
			grid_shield_a_hi_en();
			grid_shield_b_lo_en();
			grid_shield_b_hi_en();
			grid_shield_a_pwr_en();
			grid_shield_b_pwr_en();

			for(i=0; i<26; i++) {
				GRID_PWM(i)->PWM_RESET = 0;
				GRID_PWM(i)->PWM_GATE = 0x0000FFFF;
			}
			
			for(i=0; i<26; i++){
				for(j=0; j<=0x8000; j = j+0x200){
					if(i >= 2) GRID_PWM((U8)(i-2))->PWM_DTYC = j/128;
					if(i >= 1) GRID_PWM((U8)(i-1))->PWM_DTYC = j/8;
					GRID_PWM(i)->PWM_DTYC = j;
					if(i <= 25) GRID_PWM((U8)(i+1))->PWM_DTYC = j/8;
					if(i <= 24) GRID_PWM((U8)(i+2))->PWM_DTYC = j/128;				
					Delay_ms(20);
				}
				
				Delay_ms(50);
				
				for(j=0; j<=0x8000; j = j+0x200){
					if(i >= 2) GRID_PWM((U8)(i-2))->PWM_DTYC = (0x8000 - j)/128;
					if(i >= 1) GRID_PWM((U8)(i-1))->PWM_DTYC = (0x8000 - j)/8;
					GRID_PWM(i)->PWM_DTYC = 0x8000 - j;
					if(i <= 25) GRID_PWM((U8)(i+1))->PWM_DTYC = (0x8000 - j)/8;
					if(i <= 24) GRID_PWM((U8)(i+2))->PWM_DTYC = (0x8000 - j)/128;
					Delay_ms(10);
				}
				
				Delay_ms(50);
			}
			
 			GRID_PIO26_SLOT_A->PIO_DOE = (0xFFFFFFFF);
 			GRID_PIO26_SLOT_B->PIO_DOE = (0xFFFFFFFF);

 			for(i=0; i<4; i++)
 			{
 				GRID_PIO26_SLOT_A->PIO_DOUT[i] = (0x0);
 				Delay_ms(200);
 				GRID_PIO26_SLOT_A->PIO_DOUT[i] = (0xFF);
 			}

 			for(i=0; i<26; i++)
 			{
 				GRID_PIO26_SLOT_A->PIO_IO[i] = 0;
 				Delay_ms(50);
 				GRID_PIO26_SLOT_A->PIO_IO[i] = 1;
 			}
		}
	}
}

