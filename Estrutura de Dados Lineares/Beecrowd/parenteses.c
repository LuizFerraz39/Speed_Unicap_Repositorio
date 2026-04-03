#include<stdio.h>
#include<stdlib.h>

int main(){
    int fecha, abre;
    char ler;
    
    char linha[1000];
    
    while (fgets(linha, 1000, stdin) != NULL) {
        fecha = abre = 0;
        int tamanho = strlen(linha);
        
        for (int i = 0; i < tamanho; i++){
            if (linha[i] == '('){
                abre++;
            }
            if (linha[i] == ')'){
                abre--;
                if (abre < 0){
                    break;
                }
            }
        }

        if (abre == 0){
            printf("correct\n");
        }
        else{
            printf("incorrect\n");
        }

    }

    return 0;
}