#include "livro.h"


// imprime dados de um livro
// pre-condicao: nenhum
// pos-condicao: nenhum
// entrada: livro
// saida: nenhum
void imprimeLivro(LIVRO livro){
    printf("\nCodigo: %d\n", livro.cod);
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Editora: %s\n", livro.editora);
    printf("Edicao: %d\n", livro.edicao);
    printf("Ano: %d\n", livro.ano);
    printf("Preco: R$ %.2f\n", livro.preco);
    printf("Estoque: %d\n", livro.estoque);
}

// recebe os dados do livro pelo usuario
// pre-condicao: nenhum
// pos-condicao: livro preenchido com dados infomados pelo usuario
// entrada: nenhum
// saida: livro preenchido com dados infomados pelo usuario
LIVRO recebeLivro(){
    LIVRO livro;
    char tempPreco[50];

    printf("\nEntre com os dados do livro:\n\n");

    printf("Codigo: ");
    scanf("%d", &livro.cod);
    getchar(); // Consome o caractere de nova linha após a entrada do inteiro

    printf("Titulo: ");
    fgets(livro.titulo, sizeof(livro.titulo), stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Autor: ");
    fgets(livro.autor, sizeof(livro.autor), stdin);
    livro.autor[strcspn(livro.autor, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Editora: ");
    fgets(livro.editora, sizeof(livro.editora), stdin);
    livro.editora[strcspn(livro.editora, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Edicao: ");
    scanf("%d", &livro.edicao);

    printf("Ano: ");
    scanf("%d", &livro.ano);

    printf("Preco: ");
    getchar(); // Consome o caractere de nova linha após a entrada do inteiro
    fgets(tempPreco, sizeof(tempPreco), stdin);
    tempPreco[strcspn(tempPreco, "\n")] = '\0'; // Remove o caractere de nova linha
    for(int i = 0; i < strlen(tempPreco); i++){
        if(tempPreco[i] == ','){
            tempPreco[i] = '.';
        }
    }
    livro.preco = atof(tempPreco);

    printf("Estoque: ");
    scanf("%d", &livro.estoque);

    return livro;
}
