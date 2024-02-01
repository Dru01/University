/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problemas nos da una serie de dimensiones de bolsas $bag$. Una bolsa se puede guardar dentro de otro si su tamaño es estrictamente menor que la otra. Nos pide calcular la minima cantidad de bolsas que queden sin guardar si guardamos una dentro de otra de manera optima, manteniendo la cantidad minima de bolsas dentro de cada una de estas bolsas
sin guardar.

Podemos ver que si todos los tamaños fueran distintos entonces todas podrian estar guardadas en una sola bolsa. El problema es cuando hay mas de una bolsa con el mismo tamaño i, puesto que estas no se pueden guardar en una misma bolsa. Entonces la respuesta esta acotada inferiormente por la cantidad maxima de bolsas con el mismo , digamos max_rep. Pero veamos que si ordenamos los tamaños de bolsas (bag), entonces todas las bolsas en posiciones con el mismo residuo modulo max_rep serían distintas, puesto que la cantidad maxima de bolsas con el mismo tamaño (que estan continuas en el arreglo ordenado) es menor o igual a max_rep. Ahora obteniendo estos grupos encontramos un acomodo para guardar las bolsas con max_rep bolsas sin guardar.

Complejidad

O(T*N*Log(N)). Donde T es la cantidad de casos, y N la cantidad de bolsas.
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

    cin >> N;
    while (N)
    {
        vector < int > bag(N);
        for (auto &b : bag)
            cin >> b;
        sort(all(bag));
        int rep = 1, max_rep = 0;
        for (int i = 1; i < N; i++)
        {
            if (bag[i] == bag[i - 1])
            {
                rep++;
                continue;
            }
            max_rep = max(max_rep, rep);
            rep = 1;
        }
        max_rep = max(max_rep, rep);
        cout << max_rep << "\n";
        for (int r = 0; r < max_rep; r++, cout << "\n")
            for (int i = r; i < N; i += max_rep)
                cout << bag[i] << (i + max_rep < N ? " " : "");
        cin >> N;
        if (N)
            cout << "\n";
    }

    return 0;
}