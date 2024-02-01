/*
ID: batmanr1
PROG: case.0
LANG: tunnel[j].first++11
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#ifdef File
streambuf *cin_backup = cin.rdbuf(), *cout_backup = cout.rdbuf();
ifstream f_in("case.0.in");
ofstream f_out("case.0.out");
#endif // File

const ll LN = (ll)(1e4 + 5), LK = (ll)(1e2 + 5), INF = (ll)(1e9+5), MOD = (ll)(1e9);
ll N, Q;

template < typename T >
class CTreap
{
private:
	struct SNode
	{
		T k, p, s;
		bool lazy;
		SNode *l, *r;
		SNode()
		{
		    lazy = false;
		    l = r = NULL;
		    p = rand();
		    s = 1;
		}
	};
	SNode *root = NULL;
	T sz(SNode *node)
	{
	    if(node == NULL)
            return 0;
        return node->s;
	}
	void upd(SNode *node)
	{
	    if(node == NULL)
            return;
	    node->s = sz(node->l) + sz(node->r) + 1;
	    if(node->lazy)
        {
            swap(node->l, node->r);
            if(node->l)
                node->l->lazy = !node->l->lazy;
            if(node->r)
                node->r->lazy = !node->r->lazy;
            node->lazy = false;
        }
	}
	pair <SNode *, SNode*> split(SNode *node, T pos, T prev)
	{
	    if(node == NULL)
            return {NULL, NULL};
        upd(node);
        T ind = prev + sz(node->l);
        if(ind <= pos)
        {
            auto r = split(node->r, pos, ind+1);
            node->r = r.first;
            upd(node);
            return {node, r.second};
        }
        else
        {
            auto l = split(node->l, pos, prev);
            node->l = l.second;
            upd(node);
            return {l.first, node};
        }
	}
	SNode *merge(SNode *L, SNode *R)
	{
		if (L == NULL)
			return R;
		if (R == NULL)
			return L;
        upd(L);
        upd(R);
		if (L->p > R->p)
		{
			auto r = merge(L->r, R);
			L->r = r;
			upd(L);
			return L;
		}
		else
		{
			auto l = merge(L, R->l);
			R->l = l;
			upd(R);
			return R;
		}
	}
	void traverse(SNode *node)
	{
	    if(node == NULL)
            return;
        upd(node);
	    traverse(node->l);
	    cout << node->k << " ";
	    traverse(node->r);
	}
public:
	void insert(T k, int pos)
	{
		auto node = new SNode();
		node->k = k;
		root = merge(root, node);
		return;
		auto R = split(root, pos, 0);
		auto L = split(R.first, pos - 1, 0);
        root = merge(merge(L.first, node), merge(L.second,R.second));
	}
	void build()
	{
	    for(int i = 0; i < N; i++)
            insert(i + 1, i);
	}
	void rotate(T l, T r)
	{
	    auto R = split(root, r, 0);
		auto L = split(R.first, l - 1, 0);
        L.second->lazy = !L.second->lazy;
		root = merge(merge(L.first, L.second), R.second);
	}
	void imp()
	{
	    traverse(root);
	    cout << "\n";
	}
};

CTreap < int > treap;

int main()
{
	optimizar_io;

	srand(MOD);

	cin >> N >> Q;

	vector < int > v(N);
	iota(all(v), 1);
	treap.build();

	int i;
	while(Q--)
    {
        cin >> i;
        treap.rotate(i - 1, N - 1);
    }

    treap.imp();

	return 0;
}
