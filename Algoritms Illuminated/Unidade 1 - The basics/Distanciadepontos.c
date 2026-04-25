#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct pares {
    double px;
    double py;
} *Pares;

typedef struct conjunto{
    Pares p1;
    Pares p2;
    double d;
} *Conjunto;

Pares* ParesGet(int n);
Pares* Paresclone(Pares* pares, int n);
Pares* Paresclonehalf(Pares* pares, int n);
void ParesPrint(Pares* pares, int n);
Pares* Pxsort(Pares* pares, int n);
Pares* Pysort(Pares* pares, int n);

Conjunto ClosestPair(Pares* px, Pares* py, int n);
Conjunto ClosestSplitPair(Pares* px, Pares* py, double best, int n);

void xSort(Pares* array, int n);
void ySort(Pares* array, int n);
void xMerge(int n, Pares* Carray, Pares* Darray, Pares* Marray, int HalfN);
void yMerge(int n, Pares* Carray, Pares* Darray, Pares* Marray, int HalfN);

double CalcDistancia(Pares p1, Pares p2);
void resultfill(Conjunto* n1, Pares par1, Pares par2, double dist);
void parclone(Pares* n1, Pares n2);
void freePares(Pares* par, int n);
void freeConjunto(Conjunto n1);
Conjunto MelhorConjunto(Conjunto n1, Conjunto n2, Conjunto n3);
void PrintarConjunto(Conjunto n1);

int main(){
    int n;
    printf("Digite a quantidade de pares: \n");
    scanf("%d", &n);

    Pares* pares = ParesGet(n);
    ParesPrint(pares, n);

    Pares* px = Paresclone(pares, n);
    Pares* py = Paresclone(pares, n);
    xSort(px, n);
    ySort(py, n);

    Conjunto resultado = ClosestPair(px, py, n);

    PrintarConjunto(resultado);

    freePares(px, n);
    freePares(py, n);
    freeConjunto(resultado);
}

Conjunto ClosestPair(Pares* px, Pares* py, int n){
    Conjunto result = malloc(sizeof(struct conjunto));
    if (n==2){
        resultfill(&result, px[0], px[1], CalcDistancia(px[0],px[1]));
        return result;
    }
    if (n==3){
        double n1 = CalcDistancia(px[0], px[1]);
        double n2 = CalcDistancia(px[0], px[2]);
        double n3 = CalcDistancia(px[1], px[2]);

        if (n1 == fmin(n1, fmin(n2,n3))){
            resultfill(&result, px[0], px[1], n1);
            return result;
        }
        else if(n2 == fmin(n1, fmin(n2,n3))){
            resultfill(&result, px[0], px[2], n2);
            return result;
        }
        else{
            resultfill(&result, px[1], px[2], n3);
            return result;
        }
    }

    int halfn = n/2;
    Pares* Lx = Paresclone(px, halfn);
    Pares* Ly = Paresclone(py, halfn);
    Pares* Rx = Paresclonehalf(px, n);
    Pares* Ry = Paresclonehalf(py, n);

    Conjunto Lpair = ClosestPair(Lx, Ly, halfn);
    Conjunto Rpair = ClosestPair(Rx, Ry, n-halfn);
    Conjunto Splitpair = ClosestSplitPair(px, py, fmin(Lpair->d, Rpair->d), n);

    Conjunto Melhor = MelhorConjunto(Lpair, Rpair, Splitpair);
    resultfill(&result, Melhor->p1, Melhor->p2, Melhor->d);

    freeConjunto(Lpair);
    freeConjunto(Rpair);
    if (Splitpair != NULL){
        freeConjunto(Splitpair); 
    }
    freePares(Lx,halfn);   
    freePares(Ly,halfn);   
    freePares(Rx, n - halfn);   
    freePares(Ry, n - halfn);   

    return result;
}

Conjunto ClosestSplitPair(Pares* px, Pares* py, double best, int n){
    int halfn = n/2;
    double xabs = px[halfn-1]->px;
    double min = xabs-best;
    double max = xabs+best;

    int qtd = 0;  
    Conjunto bestPair = NULL;
    Pares* Spar = malloc(n * sizeof(Pares));

    for (int i = 0; i < n; i ++){
        if (py[i]->px > min && py[i]->px < max){
            Spar[qtd] = py[i];
            qtd++;
        }
    }

    if (qtd == 0){
        return bestPair;
    }


    for(int i = 1; i < qtd; i++){
        for (int j = 1; j < fmin(7, qtd-i)+1; j++){
            printf("i = %d, j = %d, qtd = %d",i , j , qtd);
            if (CalcDistancia(Spar[i-1],Spar[i+j-1]) < best){
                best = CalcDistancia(Spar[i-1],Spar[i+j-1]);
                resultfill(&bestPair, Spar[i-1], Spar[i+j-1], best);
            }
        }
    }
    free(Spar);
    return bestPair;
}

void freePares(Pares* par, int n){
    for (int i = 0; i < n; i++){
        free(par[i]);
    }
    free(par);
}
void freeConjunto(Conjunto n1){
    free(n1->p1);
    free(n1->p2);
    free(n1);
}
void PrintarConjunto(Conjunto n1){
    printf("O conjunto foi: \nPar 1: (%.2lf, %.2lf)\nPar 2: (%.2lf, %.2lf)\nDistancia : (%.2lf)\n", n1->p1->px, n1->p1->py, n1->p2->px, n1->p2->py, n1->d);
}

Conjunto MelhorConjunto(Conjunto n1, Conjunto n2, Conjunto n3){
    double menor;
    if (n3 != NULL){
        menor = fmin(n1->d, fmin(n2->d, n3->d));
    }
    else{
        menor = fmin(n1->d, n2->d);
    }

    if (n1->d == menor){
        return n1;
    }
    else if (n2->d == menor){
        return n2;
    }
    else{
        return n3;
    }
}

double CalcDistancia(Pares p1, Pares p2){
    double n1 = p1->px - p2->px;
    double n2 = p1->py - p2->py;
    double n3 = n1*n1 + n2*n2;

    return sqrt(n3);
}

void resultfill(Conjunto* n1, Pares par1, Pares par2, double dist){
    if ((*n1) == NULL){
        (*n1) = malloc(sizeof(struct conjunto));
    }

    (*n1)->p1 = malloc(sizeof(struct pares));
    (*n1)->p2 = malloc(sizeof(struct pares));

    parclone(&((*n1)->p1), par1);
    parclone(&((*n1)->p2), par2);

    (*n1)->d = dist;
}

void parclone(Pares* n1, Pares n2){
    (*n1)->px = n2->px; 
    (*n1)->py = n2->py; 
}

Pares* Paresclone(Pares* pares, int n){
    Pares* clone = malloc(n * sizeof(Pares));
    for (int i = 0; i < n; i ++){
        clone[i] = malloc(sizeof(struct pares));
        clone[i]->px = pares[i]->px;
        clone[i]->py = pares[i]->py;
    }

    return clone;
}

Pares* Paresclonehalf(Pares* pares, int n){
    int halfn = n/2;
    
    Pares* clone = malloc(n * sizeof(Pares));
    for (int i = 0; i+halfn < n; i++){
        clone[i] = malloc(sizeof(struct pares));
        clone[i]->px = pares[i+halfn]->px;
        clone[i]->py = pares[i+halfn]->py;
    }

    return clone;
}

Pares* ParesGet(int n){
    Pares* pares = malloc(n * sizeof(Pares));
    for (int i = 0; i < n; i++){
        pares[i] = malloc (sizeof(struct pares));
        scanf("%lf %lf", &pares[i]->px, &pares[i]->py);
    }

    return pares;
}

void ParesPrint(Pares* pares, int n){
    for (int i = 0; i < n; i++){

        printf("Par %d : %.2lf %.2lf\n", i+1, pares[i]->px, pares[i]->py);

    }
}

void ySort(Pares* array, int n){
    Pares BaseA, BaseB;
    if (n == 1){
        return;
    }
    else if (n == 2){
        BaseA = array[0];
        BaseB = array[1];

        if (BaseA->py > BaseB->py){
            array[0] = BaseB;
            array[1] = BaseA;
        }
        return;
    }
    else{
        int HalfN;
        HalfN = n/2;
            Pares* Carray = calloc(HalfN, (sizeof(Pares)));
            Pares* Darray = calloc(n - HalfN, (sizeof(Pares)));
            for (int i = 0; i < HalfN; i++){
                Carray[i] = array[i];
            }
            for (int i = 0; i+HalfN < n; i++){
                Darray[i] = array[i+HalfN];
            }
        ySort(Carray, HalfN);
        ySort(Darray, n - HalfN);
        yMerge(n, Carray, Darray, array, HalfN);
        free(Carray);
        free(Darray);
        return;
    }
}    

void xSort(Pares* array, int n){
    Pares BaseA, BaseB;
    if (n == 1){
        return;
    }
    else if (n == 2){
        BaseA = array[0];
        BaseB = array[1];

        if (BaseA->px > BaseB->px){
            array[0] = BaseB;
            array[1] = BaseA;
        }
        return;
    }
    else{
        int HalfN;
        HalfN = n/2;
            Pares* Carray = calloc(HalfN, (sizeof(Pares)));
            Pares* Darray = calloc(n - HalfN, (sizeof(Pares)));
            for (int i = 0; i < HalfN; i++){
                Carray[i] = array[i];
            }
            for (int i = 0; i+HalfN < n; i++){
                Darray[i] = array[i+HalfN];
            }
        xSort(Carray, HalfN);
        xSort(Darray, n - HalfN);
        xMerge(n, Carray, Darray, array, HalfN);
        free(Carray);
        free(Darray);
        return;
    }
}       

void xMerge(int n, Pares* Carray, Pares* Darray, Pares* Marray, int HalfN){
    int i, j, k, CodeBreak;
    i = j = k = CodeBreak = 0;
    while (1){
        if (Carray[i]->px < Darray[j]->px){
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

void yMerge(int n, Pares* Carray, Pares* Darray, Pares* Marray, int HalfN){
    int i, j, k, CodeBreak;
    i = j = k = CodeBreak = 0;
    while (1){
        if (Carray[i]->py < Darray[j]->py){
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


/* 
Lista de bugs do codigo:

Formula da calcula de distancia estava errada
    No lugar de subtrair os pontos, eu estava somando

Não converti corretamente o Pseudo-Codigo para o código
    No pseudocodigo, ele usava i=1 e j=1, numa soma i+j, ele nunca iria dar 0;
    Mas no meu ele fazia isso, com i=0 e j=0, isso fazia i+j = i, o que não pode acontecer
    Tive que consertar fazendo i+j-1

Dei Control + V sem corrijir
    xMerge usava py invés de px

Tentei remover a função resultfill e fiz errado
    Tentei remover a função porque pensei que tinha bugs, mas eu fiz isso de uma forma errada
    Fazendo com que o SplitPair não tivesse os Pares, mas sim ponteiros pra eles, que eu dava
    Free aonde os ponteiros apontavam depois

*/