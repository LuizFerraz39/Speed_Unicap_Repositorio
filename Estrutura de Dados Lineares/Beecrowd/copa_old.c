#include<stdlib.h>
#include<stdio.h>

typedef struct elemento{
    int valor;
    struct elemento* prox;
} Elem;

typedef struct lista{
    Elem* inicio;
    int qtd;
}* Lista;

int remover_final(Lista li);
int inserir_inicio(Lista li, int valor);

Lista criar_lista(){
    Lista li = malloc(sizeof(struct lista));
    if(li != NULL){
        li->inicio = NULL;
        li->qtd = 0;
    }
    return li;
}

void shift(Lista li){
    int valor;

    if(li == NULL || li->inicio == NULL || li->qtd == 0)
        return;
    Elem* aux = li->inicio;
    Elem* ant = li->inicio;
    if(aux->prox == NULL){
        return;
    }

    while(aux->prox != NULL){
        ant = aux;
        aux = aux ->prox;
    }
    free(aux);
    ant->prox = NULL;
    li->qtd--;

    valor = ant->valor;
    remover_final(li);
    inserir_inicio(li, valor);
    return;
}

int inserir_inicio(Lista li, int valor){
    Elem* no = malloc(sizeof(Elem));
    if(no != NULL){
        no->valor = valor;
        no->prox = li->inicio;
        li->inicio = no;
        li->qtd++;
        return 0;
    }
    return 1;
}


int inserir_final(Lista li, int valor){
    if(li == NULL)
        return 1;
    Elem* no = malloc(sizeof(Elem));
    if(no == NULL)
        return 1;
    no->valor = valor;
    no->prox = NULL;
    if(li->inicio == NULL){
        li->inicio = no;
        li->qtd++;
        return 0;
    }
    Elem* aux = li->inicio;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = no;
    li->qtd++;
    return 0;
    
}

int remover_inicio(Lista li){
    if(li->inicio == NULL){
        return 1;
    }
    Elem* no = li->inicio;
    li->inicio = no->prox;
    li->qtd--;
    free(no);
    return 0;
}

int acessar_final(Lista li){
    int valor;

    if(li->inicio == NULL){
        return -1;
    }
    Elem* aux = li->inicio;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    valor = aux->valor;

    return valor;
}

int remover_final(Lista li){
    if(li == NULL || li->inicio == NULL || li->qtd == 0)
        return 1;
    Elem* aux = li->inicio;
    Elem* ant;
    if(aux->prox == NULL){
        free(aux);
        li->inicio = NULL;
        li->qtd--;
        return 0;
    }
    while(aux->prox != NULL){
        ant = aux;
        aux = aux ->prox;
    }
    free(aux);
    ant->prox = NULL;
    li->qtd--;
    return 0;
}

int acessar_inicio(Lista li, int* valor){
    if(li == NULL){
        return 1;
    }
    if(li->inicio == NULL){
        return 1;
    }
    *valor = li->inicio->valor;
    return 0;
}

void destruir(Lista li){
    if(li != NULL){
        Elem* no = li->inicio;
        while(no != NULL){
            Elem *prox = no->prox;
            free(no);
            no = prox;
        }
        free(li);
    }
}

int lista_quantidade(Lista li){
    if(li == NULL)
        return 0;
    return li->qtd;
}

int tamanho_lista(Lista li){
    if(li == NULL)
        return 0;

    int count = 0;
    Elem* aux = li->inicio;
    while(aux != NULL){
        count++;
        aux = aux->prox;
    }
    return count;
}

int remover_numero(Lista li, int valor){
    if (li->inicio == NULL){
        return 1;
    }
    
    Elem* aux = li->inicio;
    Elem* ant = aux;

    if (aux->valor == valor){
        remover_inicio(li);
        return 0;
    }
    aux = aux->prox;

    while(aux != NULL){
        if (aux->valor == valor){
            ant->prox = aux->prox;
            free(aux);
            return 0;
        }
        ant = aux;
        aux = aux->prox;
    }

    return 1;
}

int main(){
    
    int tamanho;
    int valor;

    Lista li = criar_lista();

    scanf("%d", &tamanho);
    for (int i = 0; i < tamanho; i++){
        scanf("%d", &valor);
        inserir_final(li, valor);
    }

    scanf("%d", &tamanho);
    for (int i = 0; i < tamanho;i++){
        scanf("%d", &valor);
        remover_numero(li, valor);
    }

    int first = 0;
    while(acessar_inicio(li, &valor) != 1){
        if (first == 0){
            printf("%d", valor);
            first = 1;
            remover_inicio(li);
        }
        else{
            printf(" %d", valor);   
            remover_inicio(li);
        }
    }


    destruir(li);
    return 0;
}