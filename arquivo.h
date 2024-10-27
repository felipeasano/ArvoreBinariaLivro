#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <ctype.h>

#include "livro.h"
#include "fila.h"

// estrutura de cabecalho para o arquivo .bin
typedef struct cabecalho
{
    int raiz;
    int topo;
    int livre;
} CABECALHO;

// estrutura para arquivo .bin contendo ponteiro para arquivo e cabecalho
typedef struct arquivo_bin
{
    FILE *arq_bin;
    CABECALHO c;
} ARQ_BIN;

// abre arquivo .bin
// pre-condicao: nenhuma
// pos-condicao: nenhuma
// Entrada: Entra com nome do arquivo e a estrutura para arquivo .bin
// Retorno: devolve a estrutura com o arquivo aberto e o cabecalho lido, ou settado
ARQ_BIN abre_arq_bin(char nome_arquivo[], ARQ_BIN b);

// insere livro no arquivo binario
// pre-condicao: arquivo aberto e livro com dados
// pos-condicao: arquivo salvo ou nao, caso ja exista, no arquivo binaria
// entrada: estrutura para arquivo binario e livro
// saida: nenhum
void insereLivro(ARQ_BIN* b, LIVRO l);

// busca por um no da arvore no arquivo binario
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, codigo do livro a ser buscado
// saida: retorna NO encontrado ou null caso nao encontrado
NO *buscaNo(ARQ_BIN b, int cod);

// imprime lista de livros presentes no arquivo ordenando pelo codigo
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, posicao acessada no arquivo
// saida: nenhum
void imprimirArvoreInOrdem(ARQ_BIN b, int pos);

// imprime livros de um autor
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, nome do autor, posicao acessada no arquivo binario
// saida: nenhum
void *buscarPorAutor(ARQ_BIN *b, char *nomeAutor, int pos);

// busca por um livro pelo titulo
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, titulo do livro, posicao acessada no arquivo binario
// saida: NO encontrado ou null caso nao encontrado
NO *buscarPorTitulo(ARQ_BIN *b, char *titulo, int pos);

// imprime a arvore por niveis
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario
// saida: nenhum
void imprimePorNiveis(ARQ_BIN b);

// imprime arvore no formato pre-ordem em lista
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, posicao acessada no arquivo
// saida: nenhum
void imprimeComoLista(ARQ_BIN b, int pos);

// calcula a quantidade total de livros
// pre-condicao: arquivo aberti
// pos-condicao: nenhum
// entrada: arquivo binario, posicao acessada no arquivo
// saida: quantidade de livros
int calculaTotal(ARQ_BIN *arq, int pos);

// imprime uma a lista de NOs livres
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// Entrada: estrutura para arquivo .bin
// Retorno: nenhum
void imprimeLivres(ARQ_BIN b);

// Função para remover espaços no início e no fim de uma string
// pre-condicao: nenhum
// pos-condicao: espacos removidos do inicio e fim de uma string removidos caso houver
// entrada: string a sofrer a mudanca
// saida: string sem espacos no inicio e fim da string
void trim(char *str);

// carrega varios livros atraves de um arquivo texto
// pre-condicao: arquivos abertos
// pos-condicao: livros carregados em lote
// entrada: arquivo binario, arquivo texto
// saida: nenhum
void carregaLote(ARQ_BIN* arq, FILE* arquivo);

// realiza a remocao de um no na arvore binario no arquivo
// pre-condicao: arquivo aberto
// pos-condicao: arquivo atualizado
// Entrada: estrutura para arquivo .bin, cod do NO a ser removido
// Retorno: nenhum
void remover(ARQ_BIN *b, int cod);

#endif
