/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar la cantidad de cadenas S (con solo letras minusculas) de tamaño N cuyos caracteres esten 
en orden creciente y la suma de Ascii[S[i]]-Ascii['a'] sea K.

Primero notemos que al ser cadenas con solo letras minusculas y con caracteres en orden creciente, entonces el tamaño de estas esta acotado por 26. Por la misma razon
la suma maxima esta acotada por 351. Ahora pedemos encontrar la respuesta con una DP[][][], donde DP[i][j][k] es la cantidad de cadenas con caracteres en orden creciente
de tamaño j, con suma K, y último caracter i. El caso base es cuando el tamaño, la suma y el último caracter es 0, cuyo valor es 1. Las transiciones es recorrer todas las
opciones teniendo cuidado que sea posible usar un caracter i, porque este puede exceder la suma.

Complejidad

O(LN**2 * LK). Donde LN es el tamaño maximo de las cadenas, y LK la suma maxima de las cadenas.
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

const ll LN = (int)(26+1), LK = (int)(351+1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll dp[LN][LN][LK], partial_sum[LN][LN][LK];

int main()
{
    optimizar_io;

    dp[0][0][0] = 1;

    for (int i = 1; i < LN; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            for (int k = 0; k < LK; k++)
            {
                dp[i][j][k] = dp[i-1][j][k];
                if (k >= i && j)
                    dp[i][j][k] += dp[i - 1][j - 1][k - i];
            }
        }
    }

    cin >> N >> K;

    while (N != 0 || K != 0)
    {
        cout << "Case " << ++T << ": " << (N <= 26 && K <= 351 ? dp[26][N][K] : 0) << "\n";
        cin >> N >> K;
    }

    return 0;
}