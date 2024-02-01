/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar la matriz (con entradas en las mayúsculas del Alfabeto) menor lexicograficamente (con orden izquierda-derecha, arriba-abajo), tal que no haya dos celdas adyacentes (con una arista en común) con la misma letra.

Entonces podemos ir construyendo de izquierda-derecha,arriba-abajo tal que en cada posición aseguremos que asignamos la letra mas chiquita tal que no haya una letra adyacente igual a esa. De esta forma estamos asegurando que es la menor lexicograficamente.

Complejidad

O(T*(N*N*C)). Donde T es la cantidad de casos, N dimension de la matriz y C la cantidad de letras.
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
string board[10];
const int dr[] = { -1,1,0,0 };
const int dc[] = { 0,0,-1,1 };

int main()
{
    optimizar_io;

    bool same;

    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        cin >> N;
        M = N;

        for (int i = 0; i < N; i++)
            cin >> board[i];

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] != '.')
                    continue;
                for (char c = 'A'; c <= 'Z'; c++)
                {
                    same = true;

                    for (int k = 0; k < 4; k++)
                    {
                        int ii = i + dr[k];
                        int jj = j + dc[k];

                        if (!out_range_map(ii,jj) && board[ii][jj] == c)
                            same = false;
                    }

                    if (same)
                    {
                        board[i][j] = c;
                        break;
                    }
                }
            }
        }

        cout << "Case " << t << ":\n";
        for (int i = 0; i < N; ++i)
            cout << board[i] << "\n";
    }

    return 0;
}