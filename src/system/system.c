#include "system.h"

#define TAMANHO_MATRIZ 620

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define WHITE "\x1B[0m"

#define N_OPCOES 9

#define OPCAO0 '0'
#define OPCAO1 '1'
#define OPCAO2 '2'
#define OPCAO3 '3'
#define OPCAO4 '4'
#define OPCAO5 '5'
#define OPCAO6 '6'
#define OPCAO7 '7'
#define OPCAO8 '8'

void limpa_buffer(void)
{
    int valorLido;
    do
    {
        valorLido = getchar();
    } while ((valorLido != '\n') && (valorLido != EOF));
}

char le_opcao(char menorValor, char maiorValor)
{
    char op;
    char entrada[100];
    char text[50];
    while (1)
    {
        printf("Digite sua opcao: ");
        scanf(" %[^\n]", entrada);
        op = entrada[0];
        if (op >= menorValor && op <= maiorValor && strlen(entrada) == 1)
        {
            limpa_buffer();
            break;
        }
        else
        {
            sprintf(text, "Opcao invalida. A opcao deve estar entre %c e %c.\n", menorValor, maiorValor);
            print_red(text);
            limpa_buffer();
        }
    }
    return op;
}

void menu(void)
{
    printf("Menu:\n");
    printf("========================================\n");
    printf("[1] Verificar conexao entre duas paginas\n");
    printf("[2] Buscar uma pagina\n");
    printf("[3] Exibir quantidade de vertices\n");
    printf("[4] Exibir quantidade de arestas\n");
    printf("[5] Exibir o grau medio do grafo\n");
    printf("[6] Encontrar a pagina mais conectada\n");
    printf("[7] Encontrar a pagina menos conectada\n");
    printf("[8] Exibir paginas isoladas\n");
    printf("[0] Sair\n");
    printf("========================================\n");
}

void print_green(char *text)
{
    printf("%s%s%s", GREEN, text, WHITE);
}

void print_yellow(char *text)
{
    printf("%s%s%s", YELLOW, text, WHITE);
}

void print_red(char *text)
{
    printf("%s%s%s", RED, text, WHITE);
}