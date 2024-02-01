/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema nos pide encontrar el promedio (esperanza) de intercambios que realiza un bubble sort para arreglo de tamaño N.

Primero notemos notemos que la probabilidad de intercambiar una pareja de numeros o no intercambiarlas es lo mismo por lo que la esperanza de intercambiarlos es 1/2. Ahora el número total de parejas es Combinaciones(N,2) = N(N-1)/2. Por lo tanto la esperanza de intercambios que realiza un bubble sort para una arreglo de tamaño N es N(N-1)/4.

Complejidad

O(T). Donde T es la cantidad de casos.
*/
#include <iostream>
#include <map>
#include <set>
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

const ll LN = (int)(26 + 1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
ll N, M, K, T;

int main()
{
    optimizar_io;

    cin >> T;
    
    for(int t = 0; t < T; t++)
    {
        cin >> N;

        ll ans = (N) * (N - 1) / 2;

        cout << "Case " << t + 1 << ": " << ans / (!(ans % 2) + 1) << (ans % 2 ? "/2" : "") << "\n";
    }
}