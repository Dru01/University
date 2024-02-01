/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema una cadena de la forma (a+b)^k donde a y b son cadenas de caracteres que representan el nombre dos variables y k un entero. Nos pide desarrollar el producto usando el binomio de Newton.

Si conocemos de antemano los coeficientes de la expresion que resulta del binomio de Newton entonces solo basta con recorrer cada potencia e imprimir cada termino de la forma 
Comb(k,i)a^(k-1)b^i. Pero recordemos que podemos precalcular los coeficiente binomiales gracias a la recurrencia de pascal que estos tienen en O(N**2).

Complejidad

O(K**2 + T*K). Donde T es el numero de casos y K la potencia que nos dan.
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

const ll LN = (int)(5e4 + 1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
ll N, M, K, T;
ll bc[51][51];

int main()
{
    optimizar_io;

    bc[0][0] = 1;
    for (int i = 1; i <= 50; i++)
    {
        bc[i][0] = 1;
        for (int j = 1; j <= i; j++)
            bc[i][j] = bc[i - 1][j - 1] + bc[i - 1][j];
    }

    cin >> T;

    string word, a, b, c;
    int power;
    for (int t = 0; t < T; t++)
    {
        cin >> word;
        a = word.substr(1, word.find('+')-1);
        b = word.substr(word.find('+')+1, word.find(')')-word.find('+')-1);
        c = word.substr(word.find('^') + 1);
        power = stoi(word.substr(word.find('^')+1));

        cout << "Case " << t + 1 << ": ";

        for (int i = 0; i <= power; i++)
        {
            if (i)
                cout << "+";
            if (bc[power][i] != 1)
                cout << bc[power][i] << "*";
            if (i != power)
            {
                cout << a;
                if (i != power - 1)
                    cout << "^" << power - i;
                if (i)
                    cout << "*";
            }
            if (i)
            {
                cout << b;
                if (i != 1)
                    cout << "^" << i;
            }
        }
        cout << "\n";
    }
}