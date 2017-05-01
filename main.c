// Engenharia de Sistemas Embarcados
// Carlos Hatus
// Yan Kaic

#include <xc.h>
#define _XTAL_FREQ 4000000
#include "lcd.h";
#include "teclado.h";

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
void selecionar();
void discar();
void adicionar();
void ativaModo();
void desativaModo();
void testaModo();
void digitarNome();
void digitarNumero();
void capturaLetra();
void capturaNumero();
void apaga();
void buscar();
void armazenar();
void chamar();
void desligar();

// Variáveis globais
bit modo = 0b0;
char entrada; // armazena o ultimo caractere digitado.
int estado = 0;

int main() {
    unsigned char i, tmp;

    CMCON = 0x07;
    TRISA = 0x30;
    TRISB = 0xE7;

    PORTA = 0xFE;
    PORTB = 0x00;
    lcd_init();
    lcd_cmd(L_CLR);

    while (1){
        switch (estado){
            case 0:
                capturaNumero(); // espera o usuario digitar
                discar();
                break;
            case 1:
                capturaNumero(); // espera o usuario digitar
                adicionar();
                break;
            case 2:
                break;
            case 3:
                digitarNumero();
                break;
            case 4:
                digitarNome();
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
        }
    }
}

void interrupt interrupcao() {

}

void discar() {
    switch(entrada){
        case '*':
            estado = 1;
            break;
        case '#':
            desativaModo();
            estado = 3; // digitar numero
            break;
        default:
            break;
    }
}

void adicionar() {
    switch(entrada){
        case '*':
            estado = 0;
            break;
        case '#':
            ativaModo();
            estado = 4; // digitar nome
            break;
        default:
            break;
    }
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

void capturaLetra() {
    entrada = tc_letra(0);
}

void capturaNumero() {
    entrada = tc_tecla(0);
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