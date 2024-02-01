/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema nos pide convertir entre dos representaciones de un bitmap a la otra. Por definición la primera es recursiva, y la segunda es la matricial.

Para convertir de la recursiva a la matricial solo basta con una dfs recurrer esta representación y llenarla cuando nos encontremos en un estado completo (1 o 0). En el caso contrario hay que ir diviendo nuestra matriz en 4 cuadrantes y checar si alguno de ellos es completo si no con una dfs ir a cada uno de ellos. La solución es muy directa, pero hay que tener cuidado con el formato de entrada y de salida que te pide el problema.

Complejidad

O(T*(N**2)). Donde T es la cantidad de casos, y N la dimensión del tablero.
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
int N, M, K, T, pos;
string word;
int board[LN][LN];

void BtoD(int li, int ri, int lj, int rj)
{
    if (li == ri || lj == rj)
        return;

    int zeros = 0;
    for (int i = li; i < ri; ++i)
        for(int j = lj; j < rj; j++)
            zeros += board[i][j] == 0;

    if (pos > 0 && pos % 50 == 0)
        cout << endl;
    ++pos;
    if (zeros == (ri - li) * (rj - lj))
        cout << "0";
    else if (zeros == 0)
        cout << "1";
    else
    {
        cout << "D";
        int hi = (li + ri + 1) / 2;
        int hj = (lj + rj + 1) / 2;
        BtoD(li, hi, lj, hj);
        BtoD(li, hi, hj, rj);
        BtoD(hi, ri, lj, hj);
        BtoD(hi, ri, hj, rj);
    }
}

void DtoB(int li, int ri, int lj, int rj)
{
    if (li == ri || lj == rj)
        return;

    char w = cin.get();
    if (w == '0' || w == '1')
    {
        for (int i = li; i < ri; ++i)
            for (int j = lj; j < rj; ++j)
                board[i][j] = w - '0';
        return;
    }

    int hi = (li + ri + 1) / 2;
    int hj = (lj + rj + 1) / 2;
    DtoB(li, hi, lj, hj);
    DtoB(li, hi, hj, rj);
    DtoB(hi, ri, lj, hj);
    DtoB(hi, ri, hj, rj);
}

int main()
{
    optimizar_io;

    char type;
    while (cin >> type, type != '#')
    {
        cin >> N >> M;
        cin.ignore();

        cout << (type == 'B' ? "D" : "B") << right << setw(4) << N << right << setw(4) << M << "\n";

        pos = 0;
        if (type == 'B')
        {
            word = "";
            while (word.size() < N * M)
            {
                string tmp;
                getline(cin, tmp);
                word = word + tmp;
            }
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    board[i][j] = word[i * M + j] - '0';
            
            BtoD(0, N, 0, M);
        }
        else
        {
            DtoB(0, N, 0, M);
            
            for (int i = 0; i < N; ++i)
            {
                for (int j = 0; j < M; ++j)
                {
                    if (i + j > 0 && (i * M + j) % 50 == 0)
                        cout << "\n";
                    cout << board[i][j];
                }
            }
        }
        cout << "\n";
    }

    return 0;
}