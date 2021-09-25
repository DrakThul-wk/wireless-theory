#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void LUDecomposition(double *arr, int n)
{
    int i, j, k, maxIdx;
    double big, s;
    for (k = 0; k < n; k++) {
        big = 0.0;
        for (i = k; i < n; i++) { // find s and ready to swap row
            s = arr[i + k * n];
            for (j = 0; j < k; j++) {
                s -= arr[i + j * n] * arr[j + k * n];
            }
            if (fabs(s) > big) {
                big = fabs(s);
                maxIdx = i;
            }
        }
        if (k != maxIdx) { // swap
            for (j = 0; j < n; j++) {
                double tmp = arr[maxIdx + j * n];
                arr[maxIdx + j * n] = arr[k + j * n];
                arr[k + j * n] = tmp;
            }
        }
        for (j = k; j < n; j++) { // calculate U value
            s = arr[k + j * n];
            for (i = 0; i < k; i++) {
                s -=arr[k + i * n] * arr[i + j * n];
            }
            arr[k + j * n] = s;
        }
        for (i = k + 1; i < n; i++) { // calculate L value
            s = arr[i + k * n];
            for (j = 0; j < k; j++) {
                s -= arr[i + j * n] * arr[j + k * n];
            }
            arr[i + k * n] = s / arr[k + k * n];
        }
    }
}


#define ARRSIZE 3
int main()
{
    double *arr = (double *)malloc(sizeof(double) * ARRSIZE * ARRSIZE);
    // arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3; 
    // arr[1][0] = 3; arr[1][1] = 1; arr[1][2] = 5; 
    // arr[2][0] = 2; arr[2][1] = 5; arr[2][2] = 2; 

    arr[0] = 1; arr[3] = 2; arr[6] = 3;
    arr[1] = 3; arr[4] = 1; arr[7] = 5;
    arr[2] = 2; arr[5] = 5; arr[8] = 2;

    LUDecomposition(arr, ARRSIZE);
    for (int i = 0; i < ARRSIZE; i++) {
        for (int j = 0; j < ARRSIZE; j++) {
            printf("%f\t", arr[i + j * ARRSIZE]);
        }
        printf("\n");
    }
    return 0;
}