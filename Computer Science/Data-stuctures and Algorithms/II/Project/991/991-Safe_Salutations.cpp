/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar la cantidad de particiones de dos elementos sin cruzar de 2N elementos. Es un problema bien sabido que el N-esimo numero de catalan cuenta esto,
puesto que si enumeramos del 1 al 2N los elementos y hacemos una biyección entre estos y la cantidad de parantesis balanceados donde cada paratensis con su correspondiente
indican que hay una linea entre estos dos elementos.

Complejidad

O(N*N+T). Donde T es el numero de casos, y N la cantidad de parejas.
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

    int catalan[11];
    
    catalan[0] = catalan[1] = 1;
    for(int i = 2; i <= 10; i++)
        for(int j = 0; j < i; j++)
            catalan[i] += catalan[j]*catalan[i-j-1];
    
    int first = 0;
    while(cin >> N)
        f_out << (first++ ? "\n" : "" ) << catalan[N] << "\n\n";

    return 0;
}