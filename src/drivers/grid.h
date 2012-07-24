#define GBASE_SYS_ID						(unsigned int)(0x10000000)
#define gSYS_ID 								(*(volatile unsigned short *)(GBASE_SYS_ID + 0x0))
#define gSYS_ID_FLAG						(*(volatile unsigned short *)(GBASE_SYS_ID + 0x2))
#define gSYS_ID_VER 						(*(volatile unsigned int *)(GBASE_SYS_ID + 0x4))
#define gSYS_ID_LOCK						(*(volatile unsigned int *)(GBASE_SYS_ID + 0x8))
#define gSYS_ID_LOCKB						(*(volatile unsigned int *)(GBASE_SYS_ID + 0xC))

#define GBASE_FUNC_LED					(unsigned int)(0x10000100)
#define gFUNC_LED_B(ch)					(*(volatile unsigned char *)(GBASE_FUNC_LED + 0x0 + 0x4 * ch))
#define gFUNC_LED_G(ch)					(*(volatile unsigned char *)(GBASE_FUNC_LED + 0x1 + 0x4 * ch))
#define gFUNC_LED_R(ch)					(*(volatile unsigned char *)(GBASE_FUNC_LED + 0x2 + 0x4 * ch))
#define gFUNC_LED_S(ch)					(*(volatile unsigned char *)(GBASE_FUNC_LED + 0x3 + 0x4 * ch))

#define GBASE_SHIELD_CTRL				(unsigned int)(0x10000200)
#define gSHIELD_CTRL_OC					(*(volatile unsigned char *)(GBASE_SHIELD_CTRL + 0x0))
#define gSHIELD_CTRL_OEL				(*(volatile unsigned char *)(GBASE_SHIELD_CTRL + 0x1))
#define gSHIELD_CTRL_OEH				(*(volatile unsigned char *)(GBASE_SHIELD_CTRL + 0x2))
#define gSHIELD_CTRL_PWREN			(*(volatile unsigned char *)(GBASE_SHIELD_CTRL + 0x3))

#define grid_func_led_set(ch, r, g, b)	{gFUNC_LED_S(ch) = (unsigned char)(0x00); gFUNC_LED_R(ch) = (unsigned char)r; gFUNC_LED_G(ch) = (unsigned char)g; gFUNC_LED_B(ch) = (unsigned char)b;}
#define grid_func_led_asi(ch)						{gFUNC_LED_S(ch) = (unsigned char)(0x80);}	// Set LED controlled by external module
#define grid_func_led_usr(ch)						{gFUNC_LED_S(ch) = (unsigned char)(0x00);}	// Set LED controlled by register values

#define grid_shield_a_lo_en()						{gSHIELD_CTRL_OEL |= (1 << 0);}
#define grid_shield_a_hi_en()						{gSHIELD_CTRL_OEH |= (1 << 0);}
#define grid_shield_b_lo_en()						{gSHIELD_CTRL_OEL |= (1 << 1);}
#define grid_shield_b_hi_en()						{gSHIELD_CTRL_OEH |= (1 << 1);}
#define grid_shield_a_pwr_en()					{gSHIELD_CTRL_PWREN |= (1 << 0);}
#define grid_shield_b_pwr_en()					{gSHIELD_CTRL_PWREN |= (1 << 1);}
#define grid_shield_a_lo_dis()					{gSHIELD_CTRL_OEL &= ~(1 << 0);}
#define grid_shield_a_hi_dis()					{gSHIELD_CTRL_OEH &= ~(1 << 0);}
#define grid_shield_b_lo_dis()					{gSHIELD_CTRL_OEL &= ~(1 << 1);}
#define grid_shield_b_hi_dis()					{gSHIELD_CTRL_OEH &= ~(1 << 1);}
#define grid_shield_a_pwr_dis()					{gSHIELD_CTRL_PWREN &= ~(1 << 0);}
#define grid_shield_b_pwr_dis()					{gSHIELD_CTRL_PWREN &= ~(1 << 1);}

typedef struct _grid_pio26{
	unsigned int GRID_MOD_SIZE;		// 0x0
	unsigned int GRID_MOD_ID;			// 0x4
	unsigned char PIO_DOUT[4];		// 0x8
	unsigned char PIO_DIN[4];			// 0xC
	unsigned int PIO_DOE;					// 0x10
	unsigned int resv1[3];
	unsigned int PIO_IMASK;				// 0x20
	unsigned int PIO_ICLR;				// 0x24
	unsigned int PIO_IE;					// 0x28
	unsigned int PIO_IINV;				// 0x2C
	unsigned int PIO_IEDGE;				// 0x30
	unsigned int resv2[3];
	unsigned char PIO_IO[26];			// 0x40 ~ 0x59
}grid_pio26, *pGrid_pio26;

#define GRID_PIO26_SLOT_A     ((pGrid_pio26)0x20000000)
#define GRID_PIO26_SLOT_B     ((pGrid_pio26)0x20000080)

typedef struct _grid_PWM{
	unsigned int GRID_MOD_SIZE;		// 0x0
	unsigned int GRID_MOD_ID;			// 0x4
	unsigned char PWM_RESET;			// 0x8
	unsigned char PWM_OUTINV;			// 0x9
	unsigned char PWM_PMEN;				// 0xA
	unsigned char PWM_FMEN;				// 0xB
	unsigned int PWM_GATE;				// 0xC
	unsigned int PWM_DTYC;				// 0x10
}grid_PWM, *pGrid_PWM;

#define GRID_PWM(ch)					((pGrid_PWM)(0x20000100 + ch * 32))
