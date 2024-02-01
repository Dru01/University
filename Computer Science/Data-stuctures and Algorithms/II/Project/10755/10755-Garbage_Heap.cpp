/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide la suma maxima de todos los subparalepipedos de un paralepipedo.

Para ellos sabemos que podemos hacer sumas parciales (por el principio de inclusion-exclusion) para poder obtener en tiempo O(1) de un paralepipedo.
Ahora iterando sobre todos estos encontramos el maximo.

Complejidad:

O(T*N*M*K). Donde T es la cantidad de casos, y N, M, K las dimensiones del paralepipedo.
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>
using namespace std;

#define FILE_STREAM
#define ll long long
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define out_range_map(x,y) ((x) < 0 || (y) < 0 || (x) == N || (y) == M)
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#ifdef FILE_STREAM
streambuf* cin_backup = cin.rdbuf(), * cout_backup = cout.rdbuf();
ifstream f_in("shortcut.in");
ofstream f_out("shortcut.out");
#endif // FILE_STREAM

const ll LN = (int)(20 + 1), LK = (int)(5e3 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll parallelepiped[LN][LN][LN];
ll partial_sum[LN][LN][LN];
ll memo[LN][LN][LN][LN][LN][LN];

ll sum_sub_parallelepiped(int il, int ir, int jl, int jr, int kl, int kr)
{
    return partial_sum[ir][jr][kr] - partial_sum[il - 1][jr][kr] - partial_sum[ir][jl - 1][kr] - partial_sum[ir][jr][kl - 1] + partial_sum[il - 1][jl - 1][kr] + partial_sum[il - 1][jr][kl - 1] + partial_sum[ir][jl - 1][kl - 1] - partial_sum[il - 1][jl - 1][kl - 1];
}

int main()
{
    optimizar_io;

    cin >> T;

    while (T--)
    {
        cin >> N >> M >> K;

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= M; j++)
            {
                for (int k = 1; k <= K; k++)
                {
                    cin >> parallelepiped[i][j][k];
                    partial_sum[i][j][k] = 0;
                    partial_sum[i][j][k] = -sum_sub_parallelepiped(i, i, j, j, k, k) + parallelepiped[i][j][k];
                }
            }
        }

        ll ans = parallelepiped[1][1][1];

        for (int il = 1; il <= N; il++)
            for (int ir = il; ir <= N; ir++)
                for (int jl = 1; jl <= M; jl++)
                    for (int jr = jl; jr <= M; jr++)
                        for (int kl = 1; kl <= K; kl++)
                            for (int kr = kl; kr <= K; kr++)
                                ans = max(ans, sum_sub_parallelepiped(il, ir, jl, jr, kl, kr));


        cout << ans << "\n" << (T ? "\n" : "");
    }

    return 0;
}