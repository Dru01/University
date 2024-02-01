/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar la cantidad de configuraciones de los cajones (abiertos/cerrados) tal que la cantidad de cajones completamente bloqueados sean K,
de un mueble con N cajones acomadados verticalmente uno tras de otro. Un cajon completamente bloqueado es aquel que es el primero o que tiene un cajon bloqueado por encima.

Para responder esta pregunta usaremos una DP[][][], donde DP[N][K][l] es la cantidad de configuraciones de los cajones (abiertos/cerrados) tal que la cantidad de cajones 
completamente bloqueados sean K, de un mueble con N cajones acomadados verticalmente uno tras de otro, tal que el anterior es abierto si l=0 o cerrado si l = 1 (l:locked).
Los casos base son cuando N y K son cero entonces hay una configuración que cumple esta restriccion. Las transiciones es abrir o cerrar el cajon actual (estas pueden estar
prohibidad en caso de que K ya sea cero), y el cambio en K depende de l y la accion que hagamos.

Complejidad:

O(T*N**2). Donde T es la cantidad de casos, N la cantidad de cajones del mueble.
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

const ll LN = (int)(100+1), LK = (int)(5e3 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll memo[LN][LN][2];

ll dp(int N, int K, bool l)
{
    if (!N)
        return K == 0;
    if (memo[N][K][l] != -1)
        return memo[N][K][l];
    ll ans = 0;
    if (K)
    {
        if (l)
            ans += dp(N - 1, K - 1, 1);
        else
            ans += dp(N - 1, K, 1);
        ans += dp(N - 1, K, 0);
    }
    else
    {
        if (!l)
            ans += dp(N - 1, K, 1);
        ans += dp(N - 1, K, 0);
    }
    return memo[N][K][l] = ans;
}

int main()
{
    optimizar_io;

    cin >> N >> K;

    fill(memo, -1);

    while (N >= 0 && K >= 0)
    {
        cout << dp(N, K, 1) << "\n";
        cin >> N >> K;
    }

    return 0;
}