#ifndef _EEPROM_INCLUDED
#define _EEPROM_INCLUDED

//---------���������---------------
#define FLASH_BLOCK_SIZE             0x400              //� ������: 2�����=3�����   
#define ADDR_FLASH_END               0x015800

#define EEPROM_SIZE                  192                //� ������ 
#define ADDR_EEPROM_START (ADDR_FLASH_END-(EEPROM_SIZE/3)*2)
#define ADDR_BLOCK_WITH_EEPROM_START (ADDR_FLASH_END-FLASH_BLOCK_SIZE)

//������ � EEPROM
#define ADDR_EEPROM_VERSION          0x00
#define ADDR_EEPROM_SLAVE_ADDR       0x05                //����� ������ 1 ����
#define ADDR_EEPROM_START_PAUSE      0x06                //��������� ����� ����� ����������� �� ���� �������� 2 �����
#define ADDR_EEPROM_MEASURE_INTERVAL 0x08                //�������� ����� �������, 2 �����
#define ADDR_EEPROM_K1               0x0A                //�1, 2 �����
#define ADDR_EEPROM_K2               (ADDR_EEPROM_K1+2)
#define ADDR_EEPROM_K3               (ADDR_EEPROM_K1+4)
#define ADDR_EEPROM_K4               (ADDR_EEPROM_K1+6)
#define ADDR_EEPROM_K5               (ADDR_EEPROM_K1+8)
#define ADDR_EEPROM_K6               (ADDR_EEPROM_K1+10)
#define ADDR_EEPROM_K7               (ADDR_EEPROM_K1+12)
#define ADDR_EEPROM_K8               (ADDR_EEPROM_K1+14)
#define ADDR_EEPROM_K9               (ADDR_EEPROM_K1+16)
#define ADDR_EEPROM_K10              (ADDR_EEPROM_K1+18) //�10


//---------����������--------------

//----------�������----------------
unsigned char eeprom_read(unsigned char addr);
void eeprom_read_buf(unsigned char addr,unsigned char *buf,unsigned char size);
void eeprom_write_byte(unsigned char addr,unsigned char data);
void eeprom_write_word(unsigned char addr,unsigned short data);
void eeprom_write_buf(unsigned char addr,unsigned char *buf,unsigned char size);

#endif



