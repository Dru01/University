/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar la cantidad de números X para un N, tales que X/sqrt(N-X) es un entero positivo.

Para que eso se cumpla entonces N-X = i*i para algún entero i, de donde obtenemos X = N-i*i y que X%i=0. E i a lo mas sqrt(N)

Complejidad

O(T*(sqrt(N))). Donde T es la cantidad de casos, y N el número ortogado.
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

int main()
{
    optimizar_io;

    int x;
    
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        cin >> N;
        cout << "Case " << t << ": ";
        for (int i = sqrt(N) - 1; i >= 1; i--)
        {
            x = N - i * i;
            if (x % i == 0)
                cout << x << " ";
        }
        cout << "\n";
    }

    return 0;
}