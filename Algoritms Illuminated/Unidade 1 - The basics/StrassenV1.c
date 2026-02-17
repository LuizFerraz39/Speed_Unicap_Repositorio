#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Matrix_Get(int x, int y, int n, int** matrix);
void Matrix_Fill(int x, int y, int n, int** matrix);
void Matrix_Print(int x, int y, int** matrix);
int Nget (int x, int y);
void Strassen (int n, int** ma, int** mb, int** mc);
void Matrix_Sub (int n, int** ma, int** mb, int** mc);
void Matrix_Add (int n, int** ma, int** mb, int** mc);
void Matrix_Void (int n, int** ma);
void Matrix_Divisions ();



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

    if (y1 != x2){
        printf("Uma matriz %dx%d nao multiplica uma matriz %dx%d", x1,y1,x2,y2);
        return 0;
    }
    else{

    int** mC = calloc (n3 * 2, sizeof(int*));
    for (int i = 0; i < n3*2;i++){
        mC[i] = calloc (n3*2, sizeof(int));
    }

    Strassen (n3, mA, mB, mC);

    printf("Matriz A: \n");
    Matrix_Print(x1, y1, mA);
    printf("Matriz B: \n");
    Matrix_Print(x2, y2, mB);
    printf("Resultado: \nMatriz C: \n");
    Matrix_Print(x1,y2, mC);

    Matrix_Void(n3*2, mA);
    Matrix_Void(n3*2, mB);
    Matrix_Void(n3*2, mC);
    }
    return 0;
}

void Strassen (int n, int** ma, int** mb, int**mc){
    if (n==1){
        mc[0][0] = ma[0][0] * mb[0][0];
        return;
    }
    else{
    if (n%2 == 1){
        n++;
    }
        int** sda = calloc(n, sizeof(int*));
        int** sdb = calloc(n, sizeof(int*));
        int** sdc = calloc(n, sizeof(int*));
        int** sdd = calloc(n, sizeof(int*));
        int** sde = calloc(n, sizeof(int*));
        int** sdf = calloc(n, sizeof(int*));
        int** sdg = calloc(n, sizeof(int*));
        int** sdh = calloc(n, sizeof(int*));

        int n3 = n/2;
        int** p1 = calloc(n, sizeof(int*));
        int** p2 = calloc(n, sizeof(int*));
        int** p3 = calloc(n, sizeof(int*));
        int** p4 = calloc(n, sizeof(int*));
        int** p5 = calloc(n, sizeof(int*));
        int** p6 = calloc(n, sizeof(int*));
        int** p7 = calloc(n, sizeof(int*));
        int** p1t = calloc(n, sizeof(int*));
        int** p2t = calloc(n, sizeof(int*));
        int** p3t = calloc(n, sizeof(int*));
        int** p4t = calloc(n, sizeof(int*));
        int** p5t = calloc(n, sizeof(int*));
        int** p6t = calloc(n, sizeof(int*));
        int** p7t = calloc(n, sizeof(int*));
        int** p5tt = calloc(n, sizeof(int*));
        int** p6tt = calloc(n, sizeof(int*));
        int** p7tt = calloc(n, sizeof(int*));

        int** sdda = calloc(n, sizeof(int*));
        int** sddat = calloc(n, sizeof(int*));
        int** sddatt = calloc(n, sizeof(int*));
        int** sddb = calloc(n, sizeof(int*));
        int** sddc = calloc(n, sizeof(int*));
        int** sddd = calloc(n, sizeof(int*));
        int** sdddt = calloc(n, sizeof(int*));
        int** sdddtt = calloc(n, sizeof(int*));

        for (int i = 0; i < n; i++){
            p1[i] = calloc(n, sizeof(int));
            p2[i] = calloc(n, sizeof(int));
            p3[i] = calloc(n, sizeof(int));
            p4[i] = calloc(n, sizeof(int));
            p5[i] = calloc(n, sizeof(int));
            p6[i] = calloc(n, sizeof(int));
            p7[i] = calloc(n, sizeof(int));
            p1t[i] = calloc(n, sizeof(int));
            p2t[i] = calloc(n, sizeof(int));
            p3t[i] = calloc(n, sizeof(int));
            p4t[i] = calloc(n, sizeof(int));
            p5t[i] = calloc(n, sizeof(int));
            p6t[i] = calloc(n, sizeof(int));
            p7t[i] = calloc(n, sizeof(int));
            p5tt[i] = calloc(n, sizeof(int));
            p6tt[i] = calloc(n, sizeof(int));
            p7tt[i] = calloc(n, sizeof(int));

            sdda[i] = calloc(n, sizeof(int));
            sddat[i] = calloc(n, sizeof(int));
            sddatt[i] = calloc(n, sizeof(int));
            sddb[i] = calloc(n, sizeof(int));
            sddc[i] = calloc(n, sizeof(int));
            sddd[i] = calloc(n, sizeof(int));
            sdddt[i] = calloc(n, sizeof(int));
            sdddtt[i] = calloc(n, sizeof(int));

            sda[i] = calloc(n, sizeof(int));
            sdb[i] = calloc(n, sizeof(int));
            sdc[i] = calloc(n, sizeof(int));
            sdd[i] = calloc(n, sizeof(int));
            sde[i] = calloc(n, sizeof(int));
            sdf[i] = calloc(n, sizeof(int));
            sdg[i] = calloc(n, sizeof(int));
            sdh[i] = calloc(n, sizeof(int)); 
        }
        for (int i = 0; i<n3;i++){
            for (int j = 0; j<n3;j++){
                sda[i][j] = ma[i][j];
                sdb[i][j] = ma[i][j+(n3)];
                sdc[i][j] = ma[i+(n3)][j];
                sdd[i][j] = ma[i+(n3)][j+(n3)];
                sde[i][j] = mb[i][j];
                sdf[i][j] = mb[i][j+(n3)];
                sdg[i][j] = mb[i+(n3)][j];
                sdh[i][j] = mb[i+(n3)][j+(n3)];
            }
        }
        Matrix_Print(n,n,sda);
        Matrix_Print(n,n,sdb);
        Matrix_Print(n,n,sdc);
        Matrix_Print(n,n,sdd);
        Matrix_Print(n,n,sde);
        Matrix_Print(n,n,sdf);
        Matrix_Print(n,n,sdg);
        Matrix_Print(n,n,sdh);
        
        /* Calculo P1 */
        Matrix_Sub(n3,sdf,sdh,p1t);
        Strassen(n3,sda,p1t,p1); 
        /* Calculo P2 */
        Matrix_Add(n3,sda,sdb,p2t);
        Strassen(n3,p2t,sdh,p2);
        /* Calculo P3 */
        Matrix_Add(n3,sdc,sdd,p3t);
        Strassen(n3, p3t, sde, p3);
        /* Calculo P4 */
        Matrix_Sub(n3,sdg,sde,p4t);
        Strassen(n3,sdd,p4t,p4);
        /* Calculo P5 */
        Matrix_Add(n3, sda, sdd, p5t);
        Matrix_Add(n3, sde, sdh, p5tt);
        Strassen(n3, p5t, p5tt, p5);
        /* Calculo P6 */
        Matrix_Sub(n3, sdb, sdd, p6t);
        Matrix_Add(n3, sdg, sdh, p6tt);
        Strassen(n3, p6t, p6tt, p6);
        /* Calculo P7 */
        Matrix_Sub(n3, sda, sdc, p7t);
        Matrix_Add(n3, sde, sdf, p7tt);
        Strassen(n3, p7t, p7tt, p7);

        /* Calculo subdivisãofinal A */
        Matrix_Add(n3, p5,p4,sddat);
        Matrix_Sub(n3,sddat,p2,sddatt);
        Matrix_Add(n3, sddatt,p6,sdda);
        /* Calculo subdivisãofinal B */
        Matrix_Add(n3, p1,p2, sddb);
        /* Calculo subdivisãofinal C */
        Matrix_Add(n3, p3,p4,sddc);
        /* Calculo subdivisãofinal D */
        Matrix_Add(n3, p1,p5,sdddt);
        Matrix_Sub(n3,sdddt,p3,sdddtt);
        Matrix_Sub(n3, sdddtt,p7,sddd);

        for (int i = 0; i<n3;i++){
            for (int j = 0; j<n3;j++){
                mc[i][j]= sdda[i][j];
                mc[i][j+n3]= sddb[i][j];
                mc[i+n3][j]= sddc[i][j];
                mc[i+n3][j+n3]= sddd[i][j];
            }
        }

        Matrix_Void(n, sda); 
        Matrix_Void(n, sdb);
        Matrix_Void(n, sdc);
        Matrix_Void(n, sdd);
        Matrix_Void(n, sde);
        Matrix_Void(n, sdf);
        Matrix_Void(n, sdg);
        Matrix_Void(n, sdh);
        Matrix_Void(n, p1);
        Matrix_Void(n, p2);
        Matrix_Void(n, p3);
        Matrix_Void(n, p4);
        Matrix_Void(n, p5);
        Matrix_Void(n, p6);
        Matrix_Void(n, p7);
        Matrix_Void(n, p1t);
        Matrix_Void(n, p2t);
        Matrix_Void(n, p3t);
        Matrix_Void(n, p4t);
        Matrix_Void(n, p5t);
        Matrix_Void(n, p6t);
        Matrix_Void(n, p7t);
        Matrix_Void(n, p5tt);
        Matrix_Void(n, p6tt);
        Matrix_Void(n, p7tt);
        Matrix_Void(n, sdda);
        Matrix_Void(n, sddat);
        Matrix_Void(n, sddatt);
        Matrix_Void(n, sddb);
        Matrix_Void(n, sddc);
        Matrix_Void(n, sddd);
        Matrix_Void(n, sdddt);
        Matrix_Void(n, sdddtt);
        Matrix_Print(n, n, mc);
        return;
    }
}

void Matrix_Sub (int n, int** ma, int** mb, int** mc){
    for (int i = 0; i <n;i++){
        for (int j = 0; j<n;j++){
            mc[i][j] = ma[i][j] - mb[i][j];
        }
    }
}

void Matrix_Add (int n, int** ma, int** mb, int** mc){
    for (int i = 0; i <n;i++){
        for (int j = 0; j<n;j++){
            mc[i][j] = ma[i][j] + mb[i][j];
        }
    }
}

void Matrix_Get(int x, int y, int n, int** matrix){
    for (int i = 0; i < n*2; i++){
        matrix[i] = calloc(n*2, sizeof(int));
    }
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\n");
}

int Nget (int x, int y){
    if (x>y){
        return x;
    }
    else{
        return y;
    }
}

void Matrix_Print(int x, int y, int** matrix){
    for (int i = 0; i < x; i++){
        for (int j = 0 ; j < y; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void Matrix_Void (int n, int** ma){
    for (int i = 0; i < n; i++){
        free(ma[i]);
    }
    free(ma);
}