//Paulo Eduardo Costalonga Armani
//22.1.4019

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"                                                   

void inicio()
{
    printf(ANSI_BOLD);
    printf(ANSI_COLOR_BLUE);
    puts("\t\t███████╗██╗   ██╗██████╗  ██████╗ ██╗  ██╗██╗   ██╗");
    puts("\t\t██╔════╝██║   ██║██╔══██╗██╔═══██╗██║ ██╔╝██║   ██║");
    puts("\t\t███████╗██║   ██║██║  ██║██║   ██║█████╔╝ ██║   ██║");
    puts("\t\t╚════██║██║   ██║██║  ██║██║   ██║██╔═██╗ ██║   ██║");
    puts("\t\t███████║╚██████╔╝██████╔╝╚██████╔╝██║  ██╗╚██████╔╝");
    puts("\t\t╚══════╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ");
    printf(ANSI_RESET "\n");

    printf(ANSI_BOLD);
    printf(ANSI_COLOR_BLUE);
    puts("\t\t██╗███████╗███████╗███████╗███████╗███████╗█████");
    puts("\t\t█               0. Sair do jogo                █");
    puts("\t\t█              1. Gerar novo jogo              █");
    puts("\t\t█               2. Carregar jogo               █");
    puts("\t\t█               3. Resolver jogo               █");
    puts("\t\t██╗███████╗███████╗███████╗███████╗███████╗█████");
    puts("\t\t█                                              █");
    printf("\t\t█  O comando deve estar no formato ");
    printf("LCV, onde:  █\n\t\t█          ");
    printf(ANSI_BOLD);
    printf(ANSI_COLOR_BLUE);
    printf("L  é a linha, ");
    printf("C  é a coluna,        █\n\t\t█        e ");
    printf("V  é o valor a ser inserido.        █\n");
    printf(ANSI_BOLD);
    printf(ANSI_COLOR_BLUE);
    puts("\t\t█                                              █");
    puts("\t\t██╗███████╗███████╗███████╗███████╗███████╗█████");
    puts("\t\t█                                              █");
    printf("\t\t█               Digite sua opção:              █\n");
    puts("\t\t█                                              █");
    puts("\t\t██╗███████╗███████╗███████╗███████╗███████╗█████");
    puts("\n");
}

Sudoku **criaMatriz(int col, int lin)
{
    Sudoku **matriz;
    matriz = malloc(lin * sizeof(Sudoku *));
    for (int i = 0; i < lin; i++)
    {
        matriz[i] = malloc(col * sizeof(Sudoku));

        for (int j = 0; j < col; j++)
        {
            matriz[i][j].valor = 0;
            matriz[i][j].alteravel = 1;
        }
    }

    return matriz;
}

void liberaMatriz(Sudoku **matriz, int col)
{
    for (int i = 0; i < col; i++)
        free(matriz[i]);
    free(matriz);
}

void sair(Sudoku **matriz, int col)
{
    liberaMatriz(matriz, col);
    printf(BOLD(BLUE("\n\tObrigado por jogar!\a\n\n")));
    exit(0);
}

void abrirArquivo(char *arquivo)
{
    printf(BOLD(BLUE(" Indique o arquivo texto contendo o jogo: ")));
    fgets(arquivo, 64, stdin);

    // tratamento da string
    int tamanho = strlen(arquivo);
    arquivo[tamanho - 1] = '\0';
}

void imprimeMatriz(Sudoku **matriz, int lin, int col)
{
    printf("\n\t\t\t\t");
    printf(TAB_TL TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_TJ
               TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR
                   TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_TR "\n");
    for (int i = 0; i < lin; i++)
    {
        printf("\t\t\t\t");
        printf(TAB_VER " ");
        for (int j = 0; j < col; j++)
        {
            if (matriz[i][j].valor == 0)
            {
                printf("_ ");
            }
            else
            {
                printf("%d ", matriz[i][j].valor);
            }
            if ((j + 1) % 3 == 0)
            {
                printf(TAB_VER " ");
            }
        }
        if ((i + 1) == 9)
        {
            printf("\n\t\t\t\t" TAB_BL TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_BJ
                       TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR
                           TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_BR);
        }
        else if ((i + 1) % 3 == 0)
        {
            printf("\n\t\t\t\t" TAB_ML TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_MJ
                       TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR
                           TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_MR);
        }
        printf("\n");
    }
}

int testeLinha(Sudoku **matriz, int lin, char valor)
{
    for (int i = 0; i < 9; i++)
    {
        if (matriz[lin][i].valor == valor)
        {
            return 0;
        }
    }
    return 1;
}

int testeColuna(Sudoku **matriz, int col, char valor)
{
    for (int i = 0; i < 9; i++)
    {
        if (matriz[i][col].valor == valor)
        {
            return 0;
        }
    }
    return 1;
}

int testeRegiao(Sudoku **matriz, int lin, int col, char valor)
{
    int lin_inicio, col_inicio;
    if (lin < 3)
    {
        lin_inicio = 0;
    }
    else if (lin < 6)
    {
        lin_inicio = 3;
    }
    else
    {
        lin_inicio = 6;
    }

    if (col < 3)
    {
        col_inicio = 0;
    }
    else if (col < 6)
    {
        col_inicio = 3;
    }
    else
    {
        col_inicio = 6;
    }

    for (int i = lin_inicio; i < lin_inicio + 3; i++)
    {
        for (int j = col_inicio; j < col_inicio + 3; j++)
        {
            if (matriz[i][j].valor == valor)
            {
                return 0;
            }
        }
    }
    return 1;
}

int regiaoSudoku(int lin, int col)
{
    int lin_inicio, col_inicio, regiao;
    if (lin < 3)
    {
        lin_inicio = 0;
    }
    else if (lin < 6)
    {
        lin_inicio = 3;
    }
    else
    {
        lin_inicio = 6;
    }

    if (col < 3)
    {
        col_inicio = 0;
    }
    else if (col < 6)
    {
        col_inicio = 3;
    }
    else
    {
        col_inicio = 6;
    }

    if (lin_inicio == 0 && col_inicio == 0)
    {
        regiao = 1;
    }
    else if (lin_inicio == 0 && col_inicio == 3)
    {
        regiao = 2;
    }
    else if (lin_inicio == 0 && col_inicio == 6)
    {
        regiao = 3;
    }
    else if (lin_inicio == 3 && col_inicio == 0)
    {
        regiao = 4;
    }
    else if (lin_inicio == 3 && col_inicio == 3)
    {
        regiao = 5;
    }
    else if (lin_inicio == 3 && col_inicio == 6)
    {
        regiao = 6;
    }
    else if (lin_inicio == 6 && col_inicio == 0)
    {
        regiao = 7;
    }
    else if (lin_inicio == 6 && col_inicio == 3)
    {
        regiao = 8;
    }
    else
    {
        regiao = 9;
    }
    return regiao;
}

int insereNumero(Sudoku **matriz, int lin, int col, char valor)
{
    if (matriz[lin][col].alteravel)
    {
        if (!testeLinha(matriz, lin, valor))
        {
            return -1;
        }
        else if (!testeColuna(matriz, col, valor))
        {
            return -2;
        }
        else if (!testeRegiao(matriz, lin, col, valor))
        {
            return -3;
        }
        matriz[lin][col].valor = valor;
        return 0;
    }
    return -4;
}

int verificarVitoria(Sudoku **matriz)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (matriz[i][j].valor == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int verificarDerrota(Sudoku **matriz)
{
    int contador;
    for (int m = 0; m < 9; m++)
    {
        for (int n = 0; n < 9; n++)
        {
            contador = 0;
            for (char valor_teste = '1'; valor_teste <= '9'; valor_teste++)
            {
                if (matriz[m][n].valor == '0')
                {
                    if (!testeLinha(matriz, m, valor_teste) || !testeColuna(matriz, n, valor_teste) || !testeRegiao(matriz, m, n, valor_teste))
                    {
                        contador++;
                    }
                }
            }
            if (contador == 9)
            {
                return 0;
            }
        }
    }
    return 1;
}

void vitoria()
{
    printf(ANSI_COLOR_GREEN);
    printf(ANSI_BOLD);
    printf("\n\n");
    puts("\t███╗   ██╗███████╗███╗   ██╗ ██████╗███████╗██╗   ██╗");
    puts("\t██║   ██║██╔════╝████╗  ██║██╔════╝██╔════╝██║   ██║");
    puts("\t██║   ██║█████╗  ██╔██╗ ██║██║     █████╗  ██║   ██║");
    puts("\t╚██╗ ██╔╝██╔══╝  ██║╚██╗██║██║     ██╔══╝  ██║   ██║");
    puts("\t ╚████╔╝ ███████╗██║ ╚████║╚██████╗███████╗╚██████╔╝");
    puts("\t  ╚═══╝  ╚══════╝╚═╝  ╚═══╝ ╚═════╝╚══════╝ ╚═════╝ ");
    printf("\n\a");
    exit(0);
}

void derrota()
{
    printf(ANSI_COLOR_RED);
    printf(ANSI_BOLD);
    printf("\n\n");
    puts("\t██████╗ ███████╗██████╗ ██████╗ ███████╗██╗   ██╗");
    puts("\t██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔════╝██║   ██║");
    puts("\t██████╔╝█████╗  ██████╔╝██║  ██║█████╗  ██║   ██║");
    puts("\t██╔═══╝ ██╔══╝  ██╔══██╗██║  ██║██╔══╝  ██║   ██║");
    puts("\t██║     ███████╗██║  ██║██████╔╝███████╗╚██████╔╝");
    puts("\t╚═╝     ╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝ ╚═════╝ ");
    printf("\n\a");
    exit(0);
}

void salvarNovo(Sudoku **matriz, char *arquivo)
{
    char arq[100];

    // Lê o nome do novo arquivo do usuário
    printf(BOLD(GREEN("Digite o nome do arquivo: ")));
    fgets(arq, 100, stdin);

    // Remove o caractere de quebra de linha (\n) do final da string do nome do arquivo
    arq[strcspn(arq, "\n")] = 0;

    // Cria um novo arquivo com o nome fornecido pelo usuário
    FILE *novoArq;
    novoArq = fopen(arq, "w");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fprintf(novoArq, "%d ", matriz[i][j].valor);
        }
        fprintf(novoArq, "\n");
    }

    fclose(novoArq);
    printf(BOLD(GREEN("\n\tJogo foi salvo em ")));
    printf("%s\n", arq);
}

int possivel(Sudoku **matriz, int lin, int col, int num)
{

    // Check if we find the same num
    // in the similar lin , we
    // return 0
    for (int i = 0; i <= 8; i++)
        if (matriz[lin][i].valor == num)
            return 0;

    // Check if we find the same num in
    // the similar column , we
    // return 0
    for (int i = 0; i <= 8; i++)
        if (matriz[i][col].valor == num)
            return 0;

    // Check if we find the same num in
    // the particular 3*3 matrix,
    // we return 0
    int xInicial = lin - lin % 3;
    int yInicial = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (matriz[i + xInicial][j + yInicial].valor == num)
                return 0;

    return 1;
}

int resolveSudoku(Sudoku **matriz, int lin, int col)
{
    if (lin == 8 && col == 9)
    {
        char *arquivo = criaArquivo(matriz, lin + 1, col);
        preencheMatrizArq(matriz, arquivo, lin + 1, col);
        return 1;
    }

    if (col == 9)
    {
        lin++;
        col = 0;
    }

    if (matriz[lin][col].valor > 0)
        return resolveSudoku(matriz, lin, col + 1);

    for (int num = 1; num <= 9; num++)
    {
        if (possivel(matriz, lin, col, num))
        {
            matriz[lin][col].alteravel = 0;
            matriz[lin][col].valor = num;

            if (resolveSudoku(matriz, lin, col + 1))
                return 1;
        }

        matriz[lin][col].valor = 0;
    }
    return 0;
}

void criaSudoku(Sudoku **matriz, int lin, int col)
{
    srand(time(NULL));
    char nivel;
    printf("Escolha o nível do jogo, fácil (F) ou difícil (D): ");
    scanf("%c", &nivel);

    for (int i = 0; i < lin; i++)
    {

        int linha = rand() % lin;
        int coluna = rand() % col;
        matriz[linha][coluna].valor = i;
    }
    char *arquivo = criaArquivo(matriz, lin, col);
    resolveSudoku(matriz, 0, 0);

    int coefDificuldade;
    if(nivel == 'F')
    {
        coefDificuldade = 4;
    } else {
        coefDificuldade = 1;
    }

    for (int i = 0; i < lin - coefDificuldade; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int linha = rand() % lin;
            int coluna = rand() % col;
            matriz[linha][coluna].alteravel = 1;
            matriz[linha][coluna].valor = 0;
        }
    }

    arquivo = criaArquivo(matriz, lin, col);

    preencheMatrizArq(matriz, arquivo, lin, col);
}

void opcao(char comando[10])
{
    printf(BOLD(BLUE(" Digite sua opção: ")));
    scanf("%s", comando);

    // tratamento da string
    int tamanho = strlen(comando);
    comando[tamanho - 1] = '\0';
}

char *criaArquivo(Sudoku **matriz, int lin, int col)
{
    FILE *arq = fopen("sudoku.txt", "w");

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {

            fprintf(arq, "%d ", matriz[i][j].valor);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
    return "sudoku.txt";
}

void preencheMatrizArq(Sudoku **matriz, char *arquivo, int lin, int col)
{
    FILE *entrada = fopen(arquivo, "r");
    while (entrada == NULL)
    {
        printf(BOLD(RED("\t Não é possível iniciar um jogo a partir deste arquivo.\n\n")));
        abrirArquivo(arquivo);
        entrada = fopen(arquivo, "r");
    }

    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fscanf(entrada, "%d ", &matriz[i][j].valor);
            if (matriz[i][j].valor == 0)
            {
                matriz[i][j].alteravel = 1;
            }
            else
            {
                matriz[i][j].alteravel = 0;
            }
        }
    }
    fclose(entrada);
}