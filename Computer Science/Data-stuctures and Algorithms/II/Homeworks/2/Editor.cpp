#include <iostream>
#include <algorithm>
#include <vector>

#define ll long long
#define left(x) (x << 1 | 1)
#define right(x) (left(x) + 1)
#define half (l + r) / 2
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)

using namespace std;
const ll LN = (int)1e5 + 5, LK = 10, INF = (int)1e9;

template < typename T >
struct SParenthesis
{
	T sum, prefix_min, prefix_max;

	SParenthesis& operator += (const SParenthesis& rhs)
	{
		this->sum += rhs.sum;
		this->prefix_min += rhs.prefix_min;
		this->prefix_max += rhs.prefix_max;
		return *this;
	}
	friend SParenthesis operator+(SParenthesis lhs, const SParenthesis& rhs)
	{
		lhs += rhs;
		return lhs;
	}
	SParenthesis& operator -= (const SParenthesis& rhs)
	{
		this->sum -= rhs.sum;
		this->prefix_min -= rhs.prefix_min;
		this->prefix_max -= rhs.prefix_max;
		return *this;
	}
	friend SParenthesis operator-(SParenthesis lhs, const SParenthesis& rhs)
	{
		lhs -= rhs;
		return lhs;
	}
};

template < typename T_1, typename T_2>
class CST
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

		node.resize(4 * N);
		lazy.resize(4 * N);
		pend.resize(4 * N);
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
class CSTP : public CST < T_1, T_2 >
{
private:
	T_1 merge(T_1 l, T_1 r)
	{
		return { l.sum + r.sum, min(l.prefix_min, l.sum + r.prefix_min), max(l.prefix_max, l.sum + r.prefix_max) };
	}

	T_1 merge_range(int l, int r, T_1 node, T_2 lazy)
	{
		return node + lazy;
	}

	T_2 merge_lazy(T_2 lazy, T_2 upd)
	{
		return lazy + upd;
	}
public:

	void update(int pos, T_2 val)
	{
		this->tval = val - this->vec[pos];
		this->vec[pos] = val;
		CST < T_1, T_2 >::update(pos, pos, this->tval);
	}
};

int main()
{
	optimizar_io;

	CSTP < SParenthesis < int >, SParenthesis < int >> st;

	int Q;

	cin >> Q;

	st.build(Q, SParenthesis<int>{0, 0, 0}, SParenthesis<int>{0, 0, 0});

	string command;

	cin >> command;

	int pos = 0;
	SParenthesis < int > ans;
	for (char c : command)
	{
		if (c == 'R')
			pos++;
		else if (c == 'L')
		{
			if (pos)
				pos--;
		}
		else if (c == '(')
			st.update(pos, SParenthesis<int>{ 1, 1, 1 });
		else if (c == ')')
			st.update(pos, SParenthesis<int>{ -1, -1, -1 });
		else
			st.update(pos, SParenthesis<int>{ 0, 0, 0 });

		ans = st.query(0, Q - 1);
		cout << (ans.prefix_min < 0 || ans.sum != 0 ? -1 : ans.prefix_max) << "\n";
	}

	return 0;

}