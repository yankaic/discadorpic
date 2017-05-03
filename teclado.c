#include <xc.h>
#include "teclado.h"
#include "atraso.h"

const unsigned char linha[4] = {TL1, TL2, TL3, TL4};

unsigned char tc_tecla(unsigned int timeout) {
    unsigned int to = 0;
    unsigned char i;
    unsigned char ret = 0;
    unsigned char tmp = PORTA;

    while (((to < timeout) || (!timeout))&&(!ret)) {
        for (i = 0; i < 4; i++) {
            PORTA |= linha[i];
            if (TC1) {
                atraso_ms(20);
                if (TC1) {
                    while (TC1);
                    ret = 1 + (i * 3);
                    break;
                }
            };
            if (TC2) {
                atraso_ms(20);
                if (TC2) {
                    while (TC2);
                    ret = 2 + (i * 3);
                    break;
                }
            };
            if (TC3) {
                atraso_ms(20);
                if (TC3) {
                    while (TC3);
                    ret = 3 + (i * 3);
                    break;
                }
            };
            PORTA &= ~linha[i];
        };
        atraso_ms(5);
        to += 5;
    }

    if (!ret)ret = 255;
    else if (ret == 10)ret = 0x2A; // *
    else if (ret == 11)ret = 0x30; // 0
    else if (ret == 12)ret = 0x23; // #
    else ret += 0x30; // [1..9]
    PORTA = tmp;
    return ret;
}

unsigned char tc_letra(unsigned int timeout) {
    unsigned char num = tc_tecla(0);
    unsigned char num2;
    unsigned char ret;
    int cont = 0;
    switch (num) {
        case '0':
            return;
        case '1':
            break;
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '8':
            for (int i = 1; i < 3; i++) {
                num2 = tc_tecla(200);
                if (num == num2) {
                    cont++;
                } else break;
            }
            break;
        case '7':
        case '9':
            for (int i = 1; i < 4; i++) {
                num2 = tc_tecla(200);
                if (num == num2) {
                    cont++;
                } else break;
            }
            break;
        case '*':
            break;
        case '#':
            break;
        default:
            break;
    }
    switch (num) {
        case '1':
            ret = 0x20;
            break;
        case '2':
            ret = 0x41 + cont;
            break;
        case '3':
            ret = 0x44 + cont;
            break;
        case '4':
            ret = 0x47 + cont;
            break;
        case '5':
            ret = 0x4A + cont;
            break;
        case '6':
            ret = 0x4D + cont;
            break;
        case '7':
            ret = 0x50 + cont;
            break;
        case '8':
            ret = 0x54 + cont;
            break;
        case '9':
            ret = 0x57 + cont;
            break;
        case '*':
        case '#':
            ret = num;
            break;
        default:
            break;
    }
    return ret;
}
