#include "p33FJ128GP706.h"

#include "system\eeprom\eeprom.h"
#include "system\pmode\pmode.h"

//---------константы---------------

//---------переменные--------------
unsigned char  cfg_pmode;
unsigned short cfg_p2_intervals[NUMBER_OF_P2_INTERVALS];

//----------функции----------------

//--------------------------основная часть-------------------------------------------
void pmode_change(unsigned int value)
{
	if (cfg_pmode == value)
		return;
	
	if (cfg_pmode == 0)
	{
		cfg_pmode = value;
		if(value == 1)
			PORTFbits.RF0 = 1;
		if(value == 2)
		{
			//dml!!!!!!!!!!!!!!!!!!!!!
		}	
		else if(value == 3)	
			PORTFbits.RF1 = 1;
	}
	else
	{
		if(value != 0)
			return; //ошибка, только через 0 можно менять значение pmode
		cfg_pmode = value;
		PORTFbits.RF0 = 0;
		PORTFbits.RF1 = 0;
		PORTDbits.RD1 = 0; //dml!!!
	}	
}

void pmode_eeprom_write_default_values(void)
{
	int i;
	
	eeprom_write_byte(ADDR_EEPROM_PMODE,DEFAULT_PMODE);
	
	for (i = 0; i < NUMBER_OF_P2_INTERVALS; i++)
		eeprom_write_byte(ADDR_EEPROM_P2_INTERVAL1 + i, DEFAULT_P2_INTERVAL);
}


void pmode_init(void)
{
	int i;

	//ножки
	TRISFbits.TRISF0 = 0; //P1 mode
	TRISFbits.TRISF1 = 0; //P3 mode
	TRISDbits.TRISD1 = 0; //P2 mode
	
	//переменные EEPROM
	cfg_pmode = eeprom_read(ADDR_EEPROM_PMODE);
	for (i = 0; i < NUMBER_OF_P2_INTERVALS; i++)
		cfg_p2_intervals[i] = eeprom_read(ADDR_EEPROM_P2_INTERVAL1 + i);
		
}

