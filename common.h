
#define SELECIONE_DISCAR    0
#define SELECIONE_ADICIONAR 1
#define DIGITAR_NUMERO      2
#define DIGITAR_NOME        3
#define CONTATO_ADICIONADO  4
#define CHAMANDO            5
#define DESLIGANDO          6
#define BUSCANDO            7

char entrada; // armazena o ultimo caractere digitado.
unsigned char numero[10];
unsigned char nome[10];


int estado = SELECIONE_DISCAR;