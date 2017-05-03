// Engenharia de Sistemas Embarcados
// Carlos Hatus
// Yan Kaic

#include <xc.h>
#define _XTAL_FREQ 4000000
#include "common.h";
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
void discar();
void adicionar();
void ativaModo();
void desativaModo();
void digitarNome();
void digitarNumero();
void buscar();
void armazenar();
void chamar();
void desligar();
void maquina();

// Variáveis globais
bit modo = 0b0;
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

    unsigned char val = eeprom_read(0x0);
    if (val = 255) { // endereco vazio só salva na primeira execução
        eeprom_write(0x0, 0x1);
        endereco = eeprom_read(0x0);
    }

    while (1) {
        maquina();
    }
    return 0;
}

void interrupt interrupcao() {

}

void maquina() {
    endereco = eeprom_read(0x0);
    switch (estado) {
        case SELECIONE_DISCAR:
            discar();
            break;
        case SELECIONE_ADICIONAR:
            adicionar();
            break;
        case DIGITAR_NUMERO:
            digitarNumero();
            break;
        case DIGITAR_NOME:
            digitarNome();
            break;
        case BUSCANDO:
            buscar();
            break;
        case CHAMANDO:
            chamar();
            break;
        case CONTATO_ADICIONADO:
            armazenar();
            break;
        case DESLIGANDO:
            desligar();
            break;
        default:
            break;
    }
}

void discar() {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Discar");
    entrada = tc_tecla(0);

    switch (entrada) {
        case '*':
            estado = SELECIONE_ADICIONAR;
            break;
        case '#':
            desativaModo();
            estado = DIGITAR_NUMERO; // digitar numero
            break;
        default:
            break;
    }

}

void adicionar() {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Adicionar");
    entrada = tc_tecla(0);

    switch (entrada) {
        case '*':
            estado = SELECIONE_DISCAR;
            break;
        case '#':
            ativaModo();
            estado = DIGITAR_NOME; // digitar nome
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
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Digite Nome");
    lcd_cmd(L_L2);
    lcd_str("#########");
    lcd_cmd(L_L2);

    entrada = ' ';
    int cont = 0;
    while (entrada != '#' && cont < 9) {
        entrada = tc_letra(0);
        if(entrada == '#' ){
            break;
        }
        if (entrada == '*' && cont > 0) {
            cont--;

            lcd_cmd(L_L2 + cont);
            continue;
        }
        nome[cont] = entrada;
        cont++;
        lcd_dat(entrada);
    }
    if (cont < 9) {
        for (; cont < 9; cont++) {
            nome[cont] = ' ';
        }
    }
    nome[9] = '\0';
    estado = DIGITAR_NUMERO;
}

void digitarNumero() {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Digite Numero");
    lcd_cmd(L_L2);
    lcd_str("#########");
    lcd_cmd(L_L2);
    entrada = ' ';

    int cont = 0;
    while (entrada != '#' && cont < 9) {
        if(entrada == '#' ){
            break;
        }
        entrada = tc_tecla(0);
        if (entrada == '*' && cont > 0) {
            cont--;
            lcd_cmd(L_L2 + cont);
            continue;
        }
        numero[cont] = entrada;
        cont++;
        lcd_dat(entrada);
    }
    if (cont < 9) {
        for (; cont < 9; cont++) {
            numero[cont] = '#';
        }
    }
    numero[9] = '\0';
    if (modo) {
        estado = CONTATO_ADICIONADO;
    } else {
        estado = BUSCANDO;
    }
}

void buscar() {
    unsigned char end = 0x1;
    static bit achou = 0b0;
    while (end < endereco) {
        achou = 0b1;
        for (int i = 0; i < 9 && numero[i] != '\0'; i++) {
            int num = eeprom_read(end + i);
            if (num != numero[i]) {
                achou = 0b0;
                break;
            }
        }
        end += 10;
        if (achou) {
            for (int i = 0; i < 9; i++) {
                nome[i] = eeprom_read(end);
                end++;
            }
            nome[9] = '\0';
            break;
        } else end += 10;
    }
    if (!achou) {
        nome[0] = 'u';
        nome[1] = 'n';
        nome[2] = 'k';
        nome[3] = 'n';
        nome[4] = 'o';
        nome[5] = 'w';
        nome[6] = 'n';
        nome[7] = '\0';

    }
    estado = CHAMANDO;
}

void armazenar() {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Armazenando...");

    for (int i = 0; i < 10; i++) {
        eeprom_write(endereco, numero[i]);
        endereco++;
    }
    for (int i = 0; i < 10; i++) {
        eeprom_write(endereco, nome[i]);
        endereco++;
    }
    eeprom_write(0x0, endereco);


    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Salvo!");
    tc_tecla(200);
    estado = SELECIONE_DISCAR;
}

void chamar() {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Chamando...");
    lcd_cmd(L_L2);
    lcd_str(nome);

    while (tc_tecla(0) != '#');

    estado = DESLIGANDO;
}

void desligar() {
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Desligando...");

    __delay_ms(1000);
    estado = SELECIONE_DISCAR;
}
