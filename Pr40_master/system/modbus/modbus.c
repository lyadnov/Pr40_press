#include "system\modbus\modbus.h"
#include "system\modbus\modbus_master.h"

#include "system\eeprom\eeprom.h"
#include "p33FJ128GP706.h"
#include "system\usart\usart.h" 




//��� �������
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
	
	//�����
#ifdef MY_MASTER_OLD
	TRISBbits.TRISB15=0; //����� RB15 �� �����PR3
#else
  TRISBbits.TRISB14=0; //����� RB14 �� �����
#endif
	//����������
	  
	//����������
	
	return;
}

///////////////////////////////////
void modbus_eeprom_write_default_values(void)
{
    return;
}






//int data_in[256];     //������ �� �������

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
//   int data_out[256]; //������ �������
// 
//
//   ////////////////////////////////////////////////////////////
//   do
//   {
//       /* setup master packet */
//       frame.function=3;			/* send data */
//       frame.slave=1;					/* slave number*/ 
//       frame.address=0;      //����� �������� ������� ����� ���������
//       frame.length=100;     //���������� ���������
//       /* setup data to send */
//       //data_out[0]=0; //������ ����� ������ ��� ������ � �����
//       result=modbus_master(frame,data_out,data_in,NULL,NULL); //������� - ����� �� ������
//       //����������� ����� 3.5 ������� ����� ������������
//       //UsartWaitForSilence();
//       mypause();
//       
//       //����� 0x1122 � ������� 34
//       frame.function=6;			/* write 1 register */
//       frame.slave=1;					/* slave number*/ 
//       frame.address=34;      //����� �������� ������� ����� ���������
//       /* setup data to send */
//       data_out[0]=0x1122;
//       result=modbus_master(frame,data_out,data_in,NULL,NULL); //������� - ����� �� ������
//       //����������� ����� 3.5 ������� ����� ������������
//       //UsartWaitForSilence();
//       mypause();
//
//        //������� 0x44 - ������� ������ ��������� �� ���� �������� 
//       frame.function=0x44;			/* write 1 register */
//       frame.slave=MODBUS_BROADCAST_ADDR;
//       result=modbus_master(frame,data_out,data_in,NULL,NULL); //������� - ����� �� ������
//       //����������� ����� 3.5 ������� ����� ������������
//       //UsartWaitForSilence();
//       mypause();
//        
// 
// 
//   }while(1);    
//   
   
   
   
   return;
}
 
