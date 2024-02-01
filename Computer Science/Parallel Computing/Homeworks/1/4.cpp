#include <stdio.h>
#include <iostream>
//OpenMP
#include <omp.h>
#include <math.h>

#define ll long long

int main()
{
    ll N = (ll)1e1, M = (ll)1e1;

    long double alpha = 1 / exp(1);

    //Forma secuencial

    long double** A = new long double* [N], ** B = new long double* [N], ** C = new long double* [N];

    for (int i = 0; i < N; i++)
    {
        A[i] = new long double[M], B[i] = new long double[M], C[i] = new long double[M];
        for (int j = 0; j < M; j++)
        {
            A[i][j] = 1.0;
            B[i][j] = i * M + j;
            C[i][j] = 0.0;
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            C[i][j] = A[i][j] + B[N - 1 - i][M - 1 - j];

    printf("La matriz C_1 es:\n");
    for (int i = 0; i < N; i++, printf("\n"))
        for (int j = 0; j < M; j++)
            printf("%f ", C[i][j]);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            C[i][j] = (alpha)*A[i][j] + (1 - alpha) * B[N - 1 - i][M - 1 - j];

    printf("La matriz C_2 es:\n");
    for (int i = 0; i < N; i++, printf("\n"))
        for (int j = 0; j < M; j++)
            printf("%f ", C[i][j]);

    for (int i = 0; i < N; i++)
        delete[] A[i], delete[] B[i], delete[] C[i];
    delete[] A, delete[] B, delete C;

    //Forma paralela

    int nthreads = 4;

    omp_set_nested(1);
    omp_set_num_threads(nthreads);

    A = new long double* [N], B = new long double* [N], C = new long double* [N];
    int i, j, k;
#pragma omp parallel private(i,j)
    {
#pragma omp parallel for
        for (i = 0; i < N; i++)
        {
            A[i] = new long double[M], B[i] = new long double[M], C[i] = new long double[M];
#pragma omp parallel for
            for (j = 0; j < M; j++)
            {
                A[i][j] = 1.0;
                B[i][j] = i * M + j;
                C[i][j] = 0.0;
            }
        }
    }

#pragma omp for collapse(2) private(i, j)
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            C[i][j] = A[i][j] + B[N - 1 - i][M - 1 - j];

    printf("La matriz C_1 es:\n");
#pragma omp for collapse(2) private(i, j)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%f ", C[i][j]);
            if(j == M-1)
                printf("\n");

        }
    }

#pragma omp for collapse(2) private(i, j)
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            C[i][j] = (alpha)*A[i][j] + (1 - alpha) * B[N - 1 - i][M - 1 - j];

    printf("La matriz C_2 es:\n");
#pragma omp for collapse(2) private(i, j)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            printf("%f ", C[i][j]);
            if(j == M-1)
                printf("\n");

        }
    }

#pragma omp parallel for private(i)
    for (i = 0; i < N; i++)
        delete[] A[i], delete[] B[i], delete[] C[i];
    delete[] A, delete[] B, delete[] C;

    return 0;
}