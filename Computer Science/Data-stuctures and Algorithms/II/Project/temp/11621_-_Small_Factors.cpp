/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide cálcular el mayor número entero M menor o igual a N tal que M = 2^i*3^j para algún i,j enteros.

Basta con calcular todos los posibles números M y luego hacer una busqueda binaria sobre ellos para encontrar el mayor número de ellos menor que N.

Complejidad

O(T*(log(N)^2). Donde T es la cantidad de casos, y N el dato mas grande.
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

    ll ans;
    vector < ll > bucket;
    double p;
    
    for (int i = 0, exp2 = 1; i < 32; i++, exp2 *= 2)
        for (int j = 0, exp3 = 1; j < 32; j++, exp3 *= 3)
            if (exp2*exp3 <= 1LL << 50)
                bucket.push_back(exp2*exp3);

    sort(all(bucket));

    while (cin >> N, N)
        cout << *lower_bound(bucket.begin(), bucket.end(), N) << "\n";

    return 0;
}