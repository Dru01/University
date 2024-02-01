/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema nos pide encontrar la k-esima fraccion irreducible con denominador menor o igual a N si estas estan ordenadas. Basta con recorrer todas las parejas de numeros (j, i)
donde j < i, y si estos son cooprimos entonces generan una fraccion irreducible, guardando todos estos y ordenandolos podemos encontrar el k-esimo elemento deseado.
Complejidad

O(N*N). Donde N es el denominador mas grande.
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

int gcd(int a, int b) {
    if (!a)
        return b;
    return gcd(b % a, a);
}

int main()
{
    optimizar_io;

    while (cin >> N >> K)
    {
        vector < pair < double, pair <int, int> > > fraction;
        fraction.push_back({ 1, {1,1 }});
        
        for (int i = 1; i <= N; i++)
            for (int j = 1; j < i; j++)
                if (gcd(j, i) == 1)
                    fraction.push_back({ (double)j / i, { j,i } });
        
        sort(all(fraction));
        cout << fraction[K - 1].second.first << '/' << fraction[K - 1].second.second << endl;
    }

    return 0;
}