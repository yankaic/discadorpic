// Engenharia de Sistemas Embarcados
// Carlos Hatus
// Yan Kaic

#include <xc.h>
#define _XTAL_FREQ 4000000
#include "lcd.h";

// CONFIG
#pragma config FOSC = EXTRCCLK  // Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, Resistor and Capacitor on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF    

void interrupt interrupcao();
void discar();
void adicionar();
void ativaModo();
void desativaModo();
void testaModo();
void digitarNome();
void digitarNumero();
void capturaNome();
void capturaNumero();
void apaga();
void buscar();
void armazenar();
void chamar();
void desligar();
bit modo = 0b0;

int main() {
    unsigned char i, tmp;

    CMCON = 0x07;
    TRISA = 0x30;
    TRISB = 0xE7;

    PORTA = 0xFE;
    PORTB = 0x00;
    lcd_init();
    lcd_cmd(L_CLR);

    while (1);
}

void interrupt interrupcao() {

}

void discar() {

}

void adicionar() {

}

void ativaModo() {
    modo = 0b1;
}

void desativaModo() {
    modo = 0b0;
}

void testaModo() {

}

void digitarNome() {

}

void digitarNumero() {

}

void capturaNome() {

}

void capturaNumero() {

}

void apaga() {

}

void buscar() {

}

void armazenar() {

}

void chamar() {

}

void desligar() {

}

