/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar cual es el numero N mas grande tal que N! puede ser representado por una computadora de 2^K bits (El K esta disfrazado). Puesto que la cantidad de
bits necesarios para representar N! son log2(N!) y que log2(xy) = log2(x) + log2(y). Entonces log2(N!) = sum log2(i) (con i entre 1 y N), entonces iterando sobre los i hasta
que nos acabemos los bits disponibles encontraremos a N

Complejidad

O(N*log(N)).
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

int main()
{
    optimizar_io;

    while (cin >> N && N) {
        N = 1 << ((N - 1960) / 10 + 2);
        int i;
        for (i = 1; N; i++)
            N -= log2(i);
        cout << i - 2 << "\n";
    }

    return 0;
}