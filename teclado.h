#include <xc.h>

#define TL1 0x02
#define TL2 0x04
#define TL3 0x40
#define TL4 0x80

#define TC1 RB7
#define TC2 RB6
#define TC3 RB5

unsigned char tc_tecla(unsigned int timeout); /*timeout=0 no time out*/ 
unsigned char tc_letra(unsigned int timeout);
