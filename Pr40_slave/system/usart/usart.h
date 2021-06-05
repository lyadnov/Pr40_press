#ifndef _USART_INCLUDED
#define _USART_INCLUDED

void rs485_send_on(void);
void rs485_send_off(void);

void UsartTxByteX(char data);
char UsartRxByte(unsigned char *data);
char UsartRxByte_withTimeout(unsigned char *data);
void UsartWaitForSilence(void);

void UsartInit(void);

#endif


