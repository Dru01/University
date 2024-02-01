/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar la cantidad de formas de expresar N como la suma de K disntintos primos.

Primero encontramos con una criba la cantidad de primos menores o iguales a LN (el limite de N). Ahora encontramos la respuesta con una DP[][], donde DP[N][K] es la cantidad
de formas de expresar N como la suma de K distintos primos. Ahora es claro que las transiciones es iterar sobre todos los primos p menores a N y suma DP[N-p][k-1], pero debemos
debemos tener cuidado puesto que esto podría contar formas en las que un primo se use mas de una vez si iteramos primero sobre los primos p de mayor a menor nos quitariamos
esta molestia. El caso base es cuando N y K son 0.

Complejidad

O(N*K). Donde N es la suma, y K la cantidad de primos.
*/
#include <iostream>
#include <map>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>
using namespace std;

#define FILE_STREAM
#define ll long long
#define left(x) (x << 1 | 1)
#define right(x) (left(x) + 1)
#define half (l + r) / 2
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define out_range_map(x,y) ((x) < 0 || (y) < 0 || (x) == N || (y) == M)
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#ifdef FILE_STREAM
streambuf* cin_backup = cin.rdbuf(), * cout_backup = cout.rdbuf();
ifstream f_in("shortcut.in");
ofstream f_out("shortcut.out");
#endif // FILE_STREAM

const ll LN = (int)(1120 + 1), LK = (int)(14 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll dp[LN][LK];
bool is_prime[LN];
vector < int > prime;

void sieve_eratosthenes(int N)
{
    is_prime[0] = is_prime[1] = false;
    fill(is_prime, 1);
    for (int p = 2; p <= N; p++) {
        if (is_prime[p])
        {
            for (int num = p * p; num <= N; num += p)
                is_prime[num] = false;
            prime.push_back(p);
        }
    }
}

int main()
{
    optimizar_io;

    sieve_eratosthenes(LN-1);

    dp[0][0] = 1;

    for (auto p : prime)
        for (int i = LN-1; i >= p; i--)
            for (int j = LK-1; j; j--)
                dp[i][j] += dp[i - p][j - 1];

    cin >> N >> K;

    while (N != 0 || K != 0)
    {
        cout << dp[N][K] << "\n";
        cin >> N >> K;
    }

    return 0;
}