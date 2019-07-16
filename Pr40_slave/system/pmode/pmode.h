#ifndef _PMODE_INCLUDED
#define _PMODE_INCLUDED

//---------константы---------------
#define DEFAULT_PMODE           0
#define DEFAULT_P2_INTERVAL     10 

#define NUMBER_OF_P2_INTERVALS  16 

#define PMODE_P1 1
#define PMODE_P2 2
#define PMODE_P3 3

//---------переменные--------------
extern unsigned char  cfg_pmode;
extern unsigned short cfg_p2_intervals[NUMBER_OF_P2_INTERVALS];

//----------функции----------------
void pmode_change(unsigned int value);
void pmode_eeprom_write_default_values(void);
void pmode_init(void);

#endif



