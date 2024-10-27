#include "arquivo.h"

// abre arquivo .bin
// pre-condicao: nenhuma
// pos-condicao: nenhuma
// Entrada: Entra com nome do arquivo e a estrutura para arquivo .bin
// Retorno: devolve a estrutura com o arquivo aberto e o cabecalho lido, ou settado
ARQ_BIN abre_arq_bin(char nome_arquivo[], ARQ_BIN b)
{
    b.arq_bin = fopen(nome_arquivo, "r+b");
    if (b.arq_bin == NULL)
    {
        // printf("Novo banco aberto!\n");
        b.arq_bin = fopen(nome_arquivo, "w+b");
        b.c.livre = -1;
        b.c.raiz = -1;
        b.c.topo = 0;
        fwrite(&b.c, sizeof(b.c), 1, b.arq_bin);
    }
    else
    {
        // printf("Banco aberto!\n");
        fseek(b.arq_bin, 0, SEEK_SET);
        fread(&b.c, sizeof(b.c), 1, b.arq_bin);
    }
    return b;
}

// grava um NO no arquivo .bin
// pre-condicao: arquivo aberto
// pos-condicao: arquivo atualizado
// Entrada: estrutura para arquivo .bin, NO a ser inserido no arquivo
// Retorno: nenhum
void grava_no(ARQ_BIN *b, NO *no)
{
    fseek(b->arq_bin, sizeof(CABECALHO) + (sizeof(NO) * no->reg), SEEK_SET);
    fwrite(no, sizeof(NO), 1, b->arq_bin);
}

// le um NO do arquivo .bin
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// Entrada: estrutura para arquivo .bin, NO a ser lido do arquivo, numero do registro
// Retorno: nenhum
void carrega_no(ARQ_BIN *b, NO *no, int reg)
{
    fseek(b->arq_bin, sizeof(CABECALHO) + (sizeof(NO) * reg), SEEK_SET);
    fread(no, sizeof(NO), 1, b->arq_bin);
}

// grava o cabecalho no arquivo .bin
// pre-condicao: arquivo aberto
// pos-condicao: arquivo atualizado
// Entrada: estrutura para arquivo .bin
// Retorno: nenhum
void grava_cabecalho(ARQ_BIN *b)
{
    fseek(b->arq_bin, 0, SEEK_SET);
    fwrite(&b->c, sizeof(CABECALHO), 1, b->arq_bin);
}

// carrega o cabecalho do arquivo .bin
// pre-condicao: arquivo aberto
// pos-condicao: cabecalho atualizado
// Entrada: estrutura para arquivo .bin
// Retorno: nenhum
void carrega_cabecalho(ARQ_BIN *b)
{
    fseek(b->arq_bin, 0, SEEK_SET);
    fread(&b->c, sizeof(CABECALHO), 1, b->arq_bin);
}

// funcao que liga o no a arvore binaria, mantendo suas propriedades
// pre-condicao: arquivo deve estar aberto e deve existir um no
// pos-condicao: arvore do arquivo eh atualizada
// Entrada: estrutura de arq binario, NO a ser ligado na arvore e seu registro
// Retorno: retorna a estrutura de arq binario atualizado
void linka_no_arvore(ARQ_BIN *b, NO novo, int reg_atual)
{

    if (b->c.raiz == -1)
    {
        b->c.raiz = 0;
    }
    NO no;
    carrega_no(b, &no, reg_atual);
    if (novo.livro.cod == no.livro.cod)
    {
        return;
    }
    if (novo.livro.cod < no.livro.cod)
    {
        if (no.esq == -1)
        {
            no.esq = novo.reg;
            grava_no(b, &no);
        }
        else
        {
            linka_no_arvore(b, novo, no.esq);
        }
    }
    else
    {
        if (no.dir == -1)
        {
            no.dir = novo.reg;
            grava_no(b, &no);
        }
        else
        {
            linka_no_arvore(b, novo, no.dir);
        }
    }
}

// insere livro no arquivo binario
// pre-condicao: arquivo aberto e livro com dados
// pos-condicao: arquivo salvo ou nao, caso ja exista, no arquivo binaria
// entrada: estrutura para arquivo binario e livro
// saida: nenhum
void insereLivro(ARQ_BIN* b, LIVRO l)
{
    NO no;
    no.livro = l;
    no.dir = -1;
    no.esq = -1;

    if (b->c.livre >= 0)
    {
        no.reg = b->c.livre;
        NO livre;
        carrega_no(b, &livre, b->c.livre);
        b->c.livre = livre.dir;
    }
    else
    {
        no.reg = b->c.topo;
        b->c.topo++;
    }
    grava_cabecalho(b);
    grava_no(b, &no);

    linka_no_arvore(b, no, 0);

    grava_cabecalho(b);
}

// funcao auxiliar na busca de um NO da arvore
// pre-condicao: nenhum
// pos-condicao: nenhum
// entrada: estrutura para arquivo binario, codigo do livro a ser buscado e posicao acessado no arquivo binario
// saida: retorna NO encontrado ou null caso nao encontrado
NO *buscaNoAux(ARQ_BIN *arq, int cod, int pos)
{
    NO *no = (NO *)malloc(sizeof(NO));
    carrega_no(arq, no, pos);
    if (no->livro.cod == cod)
    {
        return no;
    }
    if (no->livro.cod < cod)
    {
        if (no->dir == -1)
        {
            return NULL;
        }
        return buscaNoAux(arq, cod, no->dir);
    }
    if (no->livro.cod > cod)
    {
        if (no->esq == -1)
        {
            return NULL;
        }
        return buscaNoAux(arq, cod, no->esq);
    }
}

// busca por um no da arvore no arquivo binario
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, codigo do livro a ser buscado
// saida: retorna NO encontrado ou null caso nao encontrado
NO *buscaNo(ARQ_BIN b, int cod)
{

    carrega_cabecalho(&b);

    if (b.c.raiz == -1)
        return NULL;
    return buscaNoAux(&b, cod, b.c.raiz);
}

// imprime lista de livros presentes no arquivo ordenando pelo codigo
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, posicao acessada no arquivo
// saida: nenhum
void imprimirArvoreInOrdem(ARQ_BIN b, int pos)
{
    NO no;
    carrega_no(&b, &no, pos);

    if (no.esq != -1)
    {
        imprimirArvoreInOrdem(b, no.esq);
    }
    imprimeLivro(no.livro);
    if (no.dir != -1)
    {
        imprimirArvoreInOrdem(b, no.dir);
    }
}

// imprime livros de um autor
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, nome do autor, posicao acessada no arquivo binario
// saida: nenhum
void *buscarPorAutor(ARQ_BIN *b, char *nomeAutor, int pos)
{

    NO *no = (NO *)malloc(sizeof(NO));
    carrega_no(b, no, pos);

    if (!strcmp(nomeAutor, no->livro.autor))
        imprimeLivro(no->livro);
    if (no->esq != -1)
    {
        buscarPorAutor(b, nomeAutor, no->esq);
    }
    if (no->dir != -1)
    {
        buscarPorAutor(b, nomeAutor, no->dir);
    }

    return NULL;
}

// busca por um livro pelo titulo
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, titulo do livro, posicao acessada no arquivo binario
// saida: NO encontrado ou null caso nao encontrado
NO *buscarPorTitulo(ARQ_BIN *b, char *titulo, int pos)
{
    NO *no = (NO *)malloc(sizeof(NO));
    carrega_no(b, no, pos);

    if (!strcmp(titulo, no->livro.titulo))
        return no;
    if (no->esq != -1)
    {
        return buscarPorTitulo(b, titulo, no->esq);
    }
    if (no->dir != -1)
    {
        return buscarPorTitulo(b, titulo, no->dir);
    }

    return NULL;
}

// imprime a arvore por niveis
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario
// saida: nenhum
void imprimePorNiveis(ARQ_BIN b)
{
    FILA fila;
    FILA *f = inicializa_fila();
    NO *no, *no_aux;
    no = (NO *)malloc(sizeof(NO));
    no_aux = (NO *)malloc(sizeof(NO));

    carrega_no(&b, no, b.c.raiz);

    enqueue(f, no->livro.cod);
    enqueue(f, -1);

    while (!vazia(f))
    {

        printf("[%d] ", f->inicio->cod);
        dequeue(f);

        if (no->esq != -1)
        {
            carrega_no(&b, no_aux, no->esq);
            enqueue(f, no_aux->livro.cod);
        }
        if (no->dir != -1)
        {
            carrega_no(&b, no_aux, no->dir);
            enqueue(f, no_aux->livro.cod);
        }
        if (f->inicio->cod == -1)
        {
            printf("\n");
            dequeue(f);
            enqueue(f, -1);
        }
        if (f->inicio->cod == -1 && f->inicio->prox == NULL)
        {
            printf("\n\n");
            break;
        }
        no = buscaNoAux(&b, f->inicio->cod, b.c.raiz);
    }
}

// imprime arvore no formato pre-ordem em lista
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// entrada: arquivo binario, posicao acessada no arquivo
// saida: nenhum
void imprimeComoLista(ARQ_BIN b, int pos)
{
    NO no;
    carrega_no(&b, &no, pos);

    // Imprime o código do livro atual
    printf("[%d", no.livro.cod);

    // Verifica se há subárvores à esquerda ou direita
    if (no.esq != -1 || no.dir != -1)
    {
        printf(","); // Separador após o código do nó principal

        // Imprime subárvore esquerda se existir
        if (no.esq != -1) {
            imprimeComoLista(b, no.esq);
        } else {
            printf("[]"); // Indica nó vazio à esquerda
        }

        // Imprime subárvore direita se existir
        if (no.dir != -1) {
            printf(","); // Separador entre filhos esquerdo e direito
            imprimeComoLista(b, no.dir);
        } else {
            printf(",[]"); // Indica nó vazio à direita
        }
    }

    printf("]"); // Fecha o nó atual
}


// calcula a quantidade total de livros
// pre-condicao: arquivo aberti
// pos-condicao: nenhum
// entrada: arquivo binario, posicao acessada no arquivo
// saida: quantidade de livros
int calculaTotal(ARQ_BIN *arq, int pos)
{
    NO no;
    carrega_no(arq, &no, pos);

    if (no.dir != -1 && no.esq != -1)
        return 1 + calculaTotal(arq, no.dir) + calculaTotal(arq, no.esq);
    if (no.dir != -1)
        return 1 + calculaTotal(arq, no.dir);
    if (no.esq != -1)
        return 1 + calculaTotal(arq, no.esq);
    return 1;
}

// funcao auxiliar a "printa_lista_livres()"
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// Entrada: estrutura para arquivo .bin, NO a ser acessado, registro desse NO
// Retorno: nenhum
void imprimeLivresAux(ARQ_BIN b, NO no, int reg){

    carrega_no(&b, &no, reg);
    printf("%d -> ", no.reg);

    if(no.dir != -1){
        imprimeLivresAux(b, no, no.dir);
    }
}

// imprime uma a lista de NOs livres
// pre-condicao: arquivo aberto
// pos-condicao: nenhum
// Entrada: estrutura para arquivo .bin
// Retorno: nenhum
void imprimeLivres(ARQ_BIN b){

    NO no;
    carrega_no(&b, &no, b.c.livre);
    printf("%d -> ", no.reg);

    if(no.dir != -1){
        imprimeLivresAux(b, no, no.dir);
    }
    printf("\n\n");
}

// Função para remover espaços no início e no fim de uma string
// pre-condicao: nenhum
// pos-condicao: espacos removidos do inicio e fim de uma string removidos caso houver
// entrada: string a sofrer a mudanca
// saida: string sem espacos no inicio e fim da string
void trim(char *str) {
    char *end;

    // Remove espaços do início
    int start = 0;
    while (isspace((unsigned char)str[start])) start++;

    // Move todos os caracteres para o início
    if (start > 0) {
        int i = 0;
        while (str[start] != '\0') {
            str[i++] = str[start++];
        }
        str[i] = '\0';
    }

    // Remove espaços do fim
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Define o novo fim da string
    *(end + 1) = '\0';
}

// Função para substituir a vírgula por ponto em uma string (para conversão de preço)
// pre-condicao: nenhum
// pos-condicao: virgulas trocadas por pontos na string
// entrada: string a sofrer a mudanca
// saida: string com pontos no lugar de virgulas
void substituir_virgula(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}

// carrega varios livros atraves de um arquivo texto
// pre-condicao: arquivos abertos
// pos-condicao: livros carregados em lote
// entrada: arquivo binario, arquivo texto
// saida: nenhum
void carregaLote(ARQ_BIN* arq, FILE* arquivo){
    LIVRO livro;
    char preco_str[20];

    // Lê os dados do arquivo e armazena na estrutura
    while (fscanf(arquivo, "%d ; %149[^;] ; %199[^;] ; %49[^;] ; %d ; %d ; %19[^;] ; %d\n",
                  &livro.cod, livro.titulo, livro.autor, livro.editora, 
                  &livro.edicao, &livro.ano, preco_str, &livro.estoque) == 8) {
        
        // Remove espaços dos campos de texto
        trim(livro.titulo);
        trim(livro.autor);
        trim(livro.editora);
        trim(preco_str);

        // Substitui a vírgula por ponto no preço e converte para float
        substituir_virgula(preco_str);
        livro.preco = strtof(preco_str, NULL);

        imprimeLivro(livro);

        insereLivro(arq, livro);
    }
}

// libera no da arvore e insere na lista de livres
// pre-condicao: arquivo aberto
// pos-condicao: arquivo atualizado
// Entrada: estrutura para arquivo .bin, NO a ser liberado
// Retorno: nenhum
void liberar_no(ARQ_BIN *b, NO* no){
    no->dir = b->c.livre;
    b->c.livre = no->reg;
    grava_no(b, no);
    grava_cabecalho(b);
}

// busca o maior NO
// pre-condicao: arquivo aberto
// pos-condicao: arquivo atualizado
// Entrada: estrutura para arquivo .bin, reg da arvore a ser feito a busca, NO a receber o maior NO
// Retorno: estrutura de arquivo .bin
int maior_dos_menores(ARQ_BIN *b, int reg, NO* maior){

    NO no;
    carrega_no(b, &no, reg);
    if(no.dir == -1){
        *maior = no;
        liberar_no(b, &no);
        return no.esq;
    }
    no.dir = maior_dos_menores(b, no.dir, maior);
    grava_no(b, &no);
    return no.reg;
}

// funcao auxiliar a "remover()"
// pre-condicao: arquivo aberto
// pos-condicao: arquivo atualizado
// Entrada: estrutura para arquivo .bin, cod do NO a ser removido, registrador indicando no acessado
// Retorno: o registro do no da arvore a receber a remocao
int remover_sub(ARQ_BIN *b, int cod, int reg){

    NO no;
    NO removido;
    carrega_no(b, &no, reg);

    if(no.livro.cod == cod){
        printf("Cod %d removido com sucesso\n", cod);
        if(no.dir == -1 && no.esq == -1){
            liberar_no(b, &no);
            return -1;
        }
        int aux;
        if(no.dir == -1){
            aux = no.esq;
            liberar_no(b, &no);
            return aux;
        }
        if(no.esq == -1){
            aux = no.dir;
            liberar_no(b, &no);
            return aux;
        }
        no.esq = maior_dos_menores(b, no.esq, &removido);
        no.livro = removido.livro;
        grava_no(b, &no);
        return reg;
    }

    if(cod < no.livro.cod){
        if(no.dir == -1 && no.esq == -1){
            printf("Codigo inexistente!\n");
        }
        else no.esq = remover_sub(b, cod, no.esq);
    }else{
        if(no.dir == -1 && no.esq == -1){
            printf("Codigo inexistente!\n");
        }
        no.dir = remover_sub(b, cod, no.dir);
    }

    grava_no(b, &no);
    return no.reg;
}

// realiza a remocao de um no na arvore binario no arquivo
// pre-condicao: arquivo aberto
// pos-condicao: arquivo atualizado
// Entrada: estrutura para arquivo .bin, cod do NO a ser removido
// Retorno: nenhum
void remover(ARQ_BIN *b, int cod){
    b->c.raiz = remover_sub(b, cod, b->c.raiz);
    grava_cabecalho(b);
}
