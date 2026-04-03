#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

typedef struct pilha {
    int dados[MAX];
    int topo;
} *Pilha;

Pilha criar_pilha(){
    Pilha p = malloc(sizeof(struct pilha));
    if(p != NULL)
        p->topo = 0;
    return p;
}

int push(Pilha p, int vagao){
    if(p->topo < MAX && p != NULL){
        p->dados[p->topo] = vagao;
        p->topo++;
        return 0;
    }else
        return 1;
}

int peek(Pilha p){
        int vagao = p->dados[p->topo - 1];
        return vagao;
}

int pop(Pilha p){
    if (p->topo == 0 || p == NULL)
        return 1;
    else
        p->topo--;
    return 0;
}

int tamanho_pilha(Pilha p){
    if(p == NULL)
        return 0;
    return p->topo;
}

void destruir_pilha(Pilha p){
    if(p != NULL)
        free(p);
}

int main(){
    int vagao;
    int* pD;
    int tamanho;

    while(1){

        scanf("%d", &tamanho);
        if(tamanho == 0){
            return 0;
        }
    
        while(1){
            
            int* pD = malloc(tamanho * sizeof(int));
            
            scanf("%d", &vagao);
            if (vagao == 0){
                printf("\n");
                break;
        }
        pD[0] = vagao;
        
        for (int i = 1; i<tamanho; i++){
           scanf("%d", &vagao);
           pD[i] = vagao;
        }
        
        Pilha pR = criar_pilha();
        
        int inicio = 0;
        for (int i = 0; i<tamanho;i++){
            push(pR, (i+1));
            
            while(peek(pR) == pD[inicio]){
                inicio++;
                pop(pR);
            }
        }
        if (inicio == tamanho){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
        destruir_pilha(pR);
        free(pD);
    }


        
    }
    
    return 0;
}