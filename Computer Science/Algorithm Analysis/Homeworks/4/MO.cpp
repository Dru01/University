// clang-format off
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// --------------------------- Defines -------------------------------------  //
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
    return os << '(' << p.first << ", " << p.second << ')'; 
}

template <typename Tc,
          typename T = typename enable_if<!is_same<Tc, string>::value,
                                          typename Tc::value_type>::type>
ostream &operator<<(ostream &os, const Tc &v) {
    os << '{';
    for (const T &x : v) os << x << ',';
    return os << '}';
}

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef DEBUG
    #define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
    #define dbg(...)
#endif

#define all(x) (x).begin(), (x).end()
#define forn(i, n) for(int i = 0; i < n; i++)
#define MOD(n) ( ( ((n) % mod) + mod ) % mod)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vp;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// --------------------------- Constants ----------------------------------- //
const ll LN = 0, 
         LM = 0, 
         mod = (ll)(1e9) + 7;
// ------------------------- Your code ---------------------------------- //
// clang-format on

template <typename T>
class CQuery
{
public:
    int l, r, idx;
    T val;
    ll ord;

    // Este orden es el propuesto en https://codeforces.com/blog/entry/61203
    inline ll gilbertOrder(int x, int y, int pow, int rotate)
    {
        if (pow == 0)
            return 0;
        int hpow = 1 << (pow - 1);
        int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const int rotateDelta[4] = {3, 0, 0, 1};
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int nrot = (rotate + rotateDelta[seg]) & 3;
        ll subSquareSize = ll(1) << (2 * pow - 2);
        ll ans = seg * subSquareSize;
        ll add = gilbertOrder(nx, ny, pow - 1, nrot);
        ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
        return ans;
    }

    CQuery() : l(0), r(0), idx(0), ord(0), val(T()) {}

    CQuery(int l, int r, T val, int idx) : l(l), r(r), idx(idx), val(val), ord(gilbertOrder(l, r, 21, 0)) {}

    friend inline bool operator<(const CQuery<T> &a, const CQuery<T> &b)
    {
        return a.ord < b.ord;
    }
};

ordered_set<pair<int, int>> s;
vector<int> num;

void remove(int idx)
{
    s.erase({num[idx], idx});
}
void add(int idx)
{
    s.insert({num[idx], idx});
}
int get_answer(CQuery<int> q)
{
    return s.order_of_key({q.val, INT32_MAX});
}

template <typename T>
vector<T> MO(vector<CQuery<int>> query)
{
    vector<T> ans(query.size());
    sort(all(query));

    int l = 0, r = 0;

    for (auto &q : query)
    {
        while (r < q.r)
            add(r++);
        while (l > q.l)
            add(--l);
        while (r > q.r)
            remove(r--);
        while (l < q.l)
            remove(l++);

        ans[q.idx] = get_answer(q);
    }

    return ans;
}

void Solve()
{
    int N, Q;

    cin >> N >> Q;

    num.resize(N);
    for (auto &i : num)
        cin >> i;

    vector<CQuery<int>> q;
    for (int i = 0; i < Q; i++)
    {
        int l, r, m;
        cin >> l >> r >> m;
        q.emplace_back(l, r + 1, m, i);
    }

    auto ans = MO<int>(q);

    for (auto &i : ans)
        cout << i << '\n';
}

// clang-format off
// --------------------------------------------------------------------- //
int main() {
    #ifdef DEBUG
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #else
        ios_base::sync_with_stdio(0); cin.tie(0);
    #endif

    int Tc = 1;
    //cin >> Tc;

    forn(i, Tc)
        Solve();

    return 0;
}