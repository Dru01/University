#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

#define ll long long
#define left(x) (x << 1 | 1)
#define right(x) (left(x) + 1)
#define half (l + r) / 2
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)

using namespace std;
const ll LN = (int)1e5 + 5, LK = 10, INF = (int)1e9;

template < typename T_1>
class CST
{
private:
	vector < vector < T_1 > > ST;
	vector < vector < T_1 > vec;
	int N = 0;

public:

	void build(int N, T_1 dflt_node, vector < T_1 > vec)
	{
		this->N = N;
		this->dflt_node = dflt_node;
		this->vec = vec;
		ST.resize(log(N)+1);
		vector < T_1 > act(N);
		for (int j = 1; j < ST.size(); j <<= 1)
		{
			for (int i = 0; i + j < N; i++)
				act[i] = (j == 1 ? vec[i] : min(ST[j - 1][i], ST[j - 1][i + j >> 1]));
			ST[j] = act;
		}
	}

	T_1 query(int l, int r)
	{
		int logq = ceil(log(l - r));
		return min(ST[logq][l], ST[loqg][r-logq]);
	}

};

class CGraph
{
public:
	int V, E;
	vector < vector < int > > adj;
	CGraph(int N, vector < vector < int > > adj)
	{
		this->adj = adj;
	}
};

template < typename Tval >
class CTree : public CGraph
{
private:
	int dfs(int act, int depth, int prev)
	{
		if (visited[act])
			return 0;
		visited[act] = true;
		node[act].depth = depth;
		node[act].father = prev;
		for (auto x : adj[act])
			node[x].size += dfs(x, depth + 1, act);
		visited[act] = false;
		return node[act].size;
	}
protected:
	struct SNode
	{
		Tval val;
		int depth, father, size;
	};
	vector < bool > visited;
public:
	vector < SNode > node;
	int root = 0;
	CTree(int N, vector < vector < int > > adj, vector < Tval > val) : CGraph(N, adj)
	{
		node.resize(N);
		visited.resize(N);
		for (int i = 0; i < N; i++)
			node[i].val = val[i];
		dfs(0, 0, 0);
	}
};

template < typename Tval >
class MOs_Tree : public CTree < Tval>
{
private:
	void dfs(int act)
	{
		if (this->visited[act])
			return;
		this->visited[act] = true;
		act_path[AN++] = act;
		for (auto x : this->adj[act])
			dfs(x);
	}
protected:
	vector < int > act_path;
	int AN = 0, block_size, tl, tr;
	vector < int > bucket;
public:
	MOs_Tree(int N, vector < vector < int > > adj, vector < Tval > val) : CTree<Tval>(N, adj, val)
	{
		act_path.resize(2*N);
		AN = 0;
		block_size = sqrt(AN);
		dfs(0);
	}

	void grow(pos)
	{
		bucket[node[act_path[pos]].val]++;
	}

	void decrese(pos)
	{
		bucket[node[act_path[pos]].val]--;
	}

	void move_pointer(int &prev, int dest)
	{
		while (prev != dest)
		{
			if (prev < dest)
			{
				grow(prev);
				prev++;
			}
			else
			{
				decrese(prev);
				prev--;
			}
		}
	}

	vector < Tval > querys(vector < pair < int, int > > q)
	{
		struct query_order {
			int l, int r, int index;
			
			static bool mos_order(const query_order& a, const query_order& b)
			{
				return (a.l / blocksize < b.l / block_size) || (a.l / block_size == b.l / block_size && a.r < b.r);
			}

			static bool org_order(const query_order& a, const query_order& b)
			{
				return (a.index < b.index);
			}
		};

		vector < query_order > moq(q.size());
		for (int i = 0; i < q.size(); i++)
			moq[i] = { q[i].first, q[i].second, i };
		sort(all(moq), query_order.mos_order)


	}
};

int main()
{
	optimizar_io;

	int N, Q;

	vector < vector < int > > adj;
	vector < ll > val;

	cin >> N >> Q;

	adj.resize(N);
	val.resize(N);

	for (int i = 0; i < N; i++)
		cin >> val[i];

	int u, v;
	for (int i = 1; i < N; i++)
	{
		cin >> u;
		adj[i].push_back(u);
		adj[u].push_back(i);
	}

	return 0;

}