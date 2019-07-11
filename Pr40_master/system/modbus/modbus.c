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
	TRISBbits.TRISB15=0; //ножка RB15 на выходPR3
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






//int data_in[256];     //данные от слейвов

//extern volatile unsigned long global_clock;
//void mypause(void)
//{
//
//    unsigned long global_clock_save=global_clock;
//
//	while(1)
//	{
//		if( (global_clock-global_clock_save)>=2)
//		{
//			return;
//		}
//	}
//}     


void modbus_main()
{
//   Mbm_frame frame;
//   int result;
//   int data_out[256]; //данные слейвам
// 
//
//   ////////////////////////////////////////////////////////////
//   do
//   {
//       /* setup master packet */
//       frame.function=3;			/* send data */
//       frame.slave=1;					/* slave number*/ 
//       frame.address=0;      //номер регистра который хотим прочитать
//       frame.length=100;     //количество регистров
//       /* setup data to send */
//       //data_out[0]=0; //датаин юзаем только для записи в слейв
//       result=modbus_master(frame,data_out,data_in,NULL,NULL); //датаоут - ответ от слейва
//       //выдерживаем паузу 3.5 символа между транзакциями
//       //UsartWaitForSilence();
//       mypause();
//       
//       //пишем 0x1122 в регистр 34
//       frame.function=6;			/* write 1 register */
//       frame.slave=1;					/* slave number*/ 
//       frame.address=34;      //номер регистра который хотим прочитать
//       /* setup data to send */
//       data_out[0]=0x1122;
//       result=modbus_master(frame,data_out,data_in,NULL,NULL); //датаоут - ответ от слейва
//       //выдерживаем паузу 3.5 символа между транзакциями
//       //UsartWaitForSilence();
//       mypause();
//
//        //функция 0x44 - функция начать измерения по всем датчикам 
//       frame.function=0x44;			/* write 1 register */
//       frame.slave=MODBUS_BROADCAST_ADDR;
//       result=modbus_master(frame,data_out,data_in,NULL,NULL); //датаоут - ответ от слейва
//       //выдерживаем паузу 3.5 символа между транзакциями
//       //UsartWaitForSilence();
//       mypause();
//        
// 
// 
//   }while(1);    
//   
   
   
   
   return;
}
 
