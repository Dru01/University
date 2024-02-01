#include <iostream>
#include <map>
#include <algorithm>
#include <math.h>

using namespace std;

#define LN int(1e5+10)
#define left(x) (x << 1 | 1)
#define right(x) (left(x) + 1)
#define parent(x) ((x-1) >> 1)

template <class TPriority, class TKey> class UpdatableHeap {

private:

    struct SNode
    {
        TPriority priority;
        TKey key;

        bool operator < (const SNode& a)
        {
            if (priority < a.priority)
                return true;
            if (priority == a.priority && key < a.key)
                return true;
            return false;
        }
    };

    SNode node[LN];
    int N = 0;
    map < TKey, int > pos;
    SNode trash = { -1,"" };

    void heapify_down(int act)
    {
        if (act >= N)
            return;

        int tmax = act;
        
        do
        {
            swap(pos[node[act].key], pos[node[tmax].key]);
            swap(node[act], node[tmax]);
            act = tmax;
            if (left(act) < N && node[act] < node[left(act)])
                tmax = left(act);
            if (right(act) < N && node[tmax] < node[right(act)])
                tmax = right(act);
        } while (act < N && tmax != act);

    }

    void heapify_up(int act)
    {
        while (act && node[parent(act)] < node[act])
        {
            swap(pos[node[act].key], pos[node[parent(act)].key]);
            swap(node[act], node[parent(act)]);
            act = parent(act);
        }
    }

    void imp()
    {
        cout << "-----\nUpdate\n";
        for (auto x : pos)
        {
            cout << x.first << " " << x.second << "\n";
        }
        cout << "-----\n";
    }

public:


    pair<TPriority, TKey> top()
    {
        SNode ans = (N ? node[0] : trash);
        return make_pair(ans.priority, ans.key);
    }

    void pop()
    {
        if (!N)
            return;
        swap(node[0], node[N - 1]);
        pos[node[0].key] = 0;
        pos.erase(node[N - 1].key);
        N--;
        heapify_down(0);
    }

    void insertOrUpdate(const TPriority& p, const TKey& k)
    {
        if (pos.count(k))
        {
            node[pos[k]].priority = p;
            heapify_down(pos[k]);
            heapify_up(pos[k]);
            return;
        }

        int act = N++;
        node[act] = { p,k };
        pos[k] = act;
        heapify_up(act);
    }

    bool isInserted(const TKey& k)
    {
        return pos.count(k) > 0;
    }

    int getSize()
    {
        return N;
    }

    void erase(const TKey& k)
    {
        if (!pos.count(k))
            return;
        int act = pos[k];
        swap(node[act], node[N - 1]);
        pos[node[act].key] = pos[node[N - 1].key];
        pos.erase(node[N - 1].key);
        N--;

        heapify_down(act);
        heapify_up(act);
        return;
    }
};


int main()
{

    UpdatableHeap < int, string> food;

    int N;

    cin >> N;

    string o;
    pair < int, string > act;

    while (N--)
    {
        cin >> o;

        if (o == "P")
        {
            act = food.top();
            if (act.first == -1)
                cout << -1;
            else
                cout << act.second << " " << act.first;
            cout << "\n";
        }
        if (o == "IU")
        {
            cin >> act.second >> act.first;
            food.insertOrUpdate(act.first, act.second);
        }
        if (o == "DL")
            food.pop();
        if (o == "D")
        {
            cin >> act.second;
            food.erase(act.second);
        }
    }

    return 0;
}