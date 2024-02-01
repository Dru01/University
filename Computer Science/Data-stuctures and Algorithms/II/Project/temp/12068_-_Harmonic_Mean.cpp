/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide cálcular la media harmonica de N enteros.

Basta con reducir la fraccion a una expresión donde sea solo sumas, productos y una división. Esto agrupando las fracciones en una sola que comparten el mismo denominador. Por último falta checar que sea una fracción irreducible, por lo que calcula el gcd y los dividimos

Complejidad

O(T*N). Donde T es la cantidad de casos, y N la cantidad de numeros dados.
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

const ll LN = (int)(1e1 + 1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll a[LN];

ll gcd(ll a, ll b)
{
	return (b ? gcd(b, a % b) : a);
}

int main()
{
	optimizar_io;

	cin >> T;
	int m, n, prod_a;
	for (int t = 0; t < T; t++)
	{
		cin >> N;
		m = 0;
		n = 0;
		prod_a = 1;
		for (int i = 0; i < N; i++)
			cin >> a[i], prod_a *= a[i];
		
		m = prod_a * N;
		for (int i = 0; i < N; i++)
			n += prod_a / a[i];

		cout << "Case " << t << ": " << m / gcd(m, n) << "/" << n / gcd(m, n) << "\n";
	}
	return 0;
}