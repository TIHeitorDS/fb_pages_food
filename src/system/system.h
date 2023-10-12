#ifndef SISTEMA_H
#define SISTEMA_H

// Módulo: funções para tratativas e falhas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lê e descarta caracteres encontrados na entrada
void limpa_buffer(void);

// Lê e valida a opção digitada pelo usuário
char le_opcao(char menorValor, char maiorValor);

// Exibe o menu
void menu(void);

// Imprime em verde
void print_green(char *text);

// Imprime em amarelo
void print_yellow(char *text);

// Imprime em vermelho
void print_red(char *text);

#endif // SISTEMA_H