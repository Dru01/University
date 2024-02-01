/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar el k-esimo entero de una cadena generada por la concatenacion de una secuencia b_n, que a su vez es la consiste de nd concatenaciones del antero a_n. Nos dan el valor de los a_n en forma de un polinomio.

Podemos darnos cuenta que la cantidad de enteros hasta b_n esta dado por la cantidad de enteros hasta b_{n-1} mas n*d, por lo que si recorremos sobre n desde 1 hasta encontrar el primer n tal que la cantidad de enteros hasta b_n sea mayor o igual a k, entonces la respuesta sería a_n puesto que los últimos n*d enteros son este. Ahora para calcular el valor de a_n basta con evaluar cada uno de los c[i]*n**i de menor a mayor.

Complejidad

O(T*sqrt(k)). Donde T es la cantidad de casos, y k el entero deseado.
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
int N, M, K, T;

int main()
{
    optimizar_io;

    cin >> T;

    while (T--)
    {
        cin >> M;
        vector < int > coefficient(M);
        for(auto & c : coefficient)
            cin >> c;
        
        cin >> K >> N;

        int tl = 0, tr = 0, n = 0;
        while(tr < N)
        {
            tl = tr;
            tr += n * K;
            n++;
        }
        ll ans = 0, n_pow_i = 1;
        for (auto &c : coefficient)
        {
            ans += c * n_pow_i;
            n_pow_i *= n;
        }
        cout << ans << "\n";
    }
}