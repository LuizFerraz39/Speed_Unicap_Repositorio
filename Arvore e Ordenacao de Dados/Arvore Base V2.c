#include <stdlib.h>
#include <stdio.h>
#define MAX 50

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int qtd;
    int balance;
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

Node CreateNode(int data);
Tree CreateTree();
void DeleteTree(Tree tree);
void FreeNode(Node node);
void InsertNode(int data, Tree tree);
Node* TreeToArray(Tree tree);
void NodeToArray(Node node, Node* array, int* counter);
void PrintArrayofNodes(Node* array, int size);

Node CreateNode(int data){
    Node node = calloc(1, sizeof(struct Node));

    node->data = data;
    node->qtd = 1;
    node->balance = 0;

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
    free(node);
}

void InsertNode(int data, Tree tree){
    if(tree == NULL){
        printf("Arvore nao existe para inserir dados");
        return;
    }

    Node nodeinsert = CreateNode(data);
    tree->size++;

    if (tree->node == NULL){
        tree->node = nodeinsert;
        return;
    }

    Node nodecurrent = tree->node;

    while(1){
        if (nodeinsert->data == nodecurrent->data){
            nodecurrent->qtd++;
            free(nodeinsert);
            return;
        }
        if (nodeinsert->data > nodecurrent->data){
            if (nodecurrent->right == NULL){
                nodecurrent->right = nodeinsert;
                return;
            }
            else{
                nodecurrent = nodecurrent->right;
            }
        }
        if (nodeinsert->data < nodecurrent->data){
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

int SearchNode(Tree tree, int data){
    int counter = 0;
    
    if (tree->node == NULL){
        return counter;
    }

    Node nodecurrent = tree->node;

    while(1){
        if (data == nodecurrent->data){
            counter = nodecurrent->qtd;
            return counter;
        }
        if (data > nodecurrent->data){
            if (nodecurrent->right == NULL){
                return counter;
            }
            else{
                nodecurrent = nodecurrent->right;
            }
        }
        if (data < nodecurrent->data){
            if (nodecurrent->left == NULL){
                return counter;
            }
            else{
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
        return 1;
    }
    else{
        return 0;
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
            printf("%d \n", aux->data);
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
                printf("%d \n", aux->data);
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

void PrintArrayofNodes(Node* array, int size){
    printf(" [ ");
    for (int i = 0; i < size; i++){
        printf("%d ", array[i]->data);
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

void RotateLeft(Node *raiz, int *status){
    if ((*raiz)->right->balance == 1){
        Node aux = *raiz;
        *raiz = aux->right;
        aux->right = (*raiz)->left;
        (*raiz)->left = aux;
        aux->balance = 0;
        (*raiz)->balance = 0;
    }
    else{
        Node aux1 = (*raiz)->right;
        Node aux2 = aux1->left;
        aux1->left = aux2->right;
        aux2->right = aux1;
        (*raiz)->right = aux2->left;
        aux2->left = *raiz;
        if (aux2->balance == 1){
            (*raiz)->balance = -1;
            aux1->balance = 0;
        }
        else if (aux2->balance == 0){
            (*raiz)->balance = 0;
            aux1->balance = 0;
        }
        else{
            (*raiz)->balance = 0;
            aux1->balance = 1;
        }
        *raiz = aux2;
        (*raiz)->balance = 0;
    }
}

void RotateRight(Node *raiz, int *status){
    if ((*raiz)->left->balance == -1){
        Node aux = *raiz;
        *raiz = aux->left;
        aux->left = (*raiz)->right;
        (*raiz)->right = aux;
        aux->balance = 0;
        (*raiz)->balance = 0;
    }
    else{
        Node aux1 = (*raiz)->left;
        Node aux2 = aux1->right;
        aux1->right = aux2->left;
        aux2->left = aux1;
        (*raiz)->left = aux2->right;
        aux2->right = *raiz;
        if (aux2->balance == -1){
            (*raiz)->balance = 1;
            aux1->balance = 0;
        }
        else if (aux2->balance == 0){
            (*raiz)->balance = 0;
            aux1->balance = 0;
        }
        else{
            (*raiz)->balance = 0;
            aux1->balance = -1;
        }
        *raiz = aux2;
        (*raiz)->balance = 0;
    }
}

void BalancedInsert(Node *raiz, int data, int *status){
    if (*raiz == NULL){
        *raiz = CreateNode(data);
        *status = 1;
    }
    else if (data == (*raiz)->info){
        (*raiz)->qtd++;
        return;
    }
    else if (data < (*raiz)->info){
        BalancedInsert(&((*raiz)->left), data, status);
        if (*status == 1){
            switch ((*raiz)->balance){
                case 1:
                    (*raiz)->balance = 0;
                    *status = 0;
                    break;
                case 0:
                    (*raiz)->balance = -1;
                    break;
                case -1:
                    RotateRight(raiz, status);
                    *status = 0;
            }
        }
    }else{
        BalancedInsert(&((*raiz)->right), data, status);
        if (*status == 1){
            switch ((*raiz)->balance){
                case -1:
                    (*raiz)->balance = 0;
                    *status = 0;
                    break;
                case 0:
                    (*raiz)->balance = 1;
                    break;
                case 1:
                    RotateLeft(raiz, status);
                    *status = 0;
            }
        }
    }
}

void BalancedInsertTree(Tree tree, int data){
    int status = 0;
    BalancedInsert(&(tree->node), data, &status);
    if (status == 1){
        tree->size++;
    }
}

void BalancedRemove(Node *raiz, int data, int *status){
    if (*raiz == NULL){
        *status = 0;
        return;
    }
    else if (data < (*raiz)->info){
        BalancedRemove(&((*raiz)->left), data, status);
        if (*status == 1){
            switch ((*raiz)->balance){
                case -1:
                    (*raiz)->balance = 0;
                    break;
                case 0:
                    (*raiz)->balance = 1;
                    *status = 0;
                    break;
                case 1:
                    RotateLeft(raiz, status);
                    if ((*raiz)->balance == 0)
                        *status = 0;
            }
        }
    }else if (data > (*raiz)->info){
        BalancedRemove(&((*raiz)->right), data, status);
        if (*status == 1){
            switch ((*raiz)->balance){
                case 1:
                    (*raiz)->balance = 0;
                    break;
                case 0:
                    (*raiz)->balance = -1;
                    *status = 0;
                    break;
                case -1:
                    RotateRight(raiz, status);
                    if ((*raiz)->balance == 0)
                        *status = 0;
            }
        }
    }else{
        Node aux = *raiz;
        if ((*raiz)->left == NULL){
            *raiz = (*raiz)->right;
            free(aux);
            *status = 1;
        }else if ((*raiz)->right == NULL){
            *raiz = (*raiz)->left;
            free(aux);
            *status = 1;
        }else{
            Node temp = (*raiz)->right;
            while (temp->left != NULL)
                temp = temp->left;

            (*raiz)->info = temp->info;

            BalancedRemove(&((*raiz)->right), temp->info, status);

            if (*status == 1){
                switch ((*raiz)->balance){
                    case 1:
                        (*raiz)->balance = 0;
                        break;
                    case 0:
                        (*raiz)->balance = -1;
                        *status = 0;
                        break;
                    case -1:
                        RotateRight(raiz, status);
                        if ((*raiz)->balance == 0)
                            *status = 0;
                }
            }
        }
    }
}

int main (){
    Tree tree = CreateTree();

    InsertNode(42, tree);
    InsertNode(17, tree);
    InsertNode(68, tree);
    InsertNode(5, tree);
    InsertNode(29, tree);
    InsertNode(53, tree);
    InsertNode(81, tree);
    InsertNode(12, tree);
    InsertNode(34, tree);
    InsertNode(74, tree);

    Node* array = TreeToArray(tree);
    int size = tree->size;

    printf("Menor valor: %d\n", MenorNode(array)->data);
    printf("Maior valor: %d\n", MaiorNode(array, tree)->data);

    printf("Arvore emOrdem Recusivamente: \n");
    PrintArrayofNodes(array, size);

    printf("Passeio por nivel: \n");
    PasseioporNivel(tree);

    int counter;
    printf("Contar nos Recursivamente \n");
    counter = 0;
    FRecursivaContarNos(tree->node, &counter);
    printf("Nos = %d \n", counter);
    printf("Contar nos Nao Recursivamente \n");
    counter = 0;
    FNaoRecursivaContarNos(tree, &counter);
    printf("Nos = %d \n \n", counter);

    printf("Contar folhas Recursivamente \n");
    counter = 0;
    FRecursivaContarFolhas(tree->node, &counter);
    printf("Folhas = %d \n", counter);
    printf("Contar folhas Nao Recursivamente \n");
    counter = 0;
    FNaoRecursivaContarFolhas(tree, &counter);
    printf("Folhas = %d \n\n", counter);

    printf("Contar nos nao-terminais Recursivamente \n");
    counter = 0;
    FRecursivaContarNosNaoTerminais(tree->node, &counter);
    printf("Nos nao-terminais = %d \n", counter);
    printf("Contar nos nao-terminais Nao Recursivamente \n");
    counter = 0;
    FNaoRecursivaContarNosNaoTerminais(tree, &counter);
    printf("Nos nao-terminais = %d \n\n", counter);

    printf("Inserindo valor 50, 3 vezes na arvore\n");

    InsertNode(50, tree);
    InsertNode(50, tree);
    InsertNode(50, tree);

    printf("O node 50 foi encontrado %d vezes na arvore\n\n", SearchNode(tree, 50));


    printf("Passeio em ordem nao recursivo:\n");
    PasseioemOrdemNaoRecursivo(tree);

    free(array);
    DeleteTree(tree);
}