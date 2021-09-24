#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void LUDecomposition(double **arr, int n)
{
    int i, j, k;
    double s;
    for (k = 0; k < n; k++) {
        for (j = k; j < n; j++) { // calculate U array
            s = arr[k][j];
            for (i = 0; i < k; i++) {
                s -= arr[k][i] * arr[i][j];
            }
            arr[k][j] = s;
        }
        for (i = k + 1; i < n; i++) { // calculate L array
            s = arr[i][k];
            for (j = 0; j < k; j++) {
                s -= arr[i][j] * arr[j][k];
            }
            arr[i][k] = s / arr[k][k];
        }
    }
}


#define ARRSIZE 4
int main()
{
    double **arr = (double **)malloc(sizeof(double *) * ARRSIZE);
    for (int i = 0; i < ARRSIZE; i++) {
        arr[i] = (double *)malloc(sizeof(double) * ARRSIZE);
    }
    arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3; arr[0][3] = 4;
    arr[1][0] = 1; arr[1][1] = 4; arr[1][2] = 9; arr[1][3] = 16;
    arr[2][0] = 1; arr[2][1] = 8; arr[2][2] = 27; arr[2][3] = 64;
    arr[3][0] = 1; arr[3][1] = 16; arr[3][2] = 81; arr[3][3] = 256;
    LUDecomposition(arr, ARRSIZE);
    for (int i = 0; i < ARRSIZE; i++) {
        for (int j = 0; j < ARRSIZE; j++) {
            printf("%f\t", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}