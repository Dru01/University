#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)

int M;

template <typename T>
string type_name();

struct CNODE
{
	bool end = false;
	int depth = 0, leaves = 0;
	map < int, CNODE* > son;
};

class CTRIE
{
private:
	int size, ans = -1, pos;
	CNODE* root = new CNODE(), * nodo;

public:

	void insert(string word)
	{
		size = word.size();
		pos = 0;
		nodo = root;
		while (pos < size)
		{
			if (!nodo->son[word[pos] - 'A'])
				nodo->son[word[pos] - 'A'] = new CNODE();
			nodo = nodo->son[word[pos] - 'A'];
			pos++;
		}
		nodo->end = true;
	}

	void dfs(CNODE* node, int depth)
	{

		if (node->end)
			node->leaves = 1;

		node->depth = depth;

		for (auto next : node->son)
		{
			dfs(next.second, depth + 1);
			node->leaves += next.second->leaves;
		}

		if (node->leaves >= M)
			ans = max(ans, depth);
	}

	int solve()
	{
		dfs(root, 0);
		return ans;
	}
};

CTRIE trie;

int main()
{
	optimizar_io;

	string word;

	cin >> word;

	cin >> M;

	string suffix = "";

	for (int i = word.size() - 1; i >= 0; i--)
	{
		suffix = word[i] + suffix;
		trie.insert(suffix);
	}

	cout << trie.solve();

	return 0;
}