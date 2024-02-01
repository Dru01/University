#include <iostream>
#include <algorithm>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#define ll long long
#define left(x) (x << 1 | 1)
#define right(x) (left(x) + 1)
#define half (l + r) / 2
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)

using namespace __gnu_pbds;
using namespace std;
const ll LN = (int)1e6 + 5, LK = 10, INF = (int)1e9;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

template < typename T_1>
class CST
{
protected:
	vector < T_1 > node;
	vector < int > vec;
	int tval;
	int tl = 0, tr = 0, N = 0;
	bool init = false;

	bool out_range(int l, int r)
	{
		if (tl > r || tr < l)
			return true;
		return false;
	}

	int _prev(int pos, int l, int r)
	{
		return node[pos].order_of_key(tr+1) - node[pos].order_of_key(tl);
	}

	void _delete(int pos, int l, int r)
	{
		if (out_range(l, r))
			return;
		node[pos].erase(tval);
		if (l == r)
			return;
		_delete(left(pos), l, half);
		_delete(right(pos), half + 1, r);
	}

	void _insert(int pos, int l, int r)
	{
		if (out_range(l, r))
			return;
		node[pos].insert(tval);
		if (l == r)
			return;
		_insert(left(pos), l, half);
		_insert(right(pos), half + 1, r);
	}

	int _query(int pos, int i, int l, int r)
	{
		if(l == r)
			return l;
		int prev = _prev(left(pos), l, r);
		if(prev > i)
			return _query(left(pos), i, l, half);
		else
			return _query(right(pos), i-prev, half + 1, r);
	}

public:

	void build(int N)
	{
		this->N = N;
		node.resize(4 * N);
		vec.resize(N, -1);
	}

	void update(int pos, int val)
	{
		tl = vec[pos];
		tr = vec[pos];
		tval = pos;
		if (tl != -1)
			_delete(0, 0, N - 1);
		tl = val;
		tr = val;
		vec[pos] = val;
		tval = pos;
		_insert(0, 0, N - 1);
	}

	int query(int l, int r, int val)
	{
		tl = l;
		tr = r;
		return _query(0, val, 0, N - 1);
	}

};

int main()
{
	optimizar_io;

	int N, M;

	CST < tree < int ,  null_type ,  less < int > ,  rb_tree_tag ,  tree_order_statistics_node_update > > tr;

	tr.build(LN);

	cin >> N;

	for(int i = 0, val; i < N; i++)
	{
		cin >> val;
		tr.update(i, val);
	}

	cin >> M;

	int type, l, r, val;
	while(M--)
	{
		cin >> type;
		if(type)
		{
			cin >> l >> val;
			tr.update(l,val);
		}
		else
		{
			cin >> l >> r >> val;
			cout << tr.query(l,r,val) << "\n";
		}
	}

	return 0;

}