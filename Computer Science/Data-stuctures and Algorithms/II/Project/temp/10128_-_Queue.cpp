/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide cálcular la cantidad de permutaciones de las N personas tal que las personas que se puedan ver de izquierda a dercha sean P y de dercha a izquierda R. Donde las personas son aquellas tales que su altura es mayor al de todas las anteriores.

Para ello usaremos una DP[N][P][R] que representa justo el estado que nos pide el problema (N personas, P izquierda-derecha, R derecha-izquierda), donde la recursión fijandonos en la persona mas chica podemos ver que solo se vera si esta esta al inicio o al final de la cola, por lo que tendriamos la recursion DP[N][P][R] = DP[N - 1][P][R] * (N - 2) + DP[N - 1][P - 1][R] + DP[N - 1][P][R - 1].

Complejidad

O(T*N**3). Donde T es la cantidad de casos, y N la cantidad de personas.
*/
#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <numeric>
#include <climits>
#include <iomanip>
using namespace std;

#define FILE_STREAM
#define ll long long
#define left(x) (x << 1 | 1)
#define right(x) (left(x) + 1)
#define half (l + i) / 2
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define out_range_map(x,y) ((x) < 0 || (y) < 0 || (x) == N || (y) == M)
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#ifdef FILE_STREAM
streambuf* cin_backup = cin.rdbuf(), * cout_backup = cout.rdbuf();
ifstream f_in("shortcut.in");
ofstream f_out("shortcut.out");
#endif // FILE_STREAM

const ll LN = (ll)(2e2+1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll memo[17][17][17];

ll dp(int N, int P, int R)
{
    if (N == 1 && P == 1 && R == 1)
        return 1;
    if (N < 2 || !P || !R)
        return 0;
    if (memo[N][P][R] != -1)
        return memo[N][P][R];
    return memo[N][P][R] = dp(N - 1,P,R) * (N - 2) + dp(N - 1,P - 1,R) + dp(N - 1,P,R - 1);
}

int main()
{
    optimizar_io;

    int P, R;
    
    fill(memo, -1);
    
    cin >> T;
    while (T--)
    {
        cin >> N >> P >> R;
        cout << dp(N,P,R) << "\n";
    }

    return 0;
}