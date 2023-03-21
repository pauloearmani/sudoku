//Paulo Eduardo Costalonga Armani
//22.1.4019

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int valor;
    int alteravel;
} Sudoku;

#define ANSI_RESET            "\x1b[0m"  
#define ANSI_BOLD             "\x1b[1m"  
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"

// caracteres das tabelas 
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET

void inicio(); // cabeçalho do programa e instruções

Sudoku **criaMatriz(int col, int lin); // alocando a matriz dinamicamente

void liberaMatriz(Sudoku **matriz, int col); // liberar a matriz alocada dinamicamente

void sair(Sudoku **matriz, int col); // sair do jogo

void abrirArquivo(char* arquivo); // abrir arquivo

void imprimeMatriz(Sudoku **matriz, int lin, int col); // imprimir matriz

int testeLinha(Sudoku **matriz, int lin, char valor); // função testar linha (verifica se o valor já existe na linha)

int testeColuna(Sudoku **matriz, int col, char valor); // função testar coluna (verifica se o valor já existe na coluna)

int testeRegiao(Sudoku **matriz, int lin, int col, char valor); // função testar região (verifica se o valor já existe na matriz 3x3)

int regiaoSudoku(int lin, int col); // verificar regiões do tabuleiro, para impressão no erro

int insereNumero(Sudoku **matriz, int lin, int col, char valor); // usa as funções de teste para efetivamente inserir um número

int verificarVitoria(Sudoku **matriz); // verificar vitória

int verificarDerrota(Sudoku **matriz); // definindo a condição de derrota 

void vitoria(); // impressão de texto de vitória

void derrota(); // impressão do texto de derrota

void salvarNovo(Sudoku **matriz, char* arquivo);

void opcao(char comando[10]);

void criaSudoku(Sudoku **matriz, int lin, int col); // cria o sudoku

int resolveSudoku(Sudoku **matriz, int lin, int col); //resolve o sudoku

int possivel(Sudoku **matriz, int lin, int col, int num); //verifica possibilidades de numeros do sudoku

char *criaArquivo(Sudoku **matriz, int lin, int col); // cria um arquivo

void preencheMatrizArq(Sudoku **matriz, char *arquivo, int lin, int col); //preenche matriz com um arquivo