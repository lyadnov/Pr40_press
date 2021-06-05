#include "system\modbus\modbus.h"
#include "system\modbus\modbus_master.h"

#include "system\eeprom\eeprom.h"
#include "p33FJ128GP706.h"
#include "system\usart\usart.h" 


//для отладки
unsigned int stat_modbus_all_frame=0;
	unsigned int stat_usart_frame_bad=0;
	unsigned int stat_usart_frame_good=0;
		unsigned int stat_modbus_frame_error_func=0;
		unsigned int stat_modbus_frame_error_crc=0;
		unsigned int stat_modbus_frame_error_slave_addr=0;
		unsigned int stat_modbus_frame_crc_ok=0;

///////////////////////////////////
void modbus_init(void)
{
	
	//ножки
#ifdef MY_MASTER_OLD
	TRISBbits.TRISB15=0; //ножка RB15 на выход
#else
	TRISBbits.TRISB14=0; //ножка RB14 на выход
#endif
	//переменные
		
	//прерывания
	
	return;
}

///////////////////////////////////
void modbus_eeprom_write_default_values(void)
{
		return;
}

