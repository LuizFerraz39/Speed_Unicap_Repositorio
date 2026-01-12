#include <stdio.h>
#include <stdlib.h>

void Sort(int n, int* array);
void Merge(int n, int* Carray, int* Darray, int* Marray, int HalfN);
void ArrayPrint(int n, int* array);
void ArrayGet(int n, int* array);

int main(){
    int tamanho;
    printf("Bom dia \nFavor digitar o tamanho do Array que vai ser ordenado \n");
    scanf("%d", &tamanho);
    int* arrayO = calloc(tamanho, sizeof(int));
    printf("Favor digitar o Array que vai ser ordenado \n");
    ArrayGet(tamanho, arrayO);
    Sort(tamanho, arrayO);
    ArrayPrint(tamanho, arrayO);
    free(arrayO);
    return 0;
}

void ArrayPrint(int n, int* array){
    printf("%d" , array[0]);
    for (int i = 1; i < n; i++){
        printf(" %d" , array[i]);
    }
    printf("\n");
    return;
}

void ArrayGet(int n, int* array){
    for (int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }
}

void Sort(int n, int* array){
    int BaseA, BaseB;
    if (n == 1){
        return;
    }
    else if (n == 2 ){
        BaseA = array[0];
        BaseB = array[1];

        if (BaseA > BaseB){
            array[0] = BaseB;
            array[1] = BaseA;
        }
        return;
    }
    else{
        int HalfN;
        HalfN = n/2;
            int* Carray = calloc(HalfN, (sizeof(int)));
            int* Darray = calloc(n - HalfN, (sizeof(int)));
            for (int i = 0; i < HalfN; i++){
                Carray[i] = array[i];
            }
            for (int i = 0; i+HalfN < n; i++){
                Darray[i] = array[i+HalfN];
            }
        Sort(HalfN, Carray);
        Sort(n - HalfN, Darray);
        Merge(n, Carray, Darray, array, HalfN);
        free(Carray);
        free(Darray);
        return;
    }
}       

void Merge(int n, int* Carray, int* Darray, int* Marray, int HalfN){
    int i, j, k, CodeBreak;
    i = j = k = CodeBreak = 0;
    while (1){
        if (Carray[i] < Darray[j]){
            Marray[k] = Carray[i];
            i++;
            k++;
            if (i == HalfN){
                break;
            } 
        }
        else{
            Marray[k] = Darray[j];
            j++;
            k++;
            if (j == n-HalfN){
                CodeBreak= 1;
                break;
            }
        }
    }
    if (CodeBreak){
        while (k<n){
            Marray[k] = Carray[i];
            i++;
            k++;
        }
    }
    else{
        while (k<n){
            Marray[k] = Darray[j];
            j++;
            k++;
        }
    }
    return;
}
