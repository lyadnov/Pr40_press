#include "main\p33FJ128GP706.h"
#include "main\errors.h" 
#include "system\modbus\modbus.h"
#include "system\usart\usart.h"

unsigned int stat_usart_error_timout=0;
unsigned int stat_usart_error_frame=0;
unsigned int stat_usart_error_parity=0;
unsigned int stat_usart_error_overrun=0;


void rs485_send_on(void)
{
	PORTBbits.RB15 = 1; //��������� �����-������������: ��������� ������ ������ � �����
		 
	//����� 400���, ����� ������ ����� ��������� �����-����������� ������� + ����� ����� modbus ��������
	T8CON = 0;
	T8CONbits.TCS = 0;            //Timer8 Clock Source Select bit: Internal clock (Fcy=40MHz=Fosc/2=80���/2
	T8CONbits.TCKPS = 3;          //1:256  1����=25*256��=6.4���
	PR8 = USART_MODBUS_PAUSE;     //400���
	TMR8 = 0;
	IFS3bits.T8IF = 0; //���������� ����
	T8CONbits.TON = 1; //�������� ������ 8
	while (IFS3bits.T8IF == 0);
}


void rs485_send_off(void)
{
	unsigned char data;

	while (U1STAbits.TRMT == 0); //���� ����������� ���������� ��������

	PORTBbits.RB15 = 0; //��������� �����-������������: ��������� ������ ������ � �����

	//�������� RX ������, �.� ��� �������� ��� ��������������, ���� ������ 4 ���� RX �������.
	data = U1RXREG;  //��������� RX ����� ��� USART, ����� ������ 4 �����
	data = U1RXREG;  //������� ���������� 4 �����,������� ��������� ��������� ������� ��� ����� TX �����������
	data = U1RXREG;
	data = U1RXREG;

	if (U1STAbits.FERR)
		data = U1RXREG;  //paranoid verification, just in case

	if (U1STAbits.OERR)
		U1STAbits.OERR = 0; //NOTE: if U1MODEbits.BRGH == 0, then this flag sometimes on
}


static void rs485_init(void)
{
	TRISBbits.TRISB15 = 0; //����� RB15 �� �����
	PORTBbits.RB15 = 0;    //��������� �����-������������: ��������� ������ ������ � �����
}


void UsartTxByteX(char data)
{
	while (U1STAbits.UTXBF == 1); //���� ��������� �������� ���������� ������
	U1TXREG = data;
}


char UsartRxByte(unsigned char *data)
//��������� ����, ������� 13-26����
//���������� 1, � ������ ������, 0 ���� ��� �������
{

	while (U1STAbits.URXDA == 0);
		
	//�������� ��� ������� ������ ��� ������
	if (U1STAbits.FERR)                 // If a framing error occured
	{
		*data = U1RXREG; 
		//error_num=err_UsartRxFrameError;
		slave_regs[REG_ERROR_USART_FRAME]++;
		return(1);
	}
	if (U1STAbits.PERR)                 // If a framing error occured
	{
		*data = U1RXREG; 
		//error_num=err_UsartRxParityError;
		 slave_regs[REG_ERROR_USART_PARITY]++; 
		return(1);
	}

	*data = U1RXREG; 

	if (U1STAbits.OERR)                 //������������ ������
	{ 
		U1STAbits.OERR=0;
		slave_regs[REG_ERROR_USART_OVERRUN]++; 
		return(1);   
	}

	return (0);                     // Return the received data
}


char UsartRxByte_withTimeout(unsigned char *data)  //������������ ������ ��������
//��������� ����, ������� 13-26����
//���������� 1, � ������ ������, 0 ���� ��� �������
{
	T8CON = 0;
	T8CONbits.TCS = 0;        //Timer8 Clock Source Select bit: Internal clock (Fcy=40MHz=Fosc/2=80���/2
	T8CONbits.TCKPS = 3;      //1:256  1����=25*256��=6.4���
	PR8 = USART_MASTER_RX_TIMEOUT;   //=3.2�� ������
	do
	{
		TMR8 = 0;
		IFS3bits.T8IF = 0; //���������� ����
		T8CONbits.TON = 1; //�������� ������ 8
		while ((U1STAbits.URXDA == 0) && (IFS3bits.T8IF ==0 ));

		if (U1STAbits.URXDA == 0)
		{
			//������� �� ��������
			T8CONbits.TON = 0; //��������� ������ 8
			stat_usart_error_timout++;
			return(1); //������ �������
		}
		else
		{
			T8CONbits.TON = 0; //��������� ������ 8
			break;
		}
	} while(1);

	//�������� ��� ������� ������ ��� ������
	if (U1STAbits.FERR)                 // If a framing error occured
	{
		*data = U1RXREG; 
		//stat_usart_error_frame++;
		slave_regs[REG_ERROR_USART_FRAME]++;
		return(1);
	}
		if(U1STAbits.PERR)                 // If a parity error occured
		{
		*data = U1RXREG; 
		//stat_usart_error_parity++;
		slave_regs[REG_ERROR_USART_PARITY]++; 
		return(1);
	}

	*data = U1RXREG; 

	if (U1STAbits.OERR)                 //������������ ������
	{ 
		U1STAbits.OERR = 0;
		//stat_usart_error_overrun++;
		slave_regs[REG_ERROR_USART_OVERRUN]++; 
		return(1);   
	}

	return (0);                     // Return the received data
}


void UsartWaitForSilence(void)
//������� ���� ���� � ����� �� �������� ������ ������������� 3.5�������
//3.5�������= ( 1��� / ((115200���_���/10���_�_�����)) )*3.5 = 300���
//������� �������� ��������� 80���  �� TMR8 �������� 80���/2 + �������� 256. 
// �.� ���������� TMR8 �� 1 ���������� ��� � (1/80���)*256= ��� � 6,4���
//������� ����� ��������� ������� ������� ������ 300���/6.4���=47 � ���������� ���� IFS3bits.T8IF
{
	unsigned char data;

	data=U1RXREG;  //��������� RX ����� ��� USART, ����� ������ 4 �����
	data=U1RXREG;  //������� ���������� 4 �����,������� ��������� ��������� ������� ��� ����� TX �����������
	data=U1RXREG;
	data=U1RXREG;

	T8CON = 0;
	T8CONbits.TCS = 0;            //Timer8 Clock Source Select bit: Internal clock (Fcy=40MHz=Fosc/2=80���/2
	T8CONbits.TCKPS = 3;          //1:256  1����=25*256��=6.4���
	PR8 = USART_MODBUS_ERROR_PAUSE;  //=300���

	do
	{
		TMR8 = 0;
		IFS3bits.T8IF = 0; //���������� ����
		T8CONbits.TON = 1; //�������� ������ 8
		while ((U1STAbits.URXDA == 0) && (IFS3bits.T8IF == 0));
				
		if (U1STAbits.URXDA == 0)
		{
			//������ ����� ��� ������ ���������
			T8CONbits.TON = 0; //��������� ������ 8
			return;
		}
		else
		{
			//������ ������, � ������ ����� �� ��������� - ��������� ������� ������
			data = U1RXREG;
			if (U1STAbits.OERR)
				U1STAbits.OERR = 0; //������������ ������
		}
	} while(1);
}


void UsartInit(void)
{
	rs485_init();

	//�����
	TRISFbits.TRISF2 = 1;     //RX
	TRISFbits.TRISF3 = 0;     //TX

	//������ usart
#if 0 
	/* NOTE: We have problem with BRGH = 1
	   errata https://ww1.microchip.com/downloads/en/DeviceDoc/80446f.pdf
	   "19. Module: UART" - "if BRGH == 1 UART receptions may be corrupted"
	   In our case: sometimes received additional 0-bit with 0 in first byte, other
	   bites received shifted.
	   Instead of 0x64 + 1_in_9bit, I receive 0xC8 + 0_in_9bit
	*/
	U1MODEbits.BRGH = 1;      //High Baud Rate Enable bit
	U1BRG = 86;                //115200��/���= (40*1000*1000��)/(4*(86+1))  
#endif
	U1MODEbits.BRGH = 0;         //High Baud Rate Enable bit
	U1BRG = 21;                //115200��/���: 113636���/���=(40*1000*1000��)/(16*(21+1))  
	//U1BRG = 20;                //115200��/���: 119047���/���=(40*1000*1000��)/(16*(20+1))  

	U1MODEbits.UEN = 0;       //TX RX - ����������, � ������ CTS RTS - ���    
	U1MODEbits.PDSEL = 0;     //8bit �������� ����.
	U1MODEbits.STSEL = 0;     //1 ���� ���
	U1MODEbits.URXINV = 0;    //UxRX Idle state is �1�
		 
	//����������
	U1STAbits.URXISEL = 0;    //���������� �� ������� ���������� �����
	U1STAbits.UTXISEL0 = 0;    //?
	U1STAbits.UTXISEL1 = 0;
	IPC2bits.U1RXIP = 4;  //��������� ���������� =4
	IPC3bits.U1TXIP = 4;  //��������� ���������� =4
	IPC16bits.U1EIP = 4;  //��������� ���������� =4
	IEC0bits.U1TXIE = 0;  //���������� �� �������� ���������
	IEC0bits.U1RXIE = 0;  //���������� �� ����� ���������
	IEC4bits.U1EIE = 0;   //���������� �� ������ ���������
		
	U1MODEbits.UARTEN = 1;    //UART1 is enabled
	U1STAbits.UTXEN = 1;      //Transmit Enable

	IFS0bits.U1TXIF = 0;  //�� ������ ������ ���������� ���� ����������      
	IFS0bits.U1RXIF = 0;
	IFS4bits.U1EIF = 0;
	
	return;
}
