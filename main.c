#include "livro.h"

void imprime_menu(){

    printf("Trabalho 2 AED - Arvore Binaria\n\n");

    printf("[0] - Encerrar o programa.\n");
    printf("[1] - Cadastrar livro.\n");
    printf("[2] - Remover livro.\n");
    printf("[3] - Buscar livro.\n");
    printf("[4] - Listar livros.\n");
    printf("[5] - Imprimir arvore por nivel.\n");
    printf("[6] - Imprimir arvore formatada como lista.\n");
    printf("[7] - Buscar por autor.\n");
    printf("[8] - Buscar por titulo.\n");
    printf("[9] - Calcular total.\n");
    printf("[10] - Carregar arquivo.\n");
    printf("[11] - Imprimir lista de registros livres.\n\n");

    printf("Entre com um das opcoes acima: ");
}

// void CadastrarLivro();

// void RemoverLivro();

// void BuscarLivro();

// void ListarLivros();

// void ImprimirArvorePorNiveis();

// void ImprimirArvoreComoLista();

// void BuscarPorAutor();

// void BuscarPorTitulo();

// void CalcularTotal();

// void CarregarArquivo();

// void ImprimirLivres();

int main(){

    int opcao;

    // do{
    //     imprime_menu();
    //     scanf("%d", &opcao);

    //     switch(opcao){
    //         case 1:
    //             // CadastrarLivro();
    //         case 2:
    //             // RemoverLivro();
    //         case 3:
    //             // BuscarLivro();
    //         case 4:
    //             // ListarLivros();
    //         case 5:
    //             // ImprimirArvorePorNiveis();
    //         case 6:
    //             // ImprimirArvoreComoLista();
    //         case 7:
    //             // BuscarPorAutor();
    //         case 8:
    //             // BuscarPorTitulo();
    //         case 9:
    //             // CalcularTotal();
    //         case 10:
    //             // CarregarArquivo();
    //         case 11:
    //             // ImprimirLivres();
    //         default:
    //             printf("Opção invalida. Tente novamente!\n");
    //     }
    // }while(opcao != 0);

    LIVRO* livro = recebeLivro();

    imprimeLivro(livro);

    return 0;
}