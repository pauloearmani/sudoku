//Paulo Eduardo Costalonga Armani
//22.1.4019

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"

int main()
{
    int lin, col;
    lin = 9;
    col = 9; // matriz 9x9

    inicio();

    char comando[10];
    Sudoku **sudoku = criaMatriz(lin, col);

    while (1)
    {
        // impressao do jogo
        printf(BOLD(BLUE("\n Digite um comando ou indique a célula a alterar: ")));
        fgets(comando, 10, stdin);

        int tamanho_comando = strlen(comando);
        comando[tamanho_comando - 1] = '\0';

        if (!strcmp(comando, "salvar"))
        {
            char arquivo[64];
            salvarNovo(sudoku, arquivo);
        }
        else if (!strcmp(comando, "sair"))
        {
            sair(sudoku, col);
            return 0;
        }
        else if (!strcmp(comando, "voltar"))
        {
            inicio();
        }
        else if (!strcmp(comando, "0"))
        {
            sair(sudoku, col);
            return 0;
        }
        else if (!strcmp(comando, "1"))
        {
            // gerar um novo jogo
            criaSudoku(sudoku, lin, col);
            imprimeMatriz(sudoku, lin, col);
        }
        else if (!strcmp(comando, "2"))
        {
            // carregar jogo existente
            char arquivo[64];
            abrirArquivo(arquivo);
            preencheMatrizArq(sudoku, arquivo, lin, col);
            imprimeMatriz(sudoku, lin, col);
        }
        else if (!strcmp(comando, "3"))
        {
            // resolver jogo
            resolveSudoku(sudoku, 0, 0);
            imprimeMatriz(sudoku, lin, col);
            sair(sudoku, col);
        }

        else if (tamanho_comando == 4)
        {

            if ((comando[0] < '1' || comando[0] > '9') ||
                (comando[1] < '1' || comando[1] > '9') ||
                (comando[2] < '1' || comando[2] > '9'))
            {
                printf(BOLD(RED("\n\tEste não é um valor válido para o Sudoku.\n")));
            }
            else
            {
                int erro;
                erro = insereNumero(sudoku, comando[0] - 49, comando[1] - 49, comando[2] - 48);
                imprimeMatriz(sudoku, lin, col);
                if (!erro)
                {
                    printf(BOLD(GREEN("\n\tSucesso!")) "\n");
                    if (verificarVitoria(sudoku))
                    {
                        vitoria();
                    }
                    else if (!verificarDerrota(sudoku))
                    {
                        imprimeMatriz(sudoku, lin, col);
                        derrota();
                    }
                }
                else if (erro == -2)
                {
                    printf(BOLD(RED("\n\tErro! A coluna %c já possui o valor %c.\n")), comando[1], comando[2]);
                }
                else if (erro == -3)
                {
                    printf(BOLD(RED("\n\tErro! A região %d já possui o valor %c.\n")),
                           regiaoSudoku(comando[0] - 49, comando[1] - 49), comando[2]);
                }
                else if (erro == -4)
                {
                    printf(BOLD(RED("\n\tErro! A célula %c,%c já possui um valor.\n")), comando[0], comando[1]);
                }
                else if (erro == -1)
                {
                    printf(BOLD(RED("\n\tErro! A linha %c já possui o valor %c.\n")), comando[0], comando[2]);
                }
            }
        }
        else
        {
            printf(BOLD(RED("\n\tComando inválido. Favor conferir a sintaxe.\n")));
        }
    }

    return 0;
}