/******************************************************************
* 																																*
* @copyright	Copyright(C) 2019 4customers UG											*
* @author 		Markus Bröker <broeker.markus@googlemail.com>  			*
*																																	*
*******************************************************************/

#include <reg51.h>
#include <tools.h>

#define OSZIPORT			P4
#define GREENPORTS 		P3
#define   REDPORTS 		P2
#define COMMONPORTS		P0

// APPLICATION SPECIFIC DEFINES
#define COLS 8
#define CYCLES_TO_DISPLAY 5000

// Prototypes
void showCharacterAtRow(unsigned int row, unsigned int, unsigned int);
void Timer0_Init();

// Variables
sbit OSZIPORT0 = OSZIPORT^0;

unsigned char code TAB[COLS]  = {
	0x7f,
	0xbf,
	0xdf,
	0xef,
	0xf7,
	0xfb,
	0xfd,
	0xfe
};

unsigned char code CHARCODE[][COLS] = {
	{0x00,0x3c,0x42,0x42,0x42,0x42,0x3c,0x00}, //0
	{0x00,0x1e,0x36,0x66,0x06,0x06,0x06,0x00}, //1
	{0x7e,0x7e,0x02,0x7e,0x7e,0x40,0x7e,0x7e}, //2
	{0x00,0x3c,0x42,0x0e,0x0e,0x42,0x3c,0x00}, //3	
	{0x00,0x66,0x66,0x7e,0x7e,0x06,0x06,0x00}, //4
	{0x7e,0x7e,0x40,0x7e,0x7e,0x02,0x7e,0x7e}, //5
	{0x3e,0x40,0x40,0x40,0x7c,0x42,0x42,0x3c}, //6
	{0x00,0x7e,0x06,0x06,0x0c,0x18,0x30,0x60}, //7
	{0x3c,0x42,0x42,0x7e,0x3c,0x42,0x42,0x3c}, //8
	{0x3c,0x7e,0x42,0x42,0x3e,0x06,0x06,0x06}, //9
	{0x00,0x3c,0x66,0x66,0x7e,0x7e,0x66,0x26}, //M	
	{0x00,0x3e,0x46,0x40,0x40,0x46,0x3e,0x00}, //C
	{0x7c,0x7c,0x42,0x7c,0x7c,0x42,0x7c,0x7c}, //B
};

void showCharacterAtRow(unsigned int row, unsigned int redMask, unsigned int greenMask) 
{
	unsigned char col;
	
	for(col = 0; col < COLS; col++) {
		
		// SET COLOR MASK
		REDPORTS = redMask;
		
		// USES SOME KIND OF MULTIPLEXING IC FROM MAXIM INTEGRATED
		//GREENPORTS = greenMask;

		// SET COMMAND FOR ROW/COL
		COMMONPORTS = CHARCODE[row][col];
		
		// SET COLOR VALUES
		REDPORTS = TAB[col];
		//GREENPORTS = TAB[col];
	}	
}

/**
 */
void Timer0_Init() 
{		
	Set_Bit(TMOD, 1);
	TH0 = 0x9c; /* 100us delay */
	TR0 = 1; /* Start Interrupt 1 */	
	Set_Bit(IE, 1);
}

/**
 */
void T0INT(void) interrupt 1
{	
	OSZIPORT0 = !OSZIPORT0;
}

/**
 */
void main()
{		
	unsigned char row;
	unsigned int  i;	
	
	unsigned int rows = sizeof(CHARCODE) / sizeof(*CHARCODE);	

	Timer0_Init();	
	
	// Start Configured Timerz
	Set_Bit(IE, 7);
		
	while(1) {	
		for(i = 0; i < CYCLES_TO_DISPLAY; i++ ) {
			showCharacterAtRow(row, 255, 255);
		}			
		
		row++;
		
		if(row == rows)	{
			row = 0;
		}
	}		
}