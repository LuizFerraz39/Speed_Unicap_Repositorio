#include <stdio.h>
#include <stdlib.h>

typedef struct dados{
    int info;
    int Pos;
} *Dados;

void SortInfo(int n, Dados* array);
void SortPos(int n, Dados* array);
void Merge(int n, Dados* Carray, Dados* Darray, Dados* Marray, int HalfN);
void MergePos(int n, Dados* Carray, Dados* Darray, Dados* Marray, int HalfN);
void DadosPrint(int n, Dados* array);
void DadosGet(int n, Dados* array);
Dados* DadosCreate(int n);
int Buscabinaria(int n, Dados* array, int elem);
void RemoverDado(int n, Dados* array, int elem);

int main(){
    int tamanho;
    scanf("%d", &tamanho);
    Dados* Marray = DadosCreate(tamanho);
    DadosGet(tamanho, Marray);
    SortInfo(tamanho, Marray);


    int tamanho2;
    int elem;
    scanf("%d", &tamanho2);

    for (int i = 0; i < tamanho2; i++){
        scanf("%d", &elem);
        int aux = Buscabinaria(tamanho, Marray, elem);
        RemoverDado(tamanho, Marray, aux);
        tamanho--;
    }    

    SortPos(tamanho, Marray);
    DadosPrint(tamanho, Marray);
    return 0;
}

void SortPos(int n, Dados* array){
    int BaseA, BaseB;
    if (n == 1){
        return;
    }
    else if (n == 2){
        BaseA = array[0]->Pos;
        BaseB = array[1]->Pos;

        if (BaseA > BaseB){
            Dados temp = array[0];

            array[0] = array[1];
            array[1] = temp;
        }
        return;
    }
    else{
        int HalfN;
        HalfN = n/2;
            Dados* Carray = DadosCreate(HalfN);
            Dados* Darray = DadosCreate(n-HalfN);
            for (int i = 0; i < HalfN; i++){
                Carray[i] = array[i];
            }
            for (int i = 0; i+HalfN < n; i++){
                Darray[i] = array[i+HalfN];
            }
        SortPos(HalfN, Carray);
        SortPos(n - HalfN, Darray);
        MergePos(n, Carray, Darray, array, HalfN);
        free(Carray);
        free(Darray);
        return;
    }
}

void RemoverDado(int n, Dados* array, int elem){
    for (int i = elem; i < n-1; i++){
        array[i] = array[i +1]; 
    }
    return;
}

int Buscabinaria(int n, Dados* array, int elem){
    int inicio = 0;
    int final = n-1;
    int meio;

    while (inicio <= final){
        meio = (inicio + final) / 2;

        if (array[meio]->info == elem){
            return meio;
        }
        else if(array[meio]->info < elem){
                inicio = meio + 1;
        }
        else {
            final = meio - 1;
        }

    }

    return -1;

}

void DadosPrint(int n, Dados* array){
    printf("%d" , array[0]->info);
    for (int i = 1; i < n; i++){
        printf(" %d" , array[i]->info);
    }
    printf("\n");
    return;
}

void DadosGet(int n, Dados* array){
    for (int i = 0; i < n; i++){
        scanf("%d", &array[i]->info);
        array[i]->Pos = i;
    }
}

Dados* DadosCreate(int n){
    Dados* array = malloc(n * sizeof(Dados));
    for (int i = 0; i<n; i++){
        array[i] = malloc(sizeof(struct dados));    
    }
    return array;
}

void SortInfo(int n, Dados* array){
    int BaseA, BaseB;
    if (n == 1){
        return;
    }
    else if (n == 2 ){
        BaseA = array[0]->info;
        BaseB = array[1]->info;

        if (BaseA > BaseB){
            Dados temp = array[0];

            array[0] = array[1];
            array[1] = temp;
        }
        return;
    }
    else{
        int HalfN;
        HalfN = n/2;
            Dados* Carray = DadosCreate(HalfN);
            Dados* Darray = DadosCreate(n-HalfN);
            for (int i = 0; i < HalfN; i++){
                Carray[i] = array[i];
            }
            for (int i = 0; i+HalfN < n; i++){
                Darray[i] = array[i+HalfN];
            }
        SortInfo(HalfN, Carray);
        SortInfo(n - HalfN, Darray);
        Merge(n, Carray, Darray, array, HalfN);
        free(Carray);
        free(Darray);
        return;
    }
}       

void MergePos(int n, Dados* Carray, Dados* Darray, Dados* Marray, int HalfN){
    int i, j, k, CodeBreak;
    i = j = k = CodeBreak = 0;
    while (1){
        if (Carray[i]->Pos < Darray[j]->Pos){
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

void Merge(int n, Dados* Carray, Dados* Darray, Dados* Marray, int HalfN){
    int i, j, k, CodeBreak;
    i = j = k = CodeBreak = 0;
    while (1){
        if (Carray[i]->info < Darray[j]->info){
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
