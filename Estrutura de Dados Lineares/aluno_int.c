#include<stdlib.h>
#include<stdio.h>
#define MAX 5

// Dados
struct aluno{
    int mat;
    float media;
};

typedef struct aluno* Aluno;

struct fila {
    Aluno alunos[MAX];
    int inicio, final, qtd;
};

typedef struct fila* Fila; // 8 bytes


// Operaçoes

Fila criar_fila(){
    Fila f = malloc(sizeof(struct fila));
    for (int i = 0; i< MAX; i++){
        f->alunos[i] = malloc(sizeof(struct aluno));
    }
    if(f != NULL){
        f->inicio = 0;
        f->final = 0;
        f->qtd = 0;
    }
    return f;
}

int inserir(Fila f, int valor, float media){
    if(f->qtd < MAX && f != NULL){
        f->alunos[f->final]->mat = valor;
        f->alunos[f->final]->media = media;
        f->final = (f->final + 1) % MAX;
        f->qtd++;
        return 0;
    }else{
        return 1;
    }
}

int remover(Fila f){
    if(f->qtd == 0 || f == NULL){
        return 1;
    }else{
        f->inicio = (f->inicio + 1) % MAX;
        f->qtd--;
        return 0;
    }
}

int acessar(Fila f, int* valor, float* media){
    if(f->qtd == 0 || f == NULL){
        return 1;
    }else{
        *valor = f->alunos[f->inicio]->mat;
        *media = f->alunos[f->inicio]->media;
        return 0;
    }
}

int tamanho(Fila f){
    if(f == NULL){
        return 0;
    }
    return f->qtd;
}

void destruir(Fila f){
    if(f != NULL)
        free(f);
}

int main(){
    Fila f = criar_fila();
    inserir(f, 10, 7.5);
    inserir(f, 20, 4.5);
    inserir(f, 30, 3);
    int valor;    
    float media;
    remover(f);
    inserir(f, 5, 9.9);
    remover(f);
    inserir(f, 60, 10);
    inserir(f, 70, 9);
    acessar(f, &valor, &media);
    printf("Inicio da fila: %d e %.02f \n", valor, media);
    destruir(f);
    return 0;
}