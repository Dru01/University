//Rubén Pérez Palacios, 2021.
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

#define ll long long
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)

using namespace std;

template < typename T >
class BST
{
private:

	struct Node
	{
		Node(T val = 0)
		{
			this->val = val;
			l = r = NULL;
		}
		~Node()
		{
			delete l;
			delete r;
		}
		T val;
		Node *l, *r;
	};

	Node *root, *q;
	T tval;

	Node* _search(Node* node)
	{
		//cont_search++;
		if (!node || node->val == tval)
			return node;
		cont_search++;
		if (node->val < tval)
			return _search(node->r);
		else
			return _search(node->l);
	}

	Node* _insert(Node* node)
	{
		cont_insert++;
		if (!node)
			return new Node(tval);
		//cont_insert++;
		if (node->val == tval)
			return node;
		if (tval > node->val)
			node->r = _insert(node->r);
		else
			node->l = _insert(node->l);
		//cont_insert++;
		return node;
	}

public:

	ll cont_insert, cont_search;

	BST(T val = 0)
	{
		root = new Node(val);
		cont_insert = cont_search = 0;
	}

	void insert(T val)
	{
		tval = val;
		_insert(root);
	}

	bool query(T val)
	{
		tval = val;
		return _search(root);
	}

	void clear()
	{
		delete root;
		root = new Node();
		cont_insert = cont_search = 0;
	}
};

template < typename T >
T grand(T tmin, T tmax)
{
	return ((double)rand() / RAND_MAX) * (tmax - tmin) + tmin;
}

int main()
{
	optimizar_io;

	BST < ll > bst;

	ll N = 1, M, tmin = 0, tmax = 1e18;

	srand(time(NULL));
	for(int i = 0; N <= 1e8; N *= ((i++%2)?2:5))
	{
		for (int j = 0; j < N; j++)
			bst.insert(grand < ll >(tmin, tmax));
		cout << bst.cont_insert << ",";
		bst.clear();
	}

	return 0;
}