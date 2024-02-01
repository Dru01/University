#include <stdio.h>
#include <stdlib.h> 
#include <omp.h>
#include <math.h>
#include <time.h>

#define ll long long

int main()
{
    ll N = (ll)1e7;

    long double* v = (long double* )malloc(N*sizeof(long double));
    long double* v_1 = (long double* )malloc((N-1)*sizeof(long double));

    for (int i = 0; i < N; i++)
        v[i] = (long double)i / exp(1);

    clock_t t;
    t = clock();

    for (int i = 1; i < N - 1; i++)
        v_1[i] = (v[i + 1] + v[i - 1])/2;

    t = clock() - t;

    free(v);
    free(v_1);

    printf("%f", ((double)t)/CLOCKS_PER_SEC);

    return 0;
}