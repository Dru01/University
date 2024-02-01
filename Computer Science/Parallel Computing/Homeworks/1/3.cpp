#include <stdio.h>
#include <iostream>
//OpenMP
#include <omp.h>
#include <math.h>

#define ll long long

int main()
{
    ll N = (ll)1e1, M = (ll)1e6;

    long double* v = new long double[N];
    long double* v_1 = new long double[N - 1];

    //Forma secuencial

    for (int i = 0; i < N; i++)
        v[i] = (long double)i / exp(1);

    for (int i = 0; i < N - 1; i++)
        v_1[i] = v[i] + v[i + 1];

    printf("El vector s_1 de v es: ");
    for (int i = 0; i < N - 1; i++)
        printf("%f ", v_1[i]);
    printf("\n");

    for (int i = 1; i < N - 1; i++)
        v_1[i] = (v[i + 1] + v[i - 1]) / 2;

    printf("El vector s_2 de v es: ");
    for (int i = 1; i < N - 1; i++)
        printf("%f ", v_1[i]);
    printf("\n");

    //Forma secuencial

    int i;

#pragma omp for private(i)
    for (i = 0; i < N; i++)
        v[i] = (long double)i / exp(1);

#pragma omp for private(i)
    for (int i = 0; i < N - 1; i++)
        v_1[i] = v[i] + v[i + 1];

    printf("El vector s_1 de v es: ");
#pragma omp for private(i)
    for (i = 0; i < N - 1; i++)
        printf("%f ", v_1[i]);
    printf("\n");

#pragma omp for private(i)
    for (i = 1; i < N - 1; i++)
        v_1[i] = (v[i + 1] + v[i - 1]) / 2;

    printf("El vector s_2 de v es: ");
#pragma omp for private(i)
    for (i = 1; i < N - 1; i++)
        printf("%f ", v_1[i]);
    printf("\n");

    delete[] v;

    return 0;
}