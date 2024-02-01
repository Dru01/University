/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide cálcular la minima cantidad de pasos para que el conjunto de numeros del 1 al N se vuelvan 0. En un paso puedes escoger cualquier cantidad de numeros y restarles a todos una misma cantidad.

Podemos ver que si tenemos una cadena reptida varias veces si hacemos llegar a 0 una, el resto en esos mismos pasos lo harán por lo que ir dividiendo por mitades y restarle el inicio de la mitad mas grande a la grande mantendremos simpre 2^i cadenas iguales en el paso i. Por lo que la cantidad de pasos es log(N).

Complejidad

O(T*(log(N)). Donde T es la cantidad de casos, y N la cantidad de números (claro se puede quitar esto memorizando o usando la función log, pero no es de interes en el problema).
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

const ll LN = (ll)(250000000), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
int dp[LN];

int main()
{
    optimizar_io;

    while (cin >> N)
    {
        int ans = 0;
        while(N)
        {
            N/=2;
            ans++;
        }
        cout << ans << "\n";
    }

    return 0;
}