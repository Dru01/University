#include <stdio.h>
#include <iostream>
//OpenMP
#include <omp.h>
#include <math.h>

#define ll long long

int main()
{
    ll N = (ll)1e1, M = (ll)1e6;

    //Forma secuencial

    long double** A = new long double* [N], ** B = new long double* [N], ** C = new long double* [N];

    for (int i = 0; i < N; i++)
    {
        A[i] = new long double[N], B[i] = new long double[N], C[i] = new long double[N];
        for (int j = 0; j < N; j++)
        {
            A[i][j] = (long double)(i + 1);
            B[i][j] = (i == j ? 1.0 : 0.0);
            C[i][j] = 0.0;
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];

    printf("La matriz A*B es:\n");
    for (int i = 0; i < N; i++, printf("\n"))
        for (int j = 0; j < N; j++)
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
            A[i] = new long double[N], B[i] = new long double[N], C[i] = new long double[N];
#pragma omp parallel for
            for (j = 0; j < N; j++)
            {
                A[i][j] = (long double)(i + 1);
                B[i][j] = (i == j ? 1.0 : 0.0);
                C[i][j] = 0.0;
            }
        }
    }

#pragma omp for collapse(3) private(i, k, j)
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];

    printf("La matriz A*B es:\n");
#pragma omp for collapse(2) private(i, j)
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%f ", C[i][j]);
            if (j == N-1)
                printf("\n");
        }
    }

#pragma omp parallel for private(i)
    for (i = 0; i < N; i++)
        delete[] A[i], delete[] B[i], delete[] C[i];
    delete[] A, delete[] B, delete[] C;

    return 0;
}