#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void imprimeLivro(LIVRO* livro);

LIVRO* recebeLivro();

#endif