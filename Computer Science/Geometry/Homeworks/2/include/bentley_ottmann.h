#ifndef BENTLEY_OATTMANN_H
#define BENTLEY_OATTMANN_H

#include "treap.h"
#include "line_segment.h"
#include "vector.h"
#include "angle_comparision.h"
#include <functional>

#define all(x) x.begin(), x.end()

template < typename T>
class CBO
{
private:

    class CSSL : public ACTreap < CLine_Segment < T >, bool >
    {
        private:

        typedef ACTreap < CLine_Segment < T >, bool > base;
        typedef typename base::SNode * node_ptr;

        void merge(node_ptr node) {}
        void merge_range(node_ptr node){}
        void merge_lazy(node_ptr node, bool lazy){}

        inline bool lower_bound_by_angle(node_ptr node, int ind, CVector<T> val)
        {
            return side(node->val.tl, node->val.tr, val) > 0;
        }

        inline bool upper_bound_by_angle(node_ptr node, int ind, CVector<T> val)
        {
            return side(node->val.tl, node->val.tr, val) >= 0;
        }

        public:

        vector<CLine_Segment < T >> segments_contained(CVector<T> u)
        {
            auto partition = base::_separate(
                [&](node_ptr node, int prev)->bool { return lower_bound_by_angle(node, prev, u); },
                [&](node_ptr node, int prev)->bool { return upper_bound_by_angle(node, prev, u); }
            );
            base::_node_path(partition[1]);
            delete partition[1];
            base::_merge_partition(partition);
            return this->path;
        }

        void insert_multiple(vector<CLine_Segment < T >> seg, CVector<T> u)
        {
            node_ptr troot = nullptr;
            swap(troot, this->root);
            for (int i = 0; i < seg.size(); i++)
                    _insert(seg[i], i);
            swap(troot, this->root);
            auto partition = base::_separate(
                [&](node_ptr node, int prev)->bool
                {
                    return lower_bound_by_angle(node, prev, u);
                },
                [&](node_ptr node, int prev)->bool
                {
                    return upper_bound_by_angle(node, prev, u);
                }
            );
            base::_merge_partition(partition);
        }

        int lower_bound(CVector<T> u)
        {
            return base::_find([&](node_ptr node, int prev)->bool { return lower_bound_by_angle(node, prev, u); });
        }

        int upper_bound(CVector<T> u)
        {
            return base::_find([&](node_ptr node, int prev)->bool { return upper_bound_by_angle(node, prev, u); });
        }
        
    };

    class CEQ : public ACTreap < pair < CVector < T >, vector < int > >, bool >
    {
        private:

        typedef pair < CVector < T >, vector < int > > T_1;
        typedef ACTreap < T_1, bool > base;
        typedef typename base::SNode * node_ptr;
        typedef array<node_ptr,2> _pair_node_ptr;

        void merge(node_ptr node) {}
        void merge_range(node_ptr node) {}
        void merge_lazy(node_ptr node, bool lazy) {}

        public:

        void insert(CVector < T > u, int idx = -1)
        {
            auto partition = base::_separate(
                [&](node_ptr node, int prev)->bool { return node->val.first < u; },
                [&](node_ptr node, int prev)->bool { return node->val.first <= u; }
            );
            if(!partition[1])
                partition[1] = new typename base::SNode({u, vector<int>()});
            if(idx != -1)
                partition[1]->val.second.push_back(idx);
            this->root = base::_merge(_pair_node_ptr{partition[0],base::_merge(_pair_node_ptr{partition[1],partition[2]}, 0)}, 0);
        }

        T_1 top()
        {
            return base::query(0,0);
        }

        void pop()
        {
            base::_erase(0);
        }

        bool empty()
        {
            return !base::size(this->root);
        }
        
    };

    CEQ eq;
    CSSL ssl;

public:
    vector < pair < CVector < T >, CLine_Segment < T > > > intersections;

    void find_new_event(int pos, const CVector<T> &act)
    {
        if(!pos)
            return;
        auto tl = ssl.query(pos - 1, pos - 1);
        auto tr = ssl.query(pos, pos);
        auto intersection = intersect(tl,tr);
        if(intersection.first == false || intersection.second.tl != intersection.second.tl || intersection.second.tl <= act)
            return;
        eq.insert(intersection.second);
        return;
    }

    void handle_point()
    {
        pair < CVector < T >, vector < int > > act = eq.top();
        eq.pop();
        vector < int > U = act.second, L, C;
        auto segment = ssl.segments_contained(act.first);
        for (auto &&s : segment)
        {
            if(s.tr == act.first)
                L.push_back(s);
            else
                C.push_back(s);
        }
        
        C.insert(L.begin(), all(U));
        sort(all(C), CAngle_Comparision(act.first));
        L.insert(L.begin(), all(C));
        if(L.size())
            intersections.emplace_back(act, L);
        
        ssl.insert_multiple(C);

        int tl = ssl.lower_bound(act.first);
        int tr = ssl.upper_bound(act.first);
        
        find_new_event(tl, act);
        if(tr != tl)
            find_new_event(tr,act);
    }

    CBO(vector < CLine_Segment < T > > segment)
    {
        for (int i = 0; i < segment.size(); i++)
        {
            eq.insert(segment[i].tl, i);
            eq.insert(segment[i].tr);
        }
        
        while(!eq.empty())
            handle_point();
    }
};

#endif // !BENTLEY_OATTMANN_H