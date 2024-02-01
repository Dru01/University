#include <iostream>
#include <map>
#include <vector>
#include <string>
#define ll long long
using namespace std;
struct treap
{
    ll val;
    treap *left;
    treap *right;
    ll seg;
    ll hijIzq;
    ll hijDer;
    ll p;
    treap()
    {
        left = right = NULL;
        val = seg = 0;
        hijIzq = hijDer = 0;
        p = rand();
    }
    void arreglar()
    {
        seg = val;
        hijIzq = 0;
        hijDer = 0;
        if (left != NULL)
        {
            hijIzq = left->hijIzq + 1 + left->hijDer;
            seg = max(seg, left->seg);
        }
        if (right != NULL)
        {
            hijDer = right->hijIzq + 1 + right->hijDer;
            seg = max(seg, right->seg);
        }
        return;
    }
};
treap *merge(treap *A, treap *B)
{
    if (A == NULL && B == NULL)
    {
        return NULL;
    }
    if (A == NULL)
    {
        return B;
    }
    if (B == NULL)
    {
        return A;
    }
    if (A->p > B->p)
    {
        A->right = merge(A->right, B);
        A->arreglar();
        return A;
    }
    else
    {
        B->left = merge(A, B->left);
        B->arreglar();
        return B;
    }
}
pair<treap *, treap *> split(treap *A, ll obj)
{
    pair<treap *, treap *> tem;
    if (A == NULL)
    {
        tem.first = NULL;
        tem.second = NULL;
        return tem;
    }
    if (A->hijIzq < obj)
    {
        tem = split(A->right, obj - (A->hijIzq + 1));
        A->right = tem.first;
        A->arreglar();
        tem.first = A;
        return tem;
    }
    else
    {
        if (A->hijIzq == obj)
        {
            tem.first = A->left;
            A->left = NULL;
            tem.second = A;
            A->arreglar();
            return tem;
        }
        else
        {
            tem = split(A->left, obj);
            A->left = tem.second;
            tem.second = A;
            A->arreglar();
            return tem;
        }
    }
}
treap *erase(treap *A, ll obj)
{
    // cout<<"flag1"<<'\n';
    pair<treap *, treap *> tem1, tem2;
    tem1 = split(A, obj);
    //	cout<<"flag2"<<'\n';
    tem2 = split(tem1.second, 1);
    //	cout<<"flag3"<<'\n';
    A = merge(tem1.first, tem2.second);
    return A;
}
int main()
{
    srand(23987);
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    map<ll, treap *> hash;
    ll n;
    cin >> n;
    treap *tem;
    treap *tema;
    ll temi;
    cin >> temi;
    tem = new treap;
    tem->val = temi;
    tem->seg = temi;
    for (ll i = 1; i < n; i++)
    {
        cin >> temi;
        tema = new treap;
        tema->val = temi;
        tema->seg = temi;
        tem = merge(tem, tema);
    }
    hash[0] = tem;
    ll m;
    cin >> m;
    ll l1, l2, l3;
    map<ll, treap *>::iterator it;
    pair<treap *, treap *> pareja, pareja1;
    treap *ca;
    treap *ce;
    treap *ci;
    treap *co;
    treap *cu;
    for (ll i = 0; i < m; i++)
    {
        cin >> l1;
        if (l1 == 0)
        {
            cin >> l2 >> l3;
            it = hash.upper_bound(l2);
            it--;
            l2 -= it->first;
            l3 -= it->first;
            pareja = split(it->second, l3 + 1);
            ci = pareja.second;
            pareja = split(pareja.first, l2);
            if (pareja.second != NULL)
            {
                cout << pareja.second->seg << '\n';
            }
            else
            {
                cout << -1 << '\n';
            }
            ca = merge(pareja.first, pareja.second);
            ca = merge(ca, ci);
            it->second = ca;
            continue;
        }
        if (l1 == 1)
        {
            cin >> l2;
            it = hash.upper_bound(l2);
            it--;
            l2 -= it->first;
            it->second = erase(it->second, l2);
            continue;
        }
        if (l1 == 2)
        {
            cin >> l2 >> l3;
            it = hash.upper_bound(l2);
            it--;
            l2 -= it->first;
            l3 -= it->first;
            if (l2 < l3)
            {
                pareja = split(it->second, l2);
                ca = pareja.first;
                pareja = split(pareja.second, 1);
                ce = pareja.first;
                pareja = split(pareja.second, l3 - l2);
                ci = pareja.first;
                cu = pareja.second;
                cu = merge(ce, cu);
                cu = merge(ci, cu);
                cu = merge(ca, cu);
                it->second = cu;
            }
            else
            {
                pareja = split(it->second, l3);
                ca = pareja.first;
                pareja = split(pareja.second, l2 - l3);
                ce = pareja.first;
                pareja = split(pareja.second, 1);
                ci = pareja.first;
                co = pareja.second;
                ca = merge(ca, ci);
                ca = merge(ca, ce);
                ca = merge(ca, co);
                it->second = ca;
            }
            continue;
        }
        if (l1 == 3)
        {
            cin >> l2;
            it = hash.upper_bound(l2);
            it--;
            l2 -= it->first;
            pareja = split(it->second, l2 + 1);
            hash[l2 + it->first + 1] = pareja.second;
            it->second = pareja.first;
        }
    }
    return 0;
}