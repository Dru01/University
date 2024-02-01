#include <stdio.h>
#include <stdlib.h> 
#include <omp.h>
#include <math.h>
#include <time.h>

#define ll long long

int main()
{
    ll N = (ll)1e1, M = (ll)1e1;

    long double* A = (long double* )malloc(N*M*sizeof(long double)), *B = (long double* )malloc(N*M*sizeof(long double)), *C = (long double* )malloc(N*M*sizeof(long double));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            A[i*M+j] = 1.0;
            B[i*M+j] = i * M + j;
            C[i*M+j] = 0.0;
        }
    }

    clock_t t;
    t = clock();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            C[i*M+j] = A[i*M+j] + B[(N - 1 - i)*M+(M - 1 - j)];

    t = clock() - t;
    
    printf("%f", ((double)t)/CLOCKS_PER_SEC);

    return 0;
}