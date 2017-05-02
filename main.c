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
unsigned char numero[9];
unsigned char nome[9];
unsigned char endereco;
unsigned char quantidade;

int main() {
    unsigned char i, tmp;

    CMCON = 0x07;
    TRISA = 0x30;
    TRISB = 0xE7;

    PORTA = 0xFE;
    PORTB = 0x00;
    lcd_init();
    lcd_cmd(L_CLR);

    endereco = 0x0;
    eeprom_write(endereco, endereco++);

    while (1) {
        endereco = eeprom_read(0x0);
        switch (estado) {
            case 0:
                capturaNumero(); // espera o usuario digitar
                discar();
                break;
            case 1:
                capturaNumero(); // espera o usuario digitar
                adicionar();
                break;
            case 3:
                digitarNumero();
                break;
            case 4:
                digitarNome();
                break;
            case 5:
                buscar();
                break;
            case 6:
                armazenar();
                break;
            default:
                break;
        }
    }
    return 0;
}

void interrupt interrupcao() {

}

void discar() {
    switch (entrada) {
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
    switch (entrada) {
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

void digitarNome() {
    capturaLetra();
    int cont = 0;
    while (entrada != '#' && cont < 9) {
        if (entrada == '*' && cont > 0) {
            cont--;
            // apaga valor da tela
        }
        nome[cont] = entrada;
        capturaLetra();
        cont++;
    }
    if (cont < 9) {
        for (; cont < 9; cont++) {
            nome[cont] = ' ';
        }
    }
    estado = 3;
}

void digitarNumero() {
    capturaNumero();
    int cont = 0;
    while (entrada != '#' && cont < 9) {
        if (entrada == '*' && cont > 0) {
            cont--;
            // apaga valor da tela
        }
        numero[cont] = entrada;
        capturaNumero();
        cont++;
    }
    if (cont < 9) {
        for (; cont < 9; cont++) {
            numero[cont] = ' ';
        }
    }
    if (modo) {
        estado = 6;
    } else estado = 5;
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
    unsigned char end = 0x1;
    static bit achou = 0b0;
    while (end < endereco) {
        achou = 0b1;
        for (int i = 0; i < 9; i++) {
            int num = eeprom_read(end + i);
            if (num != numero[i]) {
                achou = 0b0;
                break;
            }
        }
        end += 9;
        if (achou) {
            for (int i = 0; i < 9; i++) {
                nome[i] = eeprom_read(end);
                end++;
                break;
            }
        } else end += 9;
    }
    if (achou) {
        chamar();
    } else {
        // escreve desconhecido
    }
}

void armazenar() {
    for (int i = 0; i < 9; i++) {
        eeprom_write(endereco, numero[i]);
        endereco++;
    }
    for (int i = 0; i < 9; i++) {
        eeprom_write(endereco, nome[i]);
        endereco++;
    }
    eeprom_write(0x0, endereco);
}

void chamar() {
    __delay_ms(5000);
    desligar();
}

void desligar() {
    __delay_ms(1000);
    estado = 0;
}