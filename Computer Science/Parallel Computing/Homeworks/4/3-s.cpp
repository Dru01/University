#include <stdio.h>
#include <stdlib.h> 
#include <omp.h>
#include <math.h>
#include <time.h>

#define ll long long

void mat_prod(double* A, double* B, double* C, int N, int K, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            C[i * M + j] = 0.0;
            for (int k = 0; k < K; k++)
                C[i * M + j] += A[i * K + k] * B[j * K + k];
        }
    }
}

int main(int argc, char* argv[])
{
    ll N = 1e4, K = 1e3, M = 1e3;

    double* A = (double*)malloc(N * K * sizeof(double)), * B = (double*)malloc(M * K * sizeof(double)), * C = (double*)malloc(N * M * sizeof(double));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++)
            A[i * K + j] = i * K + j;

    for (int i = 0; i < M; i++)
        for (int j = 0; j < K; j++)
            B[i * K + j] = i * K + j;

    clock_t t;
    t = clock();

    mat_prod(A, B, C, N, K, M);

    t = clock() - t;

    printf("%f", ((double)t) / CLOCKS_PER_SEC);

    return 0;
}