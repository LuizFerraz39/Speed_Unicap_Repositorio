#include <stdio.h>
#include <stdlib.h>

void Sort(int n, int* array);
void Merge(int n, int* Carray, int* Darray, int* Marray, int HalfN);
void ArrayPrint(int n, int* array);
void ArrayGet(int n, int* array);
int Sort_CountInv(int n, int* array);
int Merge_CountSplitInv(int HalfN, int n, int* Carray, int* Darray, int* Marray);

int main(){
    int tamanho, inversions;
    printf("Bom dia \nFavor digitar o tamanho do Array que vai ser ordenado e ter suas inversoes contadadas \n");
    scanf("%d", &tamanho);
    int* arrayO = calloc(tamanho, sizeof(int));
    printf("Favor digitar o Array\n");
    ArrayGet(tamanho, arrayO);

    inversions = Sort_CountInv(tamanho, arrayO);
    printf("Seu array ordenado: \n");
    ArrayPrint(tamanho, arrayO);
    printf("O total de inversoes: \n%d", inversions);
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

int Sort_CountInv(int n, int* array){
    if (n == 0 || n == 1){
        return 0;
    }
    else{
        int Cinv, Dinv;
        int* Chalf = calloc (n,(sizeof(int)));
        int* Dhalf = calloc (n,(sizeof(int)));
        int Nhalf = n/2;
        for (int i = 0; i <Nhalf;i++){
            Chalf[i] = array[i];
        }
        for (int i = 0; i+Nhalf < n; i++){
            Dhalf[i] = array[i+Nhalf];
        }

        Cinv = Sort_CountInv(Nhalf, Chalf);
        Dinv = Sort_CountInv(n-Nhalf,Dhalf);

        int Minv = Merge_CountSplitInv(Nhalf, n, Chalf, Dhalf, array);

        free(Chalf);
        free(Dhalf);

        return Cinv+Dinv+Minv;
    }
}

int Merge_CountSplitInv(int HalfN, int n, int* Carray, int* Darray, int* Marray){
    int i, j, k, CodeBreak, Minv;
    i = j = k = CodeBreak = Minv = 0;
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
            Minv = Minv + (HalfN - i);
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
    return Minv;
}
