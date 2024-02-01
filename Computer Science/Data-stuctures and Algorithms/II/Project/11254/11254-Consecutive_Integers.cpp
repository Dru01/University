/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema nos pide encontrar un conjunto de numeros consecutivos tales que su suma sea N y sea el de tamaño mas grande. Para ello basta con ver que la suma entre los numeros
tl y tl + tsize es (tsize + 1) * (2 * tl + tsize)/2 = N, por lo que tzise esta acotado por sqrt(2 * N), por lo que podemos recorrer todos los tamaños de mayor a menor (empezando por sqrt(2*N)) y checar si alguno funciona (notese que la misma formula nos da un tl para cada tsize)

Complejidad

O(T*sqrt(N)). Donde T es el numero de casos y N la suma deseada.
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

int main()
{
    optimizar_io;

    int tl, cl, tsize;
    while (cin >> N && N > 0) {
        
        tl = N, tsize = 0;
        
        for (int csize = sqrt(2 * N); csize > 0; csize--)
        {
            cl = (2 * N - csize - csize * csize) / (2 * (csize + 1));
            
            if ((csize + 1) * (2 * cl + csize) == 2 * N)
            {
                tl = cl;
                tsize = csize;
                break;
            }
        }

        if (tl == 0)
        {
            tl = 1;
            tsize--;
        }

        cout << N << " = " << tl << " + ... + " << tl + tsize << "\n";
    }

    return 0;
}