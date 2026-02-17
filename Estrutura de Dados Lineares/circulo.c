#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"

struct Sphere{
    float raio;
    float area;
    float perimetro;
};

Sphere CreateS (float raio){
    if (raio < 0){
        raio *= -1;
    }

    Sphere s = malloc(sizeof(struct Sphere));

    s->raio = raio;
    s->area = raio*raio*3.14;
    s->perimetro = raio*2*3.14;

    return s;
}

float RadiusS (Sphere s){
    return s->raio;
}
float AreaS (Sphere s){
    return s->area;
}
float PerimeterS (Sphere s){
    return s->perimetro;
}
void PrintS (Sphere s){
    printf("O circulo de raio %.2f possui as seguintes medidas: \nArea = %.2f \nPerimetro = %.2f \n", (RadiusS(s)), (AreaS(s)), (PerimeterS(s)));
}
void FreeS (Sphere s){
    free(s);
}
