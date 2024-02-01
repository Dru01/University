/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema nos pide encontrar 5 jugadores con mejor ataque y los 5 jugadores con peor ataque y luego ordenar cada uno de ellos por nombre.

Basta ver que primero ordenando por ataque los 10 jugadores y luego ordenar cada una de las mitades por nombre ñobtenemos la respuesta.

Complejidad

O(T*(log(N)). Donde T es la cantidad de casos, y N la cantidad de jugadores.
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
#include <numeric>
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

const ll LN = (ll)(2e2 + 1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll memo[17][17][17];

bool att_deff_name_comp(pair < string, pair < int, int > > l, pair < string, pair < int, int > > r)
{
    if (l.second.first != r.second.first)
        return l.second.first > r.second.first;
    if (l.second.second != r.second.second)
        return l.second.second < r.second.second;
    return l.first < r.first;
}

bool name_comp(pair < string, pair < int, int > > l, pair < string, pair < int, int > > r)
{
    return l.first < r.first;
}

int main()
{
    optimizar_io;

    cin >> T;
    vector < pair < string, pair < int, int > > > team(10);
    for (int t = 1; t <= T; t++)
    {

        for (int i = 0; i < 10; i++)
            cin >> team[i].first >> team[i].second.first >> team[i].second.second;

        sort(all(team), att_deff_name_comp);
        sort(team.begin(), team.begin() + 5, name_comp);
        sort(team.begin() + 5, team.begin() + 10, name_comp);

        cout << "Case " << t << ":\n";
        for (int i = 0; i < 2; i++)
        {
            cout << "(";
            for (int j = 0; j < 5; j++)
                cout << team[i * 5 + j].first << (j != 4 ? ", " : "");
            cout << ")\n";
        }

    }

    return 0;
}