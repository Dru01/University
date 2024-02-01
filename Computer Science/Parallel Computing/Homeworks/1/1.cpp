#include <stdio.h>
#include <iostream>
//OpenMP
#include <omp.h>
#include <math.h>

#define ll long long

int main()
{
    ll N = (ll)1e6;

    long double* v = new long double[N];

    long double sum = 0.0;

    int nthreads = 4, i;

    //Forma paralela
#pragma omp parallel num_threads(nthreads) reduction(+:sum)
    {
#pragma omp for private(i)
        for (i = 0; i < N; i++)
            v[i] = (long double)i / exp(1);
#pragma omp for private(i)
        for (i = 0; i < N; i++)
            sum += v[i];
    }

    printf("La suma del vector es: %f (paralelo)\n", sum);

    //Forma secuencial

    sum = 0.0;

    for (int i = 0; i < N; i++)
        v[i] = (long double)i / exp(1);

    for (int i = 0; i < N; i++)
        sum += v[i];

    printf("La suma del vector es: %f (secuencial)\n", sum);

    delete[] v;

    return 0;
}