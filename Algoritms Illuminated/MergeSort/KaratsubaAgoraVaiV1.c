#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void NumberGet (char* estring, int* number, int size);
void ArrayPrintV1 (int* array, int n);
void ArrayPrintV2 (int* array, int n);
void StringPrint (char* array, int n);
void Karatsuba (int* num1, int* num2, int* num3, int size3);
int SizeGet (int size1, int size2);
void GetADBC (int* basePQ,int* baseAC,int* baseBD, int* baseADBC, int size, int big);
void BigSum (int* bigAC, int* bigADBC, int* baseBD, int size3, int* num3);

int main(){
    int size1, size2, size3;
    char* pre_number1 = malloc(100 * sizeof(char));
    char* pre_number2 = malloc(100 * sizeof(char));

    printf("Bom dia, Bem-vindo a multiplicacao do Karatusuba \nFavor digitar o primeiro numero\n");
    fgets(pre_number1, 100, stdin);
    printf("Favor digitar o segundo numero\n");
    fgets(pre_number2, 100, stdin);

    size1 = strlen(pre_number1) - 1;
    size2 = strlen(pre_number2) - 1;
    size3 = SizeGet(size1, size2);
    printf("%d \n", size3);

    int* number1 = calloc(size3, sizeof(int));
    int* number2 = calloc(size3, sizeof(int));
    int* number3 = calloc(size3*8, sizeof(int));

    NumberGet(pre_number1, number1, size1);
    NumberGet(pre_number2, number2, size2);

    printf("--------Checagem de input-----------\n");
    StringPrint(pre_number1, size1);
    ArrayPrintV2(number1, size1);
    printf("--------Checagem de input-----------\n");

    free(pre_number1);
    free(pre_number2);

    Karatsuba(number1, number2, number3, size3);

    printf("O resultado da multiplicacao:\n");
    printf("%d \n", size3);
    ArrayPrintV2(number3, size3*2);

    free(number1);
    free(number2);
    free(number3);
    return 0;
}

void Karatsuba (int* num1, int* num2, int* num3, int size3){
    if (size3 == 1){
        int mult = 0;
        mult = num1[0] * num2[0];
        num3[0] = mult%10;
        num3[1] = mult/10;
        return;   
    }
    else{
    
    int size4 = (size3+1)/2;
    int size5 = size3/2;
    int size6 = size4*2;
    int* baseA = calloc(size4*2, sizeof(int)); 
    int* baseB = calloc(size4*2, sizeof(int)); 
    int* baseC = calloc(size4*2, sizeof(int)); 
    int* baseD = calloc(size4*2, sizeof(int)); 
    int* baseP = calloc((size4+1)*2, sizeof(int)); 
    int* baseQ = calloc((size4+1)*2, sizeof(int)); 

    for (int i = 0; i<size4;i++){
        baseB[i] = num1[i];
        baseD[i] = num2[i];
    }

    for (int i = 0; i<size5;i++){
        baseA[i] = num1[size4+i];
        baseC[i] = num2[size4+i];
    }
    int carry = 0;
    int soma = 0;
    for (int i = 0; i<size4;i++){
        soma = (baseA[i] + baseB[i] + carry);
        baseP[i] = soma%10;
        carry = soma/10;
    }
    baseP[size4] = carry;
    
    carry = 0;
    soma = 0;
    for (int i = 0; i<size4;i++){
        soma = (baseC[i] + baseD[i] + carry);
        baseQ[i] = soma%10;
        carry = soma/10;
    }
    baseQ[size4] = carry;

    int* baseAC = calloc(size6*4, sizeof(int));
    Karatsuba(baseA, baseC, baseAC, size4);
    int* baseBD = calloc(size6*4, sizeof(int));
    Karatsuba(baseB, baseD, baseBD, size4);

    printf("-----------------Iteracao BD----------------\n");
    printf("BaseB da interacao: ------------\n");
    ArrayPrintV2(baseB,size4);
    printf("BaseD da interacao: ------------\n");
    ArrayPrintV2(baseD,size4);
    printf("BaseBD da interacao: ------------\n");
    ArrayPrintV2(baseBD,size6);


    int big = 0;
    int big2 = 0;
    int* baseADBC = calloc((size6+1)*4, sizeof(int));

    int* basePQ = calloc((size6+1)*4, sizeof(int));
    printf("Etapa de calcular o PQ\n");
    if (baseP[size4] || baseQ[size4]){
        big = 1;
        Karatsuba(baseP, baseQ, basePQ, size4+1);
        if (basePQ[size6] != 0){
            big2 = 1;
        }
        GetADBC(basePQ, baseAC, baseBD, baseADBC, size6, big2);
    }
    else{
        Karatsuba(baseP, baseQ, basePQ, size4);
        GetADBC(basePQ, baseAC, baseBD, baseADBC, size6, 0);
    }
    printf("Etapa de calcular o ADBC\n");


    printf("-----------------Iteracao PQ----------------\n");
    printf("BaseA da interacao: ------------\n");
    ArrayPrintV2(baseA,size4);
    printf("BaseB da interacao: ------------\n");
    ArrayPrintV2(baseB,size4);
    printf("BaseP que foi a soma: -----\n");
    ArrayPrintV2(baseP, size4+1);
    printf("BaseQ que foi a soma: -----\n");
    ArrayPrintV2(baseQ, size4+1);
    printf("BasePQ que foi o produto --\n");
    ArrayPrintV2(basePQ, size3+1);

    int* bigAC = calloc(size6*8, sizeof(int));
    for (int i = 0; i<size6;i++){
        bigAC[i+size6] =baseAC[i]; 
    }
    int* bigADBC = calloc(size6*8, sizeof(int));
    if (big2){
        for (int i = 0; i<size6+1;i++){
            bigADBC[i+size4] = baseADBC[i]; 
        }
    }
    else{
        for (int i = 0; i<size6;i++){
            bigADBC[i+size4] = baseADBC[i]; 
        }
    }
    int* bigBD = calloc(size6*8, sizeof(int));
    for (int i = 0; i<size6; i++){
        bigBD[i] = baseBD[i];
    }
    printf("---------------Iteracao Pre-BIGSUM-----------------\n");
    printf("BigAC da interacao: ------------\n");
    ArrayPrintV2(bigAC, size6*2);
    BigSum(bigAC,bigADBC,bigBD,size6,num3);
    printf("---------------Tentando dar free-----------------\n");
    free(baseA);
    free(baseB);
    free(baseC);
    free(baseD);
    free(baseAC);
    free(baseBD);
    free(baseADBC);
    free(baseP);
    free(baseQ);
    free(basePQ);
    free(bigAC);
    free(bigADBC);
    free(bigBD);
    printf("---------------Tentando depois de dar o free-----------------\n");
    return;
    }
}

void GetADBC (int* basePQ,int* baseAC,int* baseBD, int* baseADBC, int size, int big){
    int soma, carry;
    soma = carry = 0;
    if (big){
        for (int i = 0; i < size; i++){
            soma = basePQ[i] - baseAC[i] - baseBD[i] - carry;
            if (soma < -10){
                baseADBC[i] = soma+20;
                carry = 2;
            }
            else if (soma < 0){
                baseADBC[i] = soma+10;
                carry = 1;
            }
            else{
                baseADBC[i] = soma;
                carry = 0;
            }
        }
        baseADBC[size] = basePQ[size] - carry;
    }
    else{
        for (int i = 0; i < size; i++){
            soma = basePQ[i] - baseAC[i] - baseBD[i] - carry;
            if (soma < -10){
                baseADBC[i] = soma+20;
                carry = 2;
            }
            else if (soma < 0){
                baseADBC[i] = soma+10;
                carry = 1;
            }
            else{
                baseADBC[i] = soma;
                carry = 0;
            }
        }
    }
/*     printf("---------------Iteracao-----------------\nBasePQ da interacao: ------------\n");
    if(big){
        ArrayPrintV2(basePQ,size+1);
    }
    else{
        ArrayPrintV2(basePQ,size+1);
    }
    printf("BaseAC da interacao: ------------\n");
    ArrayPrintV2(baseAC,size);
    printf("BaseBD da interacao: ------------\n");
    ArrayPrintV2(baseBD,size);
    printf("BaseADBC que foi o produto: -----\n");
    ArrayPrintV2(baseADBC,size+1); */
    return;
}

void BigSum (int* bigAC, int* bigADBC, int* bigBD, int size3, int* num3){
    int soma, carry;
    soma = carry = 0;
    for (int i = 0; i<size3*2;i++){
        soma = bigAC[i] + bigADBC[i] + bigBD[i] + carry;
        carry = soma/10;
        assert(i < size3 * 2);
        num3[i] = soma%10;
    }
    printf("---------------Iteracao BIGSUM-----------------\n");
    printf("BigAC da interacao: ------------\n");
    ArrayPrintV2(bigAC,size3*2);
    printf("BigADBC que foi o produto: -----\n");
    ArrayPrintV2(bigADBC,size3*2);
    printf("BigBD da interacao: ------------\n");
    ArrayPrintV2(bigBD,size3*2);
}

void NumberGet (char* estring, int* number, int size){
    for (int i = 0; i < size; i++){
        number[i] = estring[size-i-1] - '0';
    }
    return;
}

void ArrayPrintV1 (int* array, int n){
    for (int i = 0; i < n; i++){
        printf("%d" , array[i]);
    }
    printf("\n");
    return;
}

void ArrayPrintV2 (int* array, int n){
    for (int i = n-1; i > -1; i--){
        printf("%d" , array[i]);
    }
    printf("\n");
    return;
}

void StringPrint (char* array, int n){
    for (int i = 0; i < n; i++){
        printf("%c" , array[i]);
    }
    printf("\n");
    return;
}

int SizeGet (int size1, int size2){
    int size3;
    if (size1 > size2){
        size3 = size1;
    }
    else{
        size3 = size2;
    }
    return size3;
}