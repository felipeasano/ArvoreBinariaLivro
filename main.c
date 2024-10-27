#include "arquivo.h"

// imprime menu de funcoes do trabalho
// pre-condicao: nenhum
// pos-condicao: nenhum
// entrada: nenhum
// saida: nenhum
void imprime_menu()
{
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

int main()
{

    ARQ_BIN arq = abre_arq_bin("arquivo", arq);
    NO *no = (NO *)malloc(sizeof(NO));
    FILE *arquivo = NULL;

    int opcao, cod;
    char temp[100];

    do
    {
        system("cls");
        imprime_menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            printf("Fim do Programa.\n");
            break;
        case 1: // Cadastrar Livro
            no->livro = recebeLivro();
            insereLivro(&arq, no->livro);
            break;
        case 2: // Remover Livro
            if (arq.c.raiz == -1)
            {
                printf("Sem livros...\n");
                continue;
            }
            else
            {
                printf("Entre com o codigo do livro a ser removido: ");
                scanf("%d", &cod);
                remover(&arq, cod);
            }
            break;
        case 3: // Buscar Livro
            printf("Entre com o codigo do livro a ser buscado: ");
            scanf("%d", &cod);
            no = buscaNo(arq, cod);
            imprimeLivro(no->livro);
            break;
        case 4: // Listar Livro
            if (arq.c.raiz == -1)
            {
                printf("Sem livros...\n");
                continue;
            }
            else
                imprimirArvoreInOrdem(arq, arq.c.raiz);
            break;
        case 5: // Imprimir por niveis
            if (arq.c.raiz == -1)
            {
                printf("Arvore vazia...\n");
                continue;
            }
            else
                imprimePorNiveis(arq);
            break;
        case 6: // Imprimir como lista
            if (arq.c.raiz == -1)
            {
                printf("Arvore vazia...\n");
                continue;
            }
            else
                imprimeComoLista(arq, arq.c.raiz);
            printf("\n");
            break;
        case 7: // Buscar por autor
            if (arq.c.raiz == -1)
            {
                printf("Arvore vazia...\n");
                continue;
            }
            else
            {
                printf("Entre com o nome do Autor: ");
                fflush(stdin);
                fgets(temp, sizeof(temp), stdin);
                temp[strcspn(temp, "\n")] = '\0';
                trim(temp);
                buscarPorAutor(&arq, temp, arq.c.raiz);
                printf("[%s]\n");
            }
            break;
        case 8: // Buscar por titulo
            if (arq.c.raiz == -1)
            {
                printf("Arvore vazia...\n");
                continue;
            }
            else
            {
                printf("Entre com o titulo do livro: ");
                fflush(stdin);
                fgets(temp, sizeof(temp), stdin);
                temp[strcspn(temp, "\n")] = '\0';
                no = buscarPorTitulo(&arq, temp, arq.c.raiz);
                if (no != NULL)
                {
                    imprimeLivro(no->livro);
                }
                else
                {
                    printf("Livro nao encontrado\n");
                }
            }
            break;
        case 9: // Calcular Total
            printf("Total de Livros: %d\n", calculaTotal(&arq, arq.c.raiz));
            break;
        case 10: // Carregar Arquivo
            printf("Entre com o nome do arquivo: ");
            fflush(stdin);
            fgets(temp, sizeof(temp), stdin);
            temp[strcspn(temp, "\n")] = '\0';

            arquivo = fopen(temp, "r");
            if (arquivo == NULL)
            {
                printf("Erro ao abrir o arquivo!\n");
            }
            else
            {
                carregaLote(&arq, arquivo);
                fclose(arquivo);
            }
            break;
        case 11: // Imprimir lista de Livres
            if (arq.c.livre == -1)
            {
                printf("Sem posicoes livres ainda...\n");
            }
            else
            {
                imprimeLivres(arq);
            }
            break;
        default:
            printf("Opcaoo invalida. Tente novamente!\n");
        }
        system("pause");
    } while (opcao != 0);

    free(no);
    fclose(arq.arq_bin);
    return 0;
}
