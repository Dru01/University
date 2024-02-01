#ifndef TREAP_H
#define TREAP_H

#include <bits/stdc++.h>
using namespace std;

template <typename T_1, typename T_2>
class ACTreap
{
protected:
	struct SNode
	{
		T_1 val;
		int priority;
		
		int size, tl, tr, freq;
		
		T_2 lazy;
		bool pend;
		
		array <SNode * ,2> son;
		SNode(T_1 val = T_1())
		{
			son[0] = son[1] = nullptr;
			priority = rand();
			this->val = val;
			freq = 1;
			size = 1;
			pend = false;
			tl = tr = 0;
		}
		~SNode()
		{
			delete (son[0]);
			delete (son[1]);
		}
	};

	typedef SNode *  _node_ptr;
	typedef array<_node_ptr,2> _pair_node_ptr;
	typedef function<bool(_node_ptr, int)> _comp_fun;

	_node_ptr root = nullptr;
	vector<T_1> path;
	int N, tindex;
	_comp_fun comp;

	virtual void merge(_node_ptr node) = 0;
	virtual void merge_range(_node_ptr node) = 0;
	virtual void merge_lazy(_node_ptr node, T_2 lazy) = 0;

	int size(_node_ptr node) { return node ? node->size : 0; }
	bool pos_lower_bound(_node_ptr node, int prev, int pos){ return ((prev + size(node->son[0])) < pos); }
	bool pos_upper_bound(_node_ptr node, int prev, int pos){ return ((prev + size(node->son[0])) <= pos); }

	void propagate(_node_ptr node)
	{
		if(!node)
			return;
		if (node->pend)
		{
			merge_range(node);
			if (node->son[0])
				merge_lazy(node->son[0], node->lazy);
			if (node->son[1])
				merge_lazy(node->son[1], node->lazy);
		}
	}

	void _update(_node_ptr node, int prev)
	{
		if (!node)
			return;
		node->size = size(node->son[0]) + size(node->son[1]) + node->freq;
		merge(node);
		node->tl = prev;
		node->tr = prev + node->size - 1;
	}

	_pair_node_ptr _split(_node_ptr node, int prev)
	{
		if (!node)
			return {nullptr, nullptr};
		propagate(node);
		_node_ptr T;
		bool side = comp(node, prev);
		if (side)
			tie(node->son[1], T) = tuple_cat(_split(node->son[1], prev + size(node->son[0]) + 1));
		else
			tie(T, node->son[0]) = tuple_cat(_split(node->son[0], prev));
		_update(node, prev);
		return side ? _pair_node_ptr{node, T} : _pair_node_ptr{T, node};
	}

	_node_ptr _merge(_pair_node_ptr node, int prev)
	{
		_node_ptr T;
		propagate(node[0]);
		propagate(node[1]);
		if (!node[0] || !node[1])
			T = node[!node[0]];
		else
		{
			if (node[0]->priority > node[1]->priority)
				T = node[0], T->son[1] = _merge(_pair_node_ptr{node[0]->son[1], node[1]}, prev + size(node[0]->son[0]) + 1);
			else
				T = node[1], T->son[0] = _merge(_pair_node_ptr{node[0], node[1]->son[0]}, prev);
		}
		_update(T, prev);
		return T;
	}

	void _traverse(_node_ptr node)
	{
		if (!node)
			return;
		propagate(node);
		_traverse(node->son[0]);
		path[tindex++] = node->val;
		_traverse(node->son[1]);
	}

	void _node_path(_node_ptr node)
	{
		tindex = 0;
		path.resize(size(node));
		_traverse(node);
	}

	void _merge_partition(array<_node_ptr,3> partition)
	{
		root = _merge(_pair_node_ptr{partition[0], _merge(_pair_node_ptr{partition[1], partition[2]},0)},0);
	}

	array<_node_ptr,3> _separate(_comp_fun _lower_bound, _comp_fun _upper_bound)
	{
		comp = _lower_bound;
		auto L = _split(root, 0);
		comp = _upper_bound;
		auto R = _split(L[1], size(L[0]));
		return {L[0], R[0], R[1]};
	}

	array<_node_ptr,3> _separate(int l, int r)
	{
		return _separate([&](_node_ptr node, int prev)->bool {return pos_lower_bound(node, prev, l);}, [&](_node_ptr node, int prev)->bool {return pos_upper_bound(node, prev, r);});
	}

	void _insert(T_1 val, int pos = -1, _comp_fun _lower_bound = nullptr, _comp_fun _upper_bound = nullptr)
	{
		auto partition = (pos == -1 ? _separate(_lower_bound, _upper_bound) : _separate(pos, pos));
		if(!partition[1])
			partition[1] = new SNode(val);
		else
			partition[1]->freq++;
		_merge_partition(partition);
	}

	void _erase(int pos = -1, _comp_fun _lower_bound = nullptr, _comp_fun _upper_bound = nullptr)
	{
		auto partition = (pos == -1 ? _separate(_lower_bound, _upper_bound) : _separate(pos, pos));
		delete partition[1];
		_merge_partition(partition);
	}

	int _find(_comp_fun comp = nullptr)
	{
		this->comp = comp;
		auto partition = _split(root, 0);
		int ans = size(partition[0]);
		root = _merge(_pair_node_ptr{partition[0],partition[1]}, 0);
		return ans;
	}

public:

	~ACTreap()
	{
		delete root;
	}

	virtual void build(int N = 0, vector<T_1> vec = vector<T_1>())
	{
		this->N = N;
		if(!vec.empty())
			for (int i = 0; i < N; i++)
				_insert((vec.empty() ? T_1() : vec[i]), i);
	}
	
	virtual T_1 query(int l, int r)
	{
		auto partition = _separate(l, r);
		T_1 ans = partition[1]->val;
		_merge_partition(partition);
		return ans;
	}

	virtual void update(int l, int r, T_2 val)
	{
		auto partition = _separate(l, r);
		merge_lazy(partition[1], val);
		_merge_partition(partition);
	}
};

#endif // !TREAP_H