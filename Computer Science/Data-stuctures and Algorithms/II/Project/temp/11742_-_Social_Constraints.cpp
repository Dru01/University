/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide cálcular la cantidad de permutaciones tales que se asegure que para una serie de restricciones tales que dos personas tiene que estar alomas/almenos tantos lugares unos del otro.

Basta con recorrer una por una de todas las permutaciones y checando si se cumplen las restricciones.

Complejidad

O(T*N!*M). Donde T es la cantidad de casos, N la cantidad de personas y M la cantidad de restricciones.
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

const ll LN = (ll)(2e2+1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;

int main()
{
    optimizar_io;

	vector < vector < int > > constraint(20, vector < int >(3));
	int ans, tl, tr;
	bool possible;

	while (cin >> N >> M, N || M)
	{
		for (int i = 0; i < M; i++)
			cin >> constraint[i][0] >> constraint[i][1] >> constraint[i][2];

		vector < int > permutation(N);
		iota(all(permutation), 0);
		ans = 0;
		do
		{
			possible = true;
			for (int i = 0; i < M; i++)
			{
				tl = find(all(permutation), constraint[i][0])-permutation.begin();
				tr = find(all(permutation), constraint[i][1])-permutation.begin();

				if ((constraint[i][2] > 0 && abs(tl - tr) > abs(constraint[i][2])) || (constraint[i][2] < 0 && abs(tl - tr) < (-constraint[i][2])))
				{
					possible = false;
					break;
				}
			}

			if (possible)
				ans++;
		} while (next_permutation(permutation.begin(), permutation.begin() + N));

		printf("%d\n", ans);
	}

    return 0;
}