#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"

int main(){
    float r;

    printf("Digite o raio do circulo: ");
    scanf("%f", &r);

    Sphere s1 = CreateS(r);
    PrintS(s1);

    return 0;
}