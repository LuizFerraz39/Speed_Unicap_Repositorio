#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, x1, y1, x2, y2;
    printf("Bem vindo a multiplicacao de matrizes Strassen\nFavor digitar o tamanho da matriz A\n");
    printf("Linhas: ");            scanf("%d", &x1);
    printf("\nColunas: ");         scanf("%d", &y1);
    printf("\nFavor digitar o tamanho da matriz B\n");
    printf("Linhas: ");            scanf("%d", &x2);
    printf("\nColunas: ");         scanf("%d", &y2);
    printf("\nFavor digitar a matriz A\n");
    int n1 = Nget(x1,y1);
    int n2 = Nget(x2,y2);
    int n3 = Nget(n1,n2);
    int** mA = calloc (n3 * 2, sizeof(int*));
    int** mB = calloc (n3 * 2, sizeof(int*));
    Matrix_Get(x1, y1, n3, mA);
    printf("Favor digitar a matriz B\n");
    Matrix_Get(x2, y2, n3, mB);

    int** mC = calloc (n3 * 2, sizeof(int*));
    for (int i = 0; i < n3*2;i++){
        mC[i] = calloc (n3*2, sizeof(int));
    }

    Matrix_Add(n3, mA, mB, mC);

    
}

void Matrix_Add (int n, int** ma, int** mb, int** mc){
    for (int i = 0; i <n;i++){
        for (int j = 0; j<n;j++){
            mc[i][j] = ma[i][j] + mb[i][j];
        }
    }
}