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

typedef struct Node{
    Aluno aluno;
    struct Node* left;
    struct Node* right;
    int qtd;
} *Node;

typedef struct Tree{
    Node node;
    int size;
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

Node CreateAluno(char* matricula, char* nome, int faltas, float media);
Node CreateNode(Aluno aluno);
Tree CreateTree();
void DeleteTree(Tree tree);
void FreeNode(Node node);
void InsertNode(Aluno aluno, Tree tree);
Node* TreeToArray(Tree tree);
void NodeToArray(Node node, Node* array, int* counter);
void PrintArrayofNodes(Node* array, int size);

Node DigitarAluno() {
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

    return CreateAluno(matricula, nome, faltas, media);
}

Node CreateNode(Aluno aluno){
    Node node = calloc(1, sizeof(struct Node));

    node->aluno = aluno;
    node->qtd = 1;

    return node;
}

Tree CreateTree(){
    Tree tree = malloc(sizeof(struct Tree));
    tree->size = 0;
    tree->node = NULL;
    return tree;
}

void DeleteTree(Tree tree){
    FreeNode(tree->node);
    free(tree);
}

void FreeNode(Node node){
    if(node->left != NULL){
        FreeNode(node->left);
    }
    if(node->right != NULL){
        FreeNode(node->right);
    }
    free(node->aluno);
    free(node);
}

void InsertNode(Aluno aluno, Tree tree){
    if(tree == NULL){
        printf("Arvore nao existe para inserir dados");
        return;
    }

    Node nodeinsert = CreateNode(aluno);
    tree->size++;

    if (tree->node == NULL){
        tree->node = nodeinsert;
        return;
    }

    Node nodecurrent = tree->node;

    while(1){
        if (nodeinsert->aluno->nome == nodecurrent->aluno->nome){
            nodecurrent->qtd++;
            free(nodeinsert);
            return;
        }

        if (strcmp(nodeinsert->aluno->nome, nodecurrent->aluno->nome)){
            if (nodecurrent->right == NULL){
                nodecurrent->right = nodeinsert;
                return;
            }
            else{
                nodecurrent = nodecurrent->right;
            }
        }
        if (strcmp(nodeinsert->aluno->nome, nodecurrent->aluno->nome) < 0){
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

int SearchNode(Tree tree, char* matricula){
    int counter = 0;
    
    if (tree->node == NULL){
        return counter;
    }

    Node nodecurrent = tree->node;

    while(1){
        if (matricula == nodecurrent->aluno->matricula){
            counter = nodecurrent->qtd;
            return counter;
        }
        if (strcmp(matricula, nodecurrent->aluno->matricula)){
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

Familia SearchNodeV2(Tree tree, char* matricula){
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
        if (matricula == nodecurrent->aluno->matricula){
            family->pai=aux;
            family->filho=nodecurrent;
            if (aux != nodecurrent){
                family->iguais = 0;
            }
            return family;
        }
        if (strcmp(matricula, nodecurrent->aluno->matricula) > 0){
            if (nodecurrent->right == NULL){
                return counter;
            }
            else{
                aux = nodecurrent;
                nodecurrent = nodecurrent->right;
            }
        }
        if (strcmp(matricula, nodecurrent->aluno->matricula) < 0){
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

void PasseioporNivel(Tree tree){
    Fila fila;
    Node aux;
    if(tree->node != NULL){
        fila = criar_fila();
        enqueue(fila, tree->node);
        while(isEmpty(fila) != 1){
            dequeue(fila, &aux);
            if (aux->left != NULL){
                enqueue(fila, aux->left);
            }
            if (aux->right != NULL){
                enqueue(fila, aux->right);
            }
            printf("%s \n", aux->aluno->nome);
        }
    }
    else{
        printf("Arvore vazia\n");
    }
}

void PasseioemOrdemNaoRecursivo(Tree tree){
    Pilha pilha;
    int checado = 0;
    Node aux;
    if(tree->node != NULL){
        pilha = criar_pilha();
        push(pilha, tree->node);
        while(isEmptyP(pilha) != 1){
            peek(pilha, &aux);
            if (checado == 0){
                while(aux->left != NULL){
                    push(pilha, aux->left);
                    peek(pilha, &aux);
                }
                checado = 1;
            }

            for (int i = 0; i < aux->qtd;i++){
                printf("%d \n", aux->aluno->nome);
            }
            pop(pilha);

            if (aux->right != NULL){
                checado = 0;
                push(pilha, aux->right);
                continue;
            }
        }
    }
    else{
        printf("Arvore vazia\n");
    }
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

void PrintArrayofNodes(Node* array, int size){
    printf(" [ ");
    for (int i = 0; i < size; i++){
        printf("%d ", array[i]->aluno->matricula);
    }
    printf("]\n");
    return;
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

int RemoveNode(Tree tree, char* matricula){
    if (SearchNode(tree, matricula) == 0){
        return 0;
    }

    Familia family = SearchNodeV2(tree, matricula);
    Node current = family->filho;
    Node father = family->pai;

    if(current->qtd>1){
        current->qtd--;
        return 1;
    }

    int isleft = 0;
    if(father->left == current){
        isleft = 1;
    }

    if (current->left == current->right && current->right == NULL){
        if (isleft){
            father->left = NULL;
        }else{
            father->right = NULL;
        }

        free(current);
        return 1;
    }

    if (current->left == NULL){
        if (isleft){
            father->left = current->right;
        }else{
            father->right = current->right;
        }

        free(current);
        return 1;
    }

    if (current->right == NULL){
        if (isleft){
            father->left = current->left;
        }else{
            father->right = current->left;
        }

        free(current);
        return 1;
    }

    int counter = 0;
    NodeCounter(current, &counter);
    Node* array = malloc(counter * sizeof(Node));
    int counter2 = 0;
    NodeToArray(current, array, &counter2);

    Node maior = array[counter-1];
    char* data2 = maior->aluno->matricula;
    int qtd = maior->qtd;

    for (int i = 0; i < qtd; i++){
        RemoveNode(tree, data2);
    }

    strcpy(family->filho->aluno->matricula, data2);
    family->filho->qtd = qtd;
    
    free(array);
    return 1;
}

int main (){
    Tree tree = CreateTree();
    char* matriculas[8] = {"202601", "202602", "202603", "202604", "202605", "202606", "202607", "202608"};
    char* nomes[8] = {
        "Ana Silva", "Bruno Sousa", "Carlos Lima", "Diana Costa",
        "Eduardo Rocha", "Fernanda Alves", "Gabriel Melo", "Helena Gomes"
    };
    int faltas[8] = {2, 4, 0, 1, 5, 3, 0, 2};
    float medias[8] = {8.5, 7.0, 9.2, 6.5, 5.8, 8.0, 9.5, 7.8};

    for (int i = 0; i < 8; i++) {
        Node novoAluno = CreateAluno(matriculas[i], nomes[i], faltas[i], medias[i]);
        InsertNode(novoAluno, tree);
    }

    Node* array = TreeToArray(tree);
    int size = tree->size;

    printf("Arvore emOrdem Recusivamente: \n");
    PrintArrayofNodes(array, size);

    free(array);
    DeleteTree(tree);
}