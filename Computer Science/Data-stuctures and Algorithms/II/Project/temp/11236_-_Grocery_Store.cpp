/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide cálcular la cantidad de numeros reales menores a 20, con dos decimales tales que su suma es igual a su producto. Por lo que basta con iterar sobre todas las ternas que cumplan las restricciones y calcular si el 4 número que cumple que su suma es igual a su producto también cumple que sea menor a 20 y con dos decimales. Para evitar dividir los números, basta con expresarlo como números enteros (con 4 posiciones) y revisar con modulos que se cumplan las respectivas divisibilidades.

Complejidad

O(T*(N**3)). Donde T es la cantidad de casos, y N la cantidad de valores diferentes que pueden adquirir cada número.
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

int main()
{
    optimizar_io;

    ll d, product, sum;
    cout << fixed;
    cout << setprecision(2);
    for (ll a = 0; 4 * a <= 2000; a++)
    {
        for (ll b = a; a + 3 * b <= 2000; b++)
        {
            for (ll c = b; a + b + 2 * c <= 2000; c++)
            {
                product = (ll)a * b * c;
                if (product <= 1000000)
                    continue;
                sum = (a + b + c);
                if (sum * 1000000 % (product - 1000000))
                    continue;
                d = sum * 1000000 / (product - 1000000);
                if (a + b + c + d > 2000 || d < c)
                    continue;
                cout << (double)a/100 << " " << (double)b / 100 << " " << (double)c / 100 << " " << (double)d / 100 << "\n";
            }
        }
    }

    return 0;
}