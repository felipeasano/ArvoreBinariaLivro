#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura representando livro
typedef struct livro{
    int cod;
    char titulo[150];
    char autor[200];
    char editora[50];
    int edicao;
    int ano;
    float preco;
    int estoque;
}LIVRO;

// estrutura representando no da arvore
typedef struct no{
    int reg;
    int dir;
    int esq;
    LIVRO livro;
}NO;

// imprime dados de um livro
// pre-condicao: nenhum
// pos-condicao: nenhum
// entrada: livro
// saida: nenhum
void imprimeLivro(LIVRO livro);

// recebe os dados do livro pelo usuario
// pre-condicao: nenhum
// pos-condicao: livro preenchido com dados infomados pelo usuario
// entrada: nenhum
// saida: livro preenchido com dados infomados pelo usuario
LIVRO recebeLivro();

#endif
