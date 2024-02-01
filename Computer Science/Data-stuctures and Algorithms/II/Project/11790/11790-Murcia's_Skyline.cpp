/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar Longest_Increasing-Subsquence, Longest_Decreasing-Subsquence, de dos arreglos H, W. Donde la longitud de una subsecuencia
es la suma de su valores en W, y la restricción de creciente y decreciente esta dada por los valores de H.

Para ello podemos hacer una DP[], donde DP[i] representa el tamaño de subsecuencia creciente mas larga tal que su último elemento es A[i].
Puesto que las transiciones es iterar sobre todos los anteriores DP[j] (j < i) y encontrar el máximo DP[max] tal que A[max] < A[i], entonces nos apoyamos
de un segment-tree para responder esto (el máximo sobre un rango de altura [0, A[i]-1]). Puesto que el rango de alturas puede ser muy grande, lo comprimimos primero
para no excedernos en memoria. Por último notemos que si revertimos el orden de H y W entonces encontrar LDS de la original es encontrar el LIS del nuevo.

Complejidad

O(T*N*log(N)). Donde T es la cantidad de casos, y N el tamaño maximo de los arreglos.
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

const ll LN = (int)(100+1), LK = (int)(5e3 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;

template < typename T_1, typename T_2>
class ACST
{
protected:
	vector < T_1 > node;
	vector < T_2 > lazy;
	vector < T_1 > vec;
	vector < bool > pend;
	T_1 dflt_node;
	T_2 tval, dflt_lazy;
	int tl = 0, tr = 0, N = 0;
	bool init = false;

	bool out_range(int l, int r)
	{
		if (tl > r || tr < l)
			return true;
		return false;
	}

	bool in_range(int l, int r)
	{
		if (tl <= l && r <= tr)
			return true;
		return false;
	}

	virtual T_1 merge(T_1 l, T_1 r) = 0;

	virtual T_1 merge_range(int l, int r, T_1 node, T_2 lazy) = 0;

	virtual T_2 merge_lazy(T_2 lazy, T_2 upd) = 0;

	void propagate(int pos, int l, int r)
	{
		node[pos] = merge_range(l, r, node[pos], lazy[pos]);
		if (l != r)
		{
			lazy[left(pos)] = merge_lazy(lazy[left(pos)], lazy[pos]);
			pend[left(pos)] = true;
			lazy[right(pos)] = merge_lazy(lazy[right(pos)], lazy[pos]);
			pend[right(pos)] = true;
		}
		lazy[pos] = dflt_lazy;
		pend[pos] = false;
	}

	void _build(int pos, int l, int r)
	{
		lazy[pos] = dflt_lazy;
		pend[pos] = false;
		if (l == r)
		{
			node[pos] = vec[l] = (init ? vec[l] : dflt_node);
			return;
		}
		_build(left(pos), l, half);
		_build(right(pos), half + 1, r);
		node[pos] = merge(node[left(pos)], node[right(pos)]);
	}

	void _update(int pos, int l, int r)
	{
		if (pend[pos])
			propagate(pos, l, r);
		if (out_range(l, r))
			return;
		if (in_range(l, r))
		{
			lazy[pos] = tval;
			propagate(pos, l, r);
			return;
		}
		_update(left(pos), l, half);
		_update(right(pos), half + 1, r);
		node[pos] = merge(node[left(pos)], node[right(pos)]);
	}

	T_1 _query(int pos, int l, int r)
	{
		if (pend[pos])
			propagate(pos, l, r);
		if (out_range(l, r))
			return dflt_node;
		if (in_range(l, r))
			return node[pos];
		return merge(_query(left(pos), l, half), _query(right(pos), half + 1, r));
	}

public:

	virtual void build(int N, T_1 dflt_node, T_2 dflt_lazy, vector < T_1 > vec = vector < T_1 >())
	{
		this->N = N;
		this->dflt_node = dflt_node;
		this->dflt_lazy = dflt_lazy;
		if (vec.empty())
			(this->vec).resize(N);
		else
		{
			this->vec = vec;
			init = true;
		}

		node.resize(4 * N,dflt_node);
		lazy.resize(4 * N,dflt_lazy);
		pend.resize(4 * N,0);
		_build(0, 0, N - 1);
	}

	virtual void update(int l, int r, T_2 val)
	{
		tl = l;
		tr = r;
		tval = val;
		_update(0, 0, N - 1);
	}

	virtual T_1 query(int l, int r)
	{
		tl = l;
		tr = r;
		return _query(0, 0, N - 1);
	}

};

template < typename T_1, typename T_2 >
class CST : public ACST < T_1, T_2 >
{
private:
	T_1 merge(T_1 l, T_1 r)
	{
		return max(l, r);
	}

	T_1 merge_range(int l, int r, T_1 node, T_2 lazy)
	{
		return max(node, lazy);
	}

	T_2 merge_lazy(T_2 lazy, T_2 upd)
	{
		return max(lazy, upd);
	}
};

ll longest_increasing_subsuquence(int N, const vector < ll > &height, const vector < ll > &width)
{
	vector < ll > ord_num(N), dp(N);
	map < ll, ll > compress;
	CST < ll, ll > st;

	ord_num = height;
	sort(all(ord_num));

	for (auto nn : ord_num)
		if (!compress.count(nn))
			compress[nn] = M++;

	st.build(M, 0, 0);

	ll ans = 0;
	for (int i = 0; i < N; i++)
	{
		dp[i] = width[i];
		dp[i] += st.query(0, compress[height[i]] - 1);
		st.update(compress[height[i]], compress[height[i]], dp[i]);
		ans = max(ans, dp[i]);
	}

	return ans;
}

int main()
{
    optimizar_io;

	cin >> T;

    for(int t = 0; t < T; t++)
    {
		cin >> N;
        M = 0;

		vector < ll > height(N), width(N);

        for (int i = 0; i < N; i++)
            cin >> height[i];
		for (int i = 0; i < N; i++)
			cin >> width[i];

		ll lis = longest_increasing_subsuquence(N, height, width);
		reverse(all(height));
		reverse(all(width));
		ll lds = longest_increasing_subsuquence(N, height, width);

		cout << "Case " << t+1 << ". ";
		if (lis >= lds)
			cout << "Increasing (" << lis << "). Decreasing (" << lds << ").";
		else
			cout << "Decreasing (" << lds << "). Increasing (" << lis << ").";

        cout << "\n";
    }

    return 0;
}