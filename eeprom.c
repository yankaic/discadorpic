#include <xc.h>
#pragma config FOSC = EXTRCCLK  // Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, Resistor and Capacitor on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define _XTAL_FREQ 4000000
void main(void) {
    TRISA = 0; //Todos os pinos do PORTB como saída
    TRISB = 0; //Todos os pinos do PORTB como saída
    CMCON = 7;
    INTCON = 0;
    OPTION_REG = 128;

    unsigned char valor;
    unsigned char end = 0;
    //eeprom_write(end, valor);

    //char valorb = eeprom_read(end);
    char valorb;

    while (1) {
        for (int i = 0; i < 256; i++) {
            valor = i;
            eeprom_write(end, valor);
            __delay_ms(1000);
            valorb = eeprom_read(end);
            PORTB = valorb;
        }
    }

    return;
}
