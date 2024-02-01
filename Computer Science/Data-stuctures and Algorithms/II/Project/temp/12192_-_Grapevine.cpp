/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide poj

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
int num[LN][LN];

int main()
{
    optimizar_io;

    int ans, tl;

    while (cin >> N >> M, (N || M))
    {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                cin >> num[i][j];
        cin >> T;

        while (T--)
        {
            int a, b;
            cin >> a >> b;

            ans = 0;
            for (int i = 0; i < N; ++i)
            {
                tl = lower_bound(num[i], num[i] + M, a) - num[i];
                for (int j = ans; j < N; ++j)
                {
                    if (N <= i + j || M <= tl + j || b < num[i + j][tl + j])
                        break;
                    ans = max(ans, j + 1);
                }
            }

            cout << ans << "\n";
        }
        cout << "-\n";
    }

    return 0;
}