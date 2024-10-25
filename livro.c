#include "livro.h"

void imprimeLivro(LIVRO* livro){
    printf("\nCodigo: %d\n", livro->cod);
    printf("Titulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Editora: %s\n", livro->editora);
    printf("Edicao: %d\n", livro->edicao);
    printf("Ano: %d\n", livro->ano);
    printf("Preco: %.2f\n", livro->preco);
    printf("Estoque: %d\n", livro->estoque);
}

LIVRO* recebeLivro(){
    LIVRO* livro = (LIVRO*)malloc(sizeof(LIVRO));
    char tempPreco[50];

    printf("\nEntre com os dados do livro:\n\n");

    printf("Codigo: ");
    scanf("%d", &livro->cod);
    getchar(); // Consome o caractere de nova linha após a entrada do inteiro

    printf("Titulo: ");
    fgets(livro->titulo, sizeof(livro->titulo), stdin);
    livro->titulo[strcspn(livro->titulo, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Autor: ");
    fgets(livro->autor, sizeof(livro->autor), stdin);
    livro->autor[strcspn(livro->autor, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Editora: ");
    fgets(livro->editora, sizeof(livro->editora), stdin);
    livro->editora[strcspn(livro->editora, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Edicao: ");
    scanf("%d", &livro->edicao);

    printf("Ano: ");
    scanf("%d", &livro->ano);

    printf("Preco: ");
    getchar(); // Consome o caractere de nova linha após a entrada do inteiro
    fgets(tempPreco, sizeof(tempPreco), stdin);
    tempPreco[strcspn(tempPreco, "\n")] = '\0'; // Remove o caractere de nova linha
    for(int i = 0; i < strlen(tempPreco); i++){
        if(tempPreco[i] == ','){
            tempPreco[i] = '.';
        }
    }
    livro->preco = atof(tempPreco);

    printf("Estoque: ");
    scanf("%d", &livro->estoque);

    return livro;
}