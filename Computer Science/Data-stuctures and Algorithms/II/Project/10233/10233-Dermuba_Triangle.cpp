/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema nos da un par de indices de dos posiciones en una region triangular. Nos pide la distancia entre el centro de estas dos posiciones.

Primero encontraremos en que renglon y columna estan ubicados (enumeradas desde 0), para ello basta con darse cuenta que el indice en la primera casilla de cada renglon r es r*r, esto puesto que la suma de los primeros r números impares es r*r. Ahora que tenemos las las coordenas de las posiciones en la forma (columna, renglon), ahora calculamos sus coordenadas en la forma (x,y) y con ello calculamos la distancia. Para la distancia en x esta dada por la diferencia de las columnas por .5 puesto que la distancia en x entre dos regiones consecutivas en un mismo renglon es .5. Para la distancia en y esta dada por la diferencia de renglones - 1 por sqrt(3)/2 puesto que la altura de un triangulo equilatero con lado 1 es eso, pero tenemos que hacer un pequeño ajuste por donde esten ubicados los triangulos porque es diferente que esten boca arriba o boca abajo. Obteniendo estas dos distancias usamos pitagoras para encontras la distancia deseada.

Complejidad

O(Tsqrt(N)). Donde T es la cantidad de casos, y N el indice de la posicion en la region triangular.
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

const ll LN = (int)(26 + 1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
ll N, M, K, T;

ll row(ll num)
{
    ll r = 0;
    while ((r + 1) * (r + 1) <= num)
        r++;
    return r;
}

ll column(ll num, ll row)
{
    return num - (row) * (row + 1);
}

double center(ll num, ll row)
{
    double ccenter = 1.0 / (2.0 * sqrt(3.0));
    if ((num - row) % 2)
        return sqrt(3.0) / 2.0 - ccenter;
    else
        return ccenter;
}

int main()
{
    //optimizar_io;

    ll rn, rm, cn, cm;
    double dr, dc;
    cout.precision(3);
    cout.setf(ios::fixed | ios::showpoint);
    while (cin >> N >> M)
    {
        rn = row(N);
        rm = row(M);
        dr = (double)(rm - rn) * (sqrt(3.0)/2.0) + center(N, rn) - center(M, rm);
        cn = column(N, rn);
        cm = column(M, rm);
        dc = (cn - cm)/2.0;
        cout << sqrt(dr * dr + dc * dc) << "\n";
    }
}