#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"

int main(){
    int quantidade;
    printf("Digite a quantidade de circulos: ");
    scanf("%d", &quantidade);

    Sphere* lista = malloc(quantidade * sizeof(Sphere));

    float raio;
    for (int i = 0; i<quantidade; i++){
        printf("Digite o raio do circulo %d:", i+1);
        scanf("%f", &raio);
        lista[i] = CreateS(raio);
    }

    float amenor = AreaS(lista[0]);
    int ida = 0;
    float pmaior = PerimeterS(lista[0]);
    int idp = 0;

    for (int i = 1; i<quantidade;i++){
        if (AreaS(lista[i]) < amenor){
            amenor = AreaS(lista[i]);
            ida = i;
        }
        if (PerimeterS(lista[i]) > pmaior){
            pmaior = PerimeterS(lista[i]);
            idp = i;
        }
    }

    printf("A menor area pertence ao circulo %d e eh %.2f \nO maior perimetro pertence ao circulo %d e eh %.2f ", ida+1,amenor,idp+1, pmaior);

    for (int i = 0; i < quantidade; i++){
        FreeS(lista[i]);
    }
    
    free(lista);
    
    return 0;
}