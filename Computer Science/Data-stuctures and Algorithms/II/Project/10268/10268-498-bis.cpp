/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide evaluar la derivada de una función polinomial. La solucion es evaluar termino por termino de la suma de la funcion de la derivada, el unico problema es que el
calcular x^i en tiempo lineal es muy tardado por lo que hacemos uso de la exponenciasion binaria para reducir este tiempo.

Complejidad

O(T*N*log(N)). Donde T es el numero de casos, y N es el coeficiente del polinomio
*/
#include <iostream>
#include <sstream>
#include <fstream>
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

ll bin_pow(ll base, ll power) {
    if (power == 0)
        return 1;
    ll ans = bin_pow(base, power / 2);
    return (power % 2 ? base : 1) * ans * ans;
}

long long c[1000000];

int main()
{
    optimizar_io;

    long long x;
    string word;

    while (cin >> x)
    {
        getchar();
        getline(cin, word);
        stringstream parse;
        parse << word;
        N = 0;
        while (parse >> c[N])
            N++;
        
        ll ans = 0;
        for (int i = 0; i < N - 1; i++)
             ans += bin_pow(x, N - i - 2) * c[i] * (N - i - 1);
        
        cout << ans << "\n";
    }
    return 0;
}