#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void LUDecomposition(double *arr, int n, int *idxSwap)
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
        idxSwap[k] = maxIdx;
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

void inverseLU(double *arr, int n, int *idxSwap, double *ret)
{
    double s;
    int i, j, p;
    int ii = -1;
    for (i = 0; i < n; i++) { // calculate L^-1
        p = idxSwap[i];
        s = ret[p];
        ret[p] = ret[i];
        if (ii >= 0) {
            for (j = ii; j < i; j++) {
                s -= arr[i + j * n] * ret[j];
            }
        } else if (s) {
            ii = i;
        }
        ret[i] = s;
    }
    for (i = n - 1; i >= 0; i--) {
        s = ret[i];
        for (j = i + 1; j < n; j++) {
            s -= arr[i + j * n] * ret[j];
        }
        ret[i] = s / arr[i + i * n];
    }
}

void MultiplyMatrix(double *A, int n, int k, double *B, int m, double *C)
{
    int i, j, h;
    double tmp;
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++) {
            tmp = 0.0;
            for (h = 0; h < m; h++) {
                tmp += A[i + h * n] * B[h + j * n];
            }
            C[i + j * n] = tmp;
        }
    }
}

#define ARRSIZE 3
int main()
{
    double *A = (double *)malloc(sizeof(double) * ARRSIZE * ARRSIZE);
    double *arr = (double *)malloc(sizeof(double) * ARRSIZE * ARRSIZE);
    // arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3; 
    // arr[1][0] = 3; arr[1][1] = 1; arr[1][2] = 5; 
    // arr[2][0] = 2; arr[2][1] = 5; arr[2][2] = 2; 

    arr[0] = 1; arr[3] = 2; arr[6] = 3;
    arr[1] = 3; arr[4] = 1; arr[7] = 5;
    arr[2] = 2; arr[5] = 5; arr[8] = 2;
    memcpy(A, arr, sizeof(double) * ARRSIZE * ARRSIZE);
    int *idxSwap = (int *)malloc(sizeof(int) * ARRSIZE);
    LUDecomposition(arr, ARRSIZE, idxSwap);
    for (int i = 0; i < ARRSIZE; i++) {
        for (int j = 0; j < ARRSIZE; j++) {
            printf("%f\t", arr[i + j * ARRSIZE]);
        }
        printf("\n");
    }
    double *inverse = (double *)malloc(sizeof(double) * ARRSIZE * ARRSIZE);
    memset(inverse, 0.0, sizeof(double) * ARRSIZE * ARRSIZE);
    for (int i = 0; i < ARRSIZE; i++) {
        inverse[i + i * ARRSIZE] = 1;
        inverseLU(arr, ARRSIZE, idxSwap, (inverse + i * ARRSIZE));
    }
    MultiplyMatrix(A, ARRSIZE, ARRSIZE, inverse, ARRSIZE, arr);
    printf("\n");
    for (int i = 0; i < ARRSIZE; i++) {
        for (int j = 0; j < ARRSIZE; j++) {
            printf("%f\t", arr[i + j * ARRSIZE]);
        }
        printf("\n");
    }

    return 0;
}