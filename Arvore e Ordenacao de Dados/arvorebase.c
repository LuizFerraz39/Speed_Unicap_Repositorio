#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX 50

typedef struct aluno{
    char matricula[20];
    char nome[100];
    int faltas;
    float media;
} *Aluno;

typedef struct info{
    Aluno data;
}* Info;

typedef struct chave{
    char codigo[20];
}* Chave;

typedef struct Node{
    Info info;
    struct Node* left;
    struct Node* right;
    int qtd;
    int balance;
} *Node;

typedef struct Tree{
    Node node;
    int size;
    int status;
} *Tree;

typedef struct elemento{
    Node valor;
    struct elemento *prox;
}Elem; 

typedef struct fila {
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
}*Fila;

typedef struct Familia {
    Node pai;
    Node filho;
    int iguais;
}* Familia;

typedef struct pilha {
    Node dados[MAX];
    int topo;
} *Pilha;

Aluno getData(Info info){
    return info->data;
}

char* getCodigo(Chave chave){
    return chave->codigo;
}

Pilha criar_pilha(){
    Pilha p = malloc(sizeof(struct pilha));
    if(p != NULL)
        p->topo = 0;
    return p;
}

int push(Pilha p, Node dado){
    if(p->topo < MAX && p != NULL){
        p->dados[p->topo] = dado;
        p->topo++;
        return 0;
    }else
        return 1;
}

int peek(Pilha p, Node* dado){
    if (p->topo == 0 || p == NULL)
        return 1;
    else{
        (*dado) = p->dados[p->topo - 1];
        return 0;
    }
}

int pop(Pilha p){
    if (p->topo == 0 || p == NULL)
        return 1;
    else
        p->topo--;
    return 0;
}


Fila criar_fila(){
    Fila f = malloc(sizeof(struct fila));
    if(f != NULL){
        f->inicio = NULL;
        f->final = NULL;
        f->qtd = 0;
    }
    return f;
}

int enqueue(Fila f, Node dado){
    if(f == NULL) return 1;

    Elem *no = malloc(sizeof(Elem));
    no->valor = dado;
    no->prox = NULL;

    if(f->final == NULL){
        f->inicio = no;
    }else{
        f->final->prox = no;
    }
    f->final = no;
    f->qtd++;
    return 0;
}

int dequeue(Fila f, Node* node){
    if(f == NULL || f->qtd == 0) return 1;

    Elem *aux = f->inicio;
    f->inicio = aux->prox; 
    if(f->inicio == NULL)
        f->final = NULL;

    (*node) = aux->valor;
    free(aux);
    f->qtd--;
    return 0;
}

// Abstracoes
Aluno getData(Info info);
char* getCodigo(Chave chave);

Aluno CreateAluno(char* matricula, char* nome, int faltas, float media);
Info CreateInfo(Aluno aluno);
Chave CreateChave(char* codigo);

int CompareKey(Chave chave, Info info);
int CompareData(Info info, Info info2);

void PrintChave(Info info);
void PrintInfo(Info info);

void FreeInfo(Info info);
void FreeChave(Chave chave);
void FreeData(Info info);
// input
Info DigitarAluno();
// arvore
Node CreateNode(Info info);
Tree CreateTree();
void DeleteTree(Tree tree);
void FreeNode(Node node);
void InsertNode(Info info, Tree tree);
Node* TreeToArray(Tree tree);
void NodeToArray(Node node, Node* array, int* counter);
void NodeCounter(Node node, int* counter);
void rotacaoEsq(Node* a, int* status);
void rotacaoDir(Node* a, int* status);
void BalancedInsert(Node* root, Info info, int* status, int* size);

int SearchNode(Tree tree, Chave chave);
Familia SearchNodeV2(Tree tree, Chave chave);
Node MaiorNode(Node* array, Tree tree);
Node MenorNode(Node* array);

// fila
Fila criar_fila();
int enqueue(Fila f, Node dado);
int dequeue(Fila f, Node* node);
int isEmpty(Fila f);

// pilha
Pilha criar_pilha();
int push(Pilha p, Node dado);
int pop(Pilha p);
int peek(Pilha p, Node* dado);
int isEmptyP(Pilha p);

void PrintArrayofNodes(Node* array, int size);
void PasseioporNivel(Tree tree);

Info CreateInfo(Aluno aluno){
    Info info = malloc(sizeof(struct info));
    info->data = aluno;
    return info;
}

Chave CreateChave(char* codigo){
    Chave chave = malloc(sizeof(struct chave));
    strcpy(chave->codigo, codigo);
    return chave;
}

void FreeInfo(Info info){
    free(info->data);
    free(info);
    return;
}

Aluno CreateAluno(char* matricula, char* nome, int faltas, float media){
    Aluno aluno = malloc(sizeof(struct aluno));

    strcpy(aluno->matricula, matricula);
    strcpy(aluno->nome, nome);
    aluno->faltas = faltas;
    aluno->media = media;

    return aluno;
}

Info DigitarAluno() {
    char matricula[20];
    char nome[100];
    int faltas;
    float media;

    printf("Digite a matricula do aluno: \n");
    scanf("%19s", matricula); 

    while (getchar() != '\n'); 

    printf("Digite o nome do aluno: \n");
    scanf("%99[^\n]", nome); 

    printf("Digite a quantidade de faltas do aluno: \n");
    scanf("%d", &faltas);

    printf("Digite a media do aluno: \n");
    scanf("%f", &media); 

    Aluno aluno = CreateAluno(matricula, nome, faltas, media);
    Info info = CreateInfo(aluno);
    return info;
}

Node CreateNode(Info info){
    Node node = calloc(1, sizeof(struct Node));

    node->info = info;
    node->qtd = 1;
    node->balance = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Tree CreateTree(){
    Tree tree = malloc(sizeof(struct Tree));
    tree->size = 0;
    tree->status = 0;
    tree->node = NULL;
    return tree;
}

void DeleteTree(Tree tree){
    if (tree->node != NULL){
        FreeNode(tree->node);
    }
    free(tree);
}

void FreeData(Info info){
    free(info);
}

void FreeChave(Chave chave){
    free(chave);
}

void FreeNode(Node node){
    if(node->left != NULL){
        FreeNode(node->left);
    }
    if(node->right != NULL){
        FreeNode(node->right);
    }
    FreeData(node->info);
    free(node);
}

void InsertNode(Info info, Tree tree){
    if(tree == NULL){
        printf("Arvore nao existe para inserir dados");
        return;
    }

    Node nodeinsert = CreateNode(info);
    tree->size++;

    if (tree->node == NULL){
        tree->node = nodeinsert;
        return;
    }

    Node nodecurrent = tree->node;

    while(1){
        if (CompareData(nodeinsert->info, nodecurrent->info) == 0){
            nodecurrent->qtd++;
            free(nodeinsert);
            return;
        }

        if (CompareData(nodeinsert->info, nodecurrent->info) > 0){
            if (nodecurrent->right == NULL){
                nodecurrent->right = nodeinsert;
                return;
            }
            else{
                nodecurrent = nodecurrent->right;
            }
        }
        if (CompareData(nodeinsert->info, nodecurrent->info) < 0){
            if (nodecurrent->left == NULL){
                nodecurrent->left = nodeinsert;
                return;
            }
            else{
                nodecurrent = nodecurrent->left;
            }
        }
    }
}

int CompareKey(Chave chave, Info info){
    return strcmp(chave->codigo, info->data->matricula);
}

int SearchNode(Tree tree, Chave chave){
    int counter = 0;
    
    if (tree->node == NULL){
        return counter;
    }

    Node nodecurrent = tree->node;

    while(1){
        if (CompareKey(chave, nodecurrent->info) == 0){
            counter = nodecurrent->qtd;
            return counter;
        }
        if (CompareKey(chave, nodecurrent->info)> 0){
            if (nodecurrent->right == NULL){
                return counter;
            }
            else{
                nodecurrent = nodecurrent->right;
            }
        }
        else{
            if (nodecurrent->left == NULL){
                return counter;
            }
            else{
                nodecurrent = nodecurrent->left;
            }
        }
    }
}

Familia SearchNodeV2(Tree tree, Chave chave){
    Familia family = malloc(sizeof(struct Familia));

    Familia counter = NULL;
    
    if (tree->node == NULL){
        return counter;
    }

    Node aux = tree->node;
    Node nodecurrent = tree->node;
    family->pai=aux;
    family->filho=nodecurrent;
    family->iguais= 1;

    while(1){
        if (CompareKey(chave, nodecurrent->info) == 0){
            family->pai=aux;
            family->filho=nodecurrent;
            if (aux != nodecurrent){
                family->iguais = 0;
            }
            return family;
        }
        if (CompareKey(chave, nodecurrent->info) > 0){
            if (nodecurrent->right == NULL){
                return counter;
            }
            else{
                aux = nodecurrent;
                nodecurrent = nodecurrent->right;
            }
        }
        if (CompareKey(chave, nodecurrent->info) < 0){
            if (nodecurrent->left == NULL){
                return counter;
            }
            else{
                aux = nodecurrent;
                nodecurrent = nodecurrent->left;
            }
        }
    }
}

Node* TreeToArray(Tree tree){
    Node* array = malloc(tree->size * sizeof(Node));
    int value = 0;
    int* counter = &value;

    NodeToArray(tree->node, array, counter);

    return array;
}

int isEmpty(Fila f){
    if (f->inicio == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

int isEmptyP(Pilha p){
    if (p->topo == 0){
        return 1;
    }
    return 0;
}

void NodeToArray(Node node, Node* array, int* counter){
    if(node->left != NULL){
        NodeToArray(node->left, array, counter);
    }

    for (int i = 0; i < node->qtd; i++){
        array[(*counter)]= node;
        (*counter)++;
    }
    
    if(node->right != NULL){
        NodeToArray(node->right, array, counter);
    }

}

void NodeCounter(Node node, int* counter){
    if(node->left != NULL){
        NodeCounter(node->left, counter);
    }

    for (int i = 0; i < node->qtd; i++){
        (*counter)++;
    }
    
    if(node->right != NULL){
        NodeCounter(node->right, counter);
    }

}


Node MaiorNode(Node* array, Tree tree){
    return array[tree->size-1];
}

Node MenorNode(Node* array){
    return array[0];
}

void FRecursivaContarNos(Node node, int* counter){
    if(node->left != NULL){
        FRecursivaContarNos(node->left, counter);
    }

    for (int i = 0; i < node->qtd; i++){
        (*counter)++;
    }
    
    if(node->right != NULL){
        FRecursivaContarNos(node->right, counter);
    }

}

void FNaoRecursivaContarNos(Tree tree, int* counter){
    (*counter) = tree->size;
}

void FRecursivaContarFolhas(Node node, int* counter){
    if(node->left != NULL){
        FRecursivaContarFolhas(node->left, counter);
    }

    if(node->left == NULL && node->right == NULL){
        (*counter)++;
    }
    
    if(node->right != NULL){
        FRecursivaContarFolhas(node->right, counter);
    }
}

void FNaoRecursivaContarFolhas(Tree tree, int* counter){
    Fila fila;
    Node aux;
    if(tree->node != NULL){
        fila = criar_fila();
        enqueue(fila, tree->node);
        while(isEmpty(fila) != 0){
            dequeue(fila, &aux);
            if (aux->left != NULL){
                enqueue(fila, aux->left);
            }
            if (aux->right != NULL){
                enqueue(fila, aux->right);
            }
            if(aux->left == NULL && aux->right == NULL){
                (*counter)++;
            }
        }
    }
    else{
        return;
    }
}

void FRecursivaContarNosNaoTerminais(Node node, int* counter){
    if(node->left != NULL){
        FRecursivaContarNosNaoTerminais(node->left, counter);
    }

    if(node->left != NULL || node->right != NULL){
        (*counter)++;
    }
    
    if(node->right != NULL){
        FRecursivaContarNosNaoTerminais(node->right, counter);
    }
}

void FNaoRecursivaContarNosNaoTerminais(Tree tree, int* counter){
    Fila fila;
    Node aux;
    if(tree->node != NULL){
        fila = criar_fila();
        enqueue(fila, tree->node);
        while(isEmpty(fila) != 0){
            dequeue(fila, &aux);
            if (aux->left != NULL){
                enqueue(fila, aux->left);
            }
            if (aux->right != NULL){
                enqueue(fila, aux->right);
            }
            if(aux->left != NULL || aux->right != NULL){
                (*counter)++;
            }
        }
    }
    else{
        return;
    }
}

int CompareData(Info info, Info info2){
    return strcmp(info->data->matricula, info2->data->matricula);
}

void PrintChave(Info info){
    printf("%s ", info->data->matricula);
}

void PrintArrayofNodes(Node* array, int size){
    printf(" [ ");
    for (int i = 0; i < size; i++){
        PrintChave(array[i]->info);
    }
    printf("]\n");
    return;
}


void rotacaoEsq (Node*a,int *status) {
    Node b, c;
    b = (*a)->right;
    if (b->balance == 1) { // rotação simples
        (*a)->right = b->left;
        b->left = *a;
        (*a)->balance = 0;
        (*a) = b;
    }
    else { // rotação dupla
        c = b->left;
        b->left = c->right;
        c->right = b;
        (*a)->right = c->left;
        c->left = *a;
    if (c->balance == 1)
        (*a)->balance = -1;
    else
        (*a)->balance = 0;
    if (c->balance == -1)
        b->balance = 1;
    else
        b->balance = 0;
    (*a) = c;
    } 
    (*a)->balance = 0;
    *status = 0;
}

void rotacaoDir (Node* a, int *status) {
    Node b, c;
    b = (*a)->left;
    if (b->balance == -1) { // rotação simples
        (*a)->left = b->right;
        b->right = *a;
        (*a)->balance = 0;
        (*a) = b;
    }
    else { // rotação dupla
        c = b->right;
        b->right = c->left;
        c->left = b;
        (*a)->left = c->right;
        c->right = *a;
        if (c->balance == -1)
            (*a)->balance = 1;
        else
            (*a)->balance = 0;
        if (c->balance == 1)
            b->balance = -1;
        else
            b->balance = 0;
        (*a) = c;
    } 
    (*a)->balance = 0;
    *status = 0;
}

void BalancedInsert(Node* root, Info info, int *status, int* size) {
    if ((*root) == NULL) {
        (*root) = CreateNode(info);
        *status = 1;
        (*size)++;
    }
    else if (CompareData(info, (*root)->info) == 0){
        (*root)->qtd++;
        return;
    }
    else if((CompareData(info, (*root)->info) < 0)) {
        BalancedInsert(&((*root)->left), info, status, size);
        if (*status == 1)
            switch ((*root)->balance) {
                case 1 : (*root)->balance = 0; *status = 0; break;
                case 0 : (*root)->balance = -1; break;
                case -1 : rotacaoDir(root,status); break;
            }
    }
    else {
        BalancedInsert(&((*root)->right), info, status, size);
        if (*status == 1)
            switch ((*root)->balance) {
                case -1 : (*root)->balance = 0; *status = 0; break;
                case 0 : (*root)->balance = 1; break;
                case 1 : rotacaoEsq(root,status); break;
            }
    }
}

void PrintInfo(Info info){
    printf("Matricula: %s ", info->data->matricula);
    printf("Nome: %s ", info->data->nome);
    printf("Media: %.2f ", info->data->media);
    printf("Faltas: %d \n", info->data->faltas);
}

void PasseioporNivel(Tree tree){
    Fila fila;
    Node aux;
    printf("Passeio por nivel: \n");
    if(tree->node != NULL){
        fila = criar_fila();
        enqueue(fila, tree->node);
        while(isEmpty(fila) == 1){
            dequeue(fila, &aux);
            if (aux->left != NULL){
                enqueue(fila, aux->left);
            }
            if (aux->right != NULL){
                enqueue(fila, aux->right);
            }
            PrintInfo(aux->info);
            printf("Balanceamento: %d \n", aux->balance);
        }
    }
    else{
        printf("Arvore vazia\n");
    }
}

void InserirAlunosExemplo(Tree tree){
    char* matriculas[8] = {"000001", "202602", "100003", "999604", "202605", "333606", "111607", "002608"};
    char* nomes[8] = {
        "Ana Silva", "Bruno Sousa", "Carlos Lima", "Diana Costa",
        "Eduardo Rocha", "Fernanda Alves", "Gabriel Melo", "Penolope Gomes"
    };
    int faltas[8] = {2, 4, 0, 1, 5, 3, 0, 2};
    float medias[8] = {8.5, 7.0, 9.2, 6.5, 5.8, 8.0, 9.5, 7.8};

    for (int i = 0; i < 8; i++) {
        Aluno baseAluno = CreateAluno(matriculas[i], nomes[i], faltas[i], medias[i]);
        Info novoAluno = CreateInfo(baseAluno);
        BalancedInsert(&(tree->node), novoAluno, &(tree->status), &(tree->size));
    }
}

Chave DigitarChave() {
    char codigo[20];

    printf("Digite a matricula do aluno: ");
    scanf("%19s", codigo);

    return CreateChave(codigo);
}

void CadastrarAluno(Tree tree){
    Info novoAluno = DigitarAluno();
    BalancedInsert(&(tree->node), novoAluno, &(tree->status), &(tree->size));
    printf("Aluno inserido \n");
}

void BuscarAluno(Tree tree){
    Chave chave = DigitarChave();

    int counter = SearchNode(tree, chave);
    if (counter < 1){
        printf("Aluno com essa matricula nao encontrado \n");
    }
    else{
        Familia familia = SearchNodeV2(tree, chave);
        Node node = familia->filho;
        printf("Aluno encontrado: \n");
        PrintInfo(node->info);
    }

    FreeChave(chave);
}

void PercorrerEmOrdem(Tree tree) {
    Node* array = TreeToArray(tree);
    int size = tree->size;

    printf("\nArvore em ordem:\n");

    for (int i = 0; i < size; i++) {
        PrintInfo(array[i]->info);
        printf("Balanceamento: %d\n", array[i]->balance);
        printf("\n");
    }

    free(array);
}

int testar (){
    Tree tree = CreateTree();

    InserirAlunosExemplo(tree);
    Node* array = TreeToArray(tree);
    int size = tree->size;

    printf("Arvore preOrdem Recusivamente: \n");
    PrintArrayofNodes(array, size);

    PasseioporNivel(tree);
    free(array);
    DeleteTree(tree);
    return 0;
}

int main() {
    Tree tree = CreateTree();
    int opcao;
    do {
        printf("\n-- Menu ----------------\n");
        printf("1 - Cadastrar novo aluno\n");
        printf("2 - Buscar aluno por matricula\n");
        printf("3 - Percorrer arvore por nivel\n");
        printf("4 - Percorrer arvore em ordem\n");
        printf("5 - Teste basico\n");
        printf("0 - Sair\n");
        printf("------------------------------\n");
        printf("Digite o numero de escolha: ");

        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                CadastrarAluno(tree);
                break;

            case 2:
                BuscarAluno(tree);
                break;

            case 3:
                PasseioporNivel(tree);
                break;

            case 4:
                PercorrerEmOrdem(tree);
                break;
            
            case 5:
                testar();
                break;

            case 0:
                printf("Deletando arvore\n");
                break;

            default:
                printf("Opcao nao existe\n");
        }

    } while (opcao != 0);

    DeleteTree(tree);

    return 0;
}