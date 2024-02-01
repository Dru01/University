/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide cálcular el modulo p % m entre dos enteros, todos los números expresados en base b.

Notemos que por las restricciones del problema podemos almacenar el valor de m en base 10 en un int. Luego recordemos que el moudlo preserva la suma por lo que si al convertir el numero p a base 10 podemos quedarnos con su modulo m en cada suma. Finalmente solo basta con convertir este último número de base 10 a base b.

Complejidad

O(T*(log(m)+log(p))). Donde T es la cantidad de casos, y m y p los enteros mencionados.
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

const ll LN = (int)(26 + 1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;

int main()
{
    optimizar_io;

    int b, p, m;
    string p_b, m_b;
    stack < int > ans;
    while (cin >> b, b)
    {

        cin >> p_b >> m_b;

        int exp_b = 1;
        m = 0;
        for (int i = m_b.size() - 1; i >= 0; i--)
        {
            m += (m_b[i] - '0') * exp_b;
            exp_b *= b;
        }

        p = 0;
        for (int i = 0; p_b[i]; i++)
        {
            p = p * b + p_b[i] - '0';
            p %= m;
        }

        while (p) {
            ans.push(p % b);
            p /= b;
        }

        if (ans.empty())
            cout << "0";
        while (!ans.empty())
        {
            cout << ans.top();
            ans.pop();
        }
        cout << "";
    }
    return 0;
}