// clang-format off
#include <bits/stdc++.h>
using namespace std;

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
// --------------------------- Constants ----------------------------------- //
const ll LN = 0, 
         LM = 0, 
         mod = (ll)(1e9) + 7;
// ------------------------- Your code ---------------------------------- //
// clang-format on

ll sumt(const vector<ll> &num, ll T)
{
    if (num.size() == 1)
        return num[0] == T;

    ll N = num.size();
    ll half = N / 2;

    map<ll, ll> bucket;
    for (ll i = half - 1, sum = 0; i >= 0; i--)
    {
        sum += num[i];
        bucket[sum]++;
    }

    ll ans = 0;
    for (ll i = half, sum = 0; i < N; i++)
    {
        sum += num[i];
        if (bucket.count(T - sum))
            ans += bucket[T - sum];
    }

    return ans +
           sumt(vector<ll>(num.begin(), num.begin() + half), T) +
           sumt(vector<ll>(num.begin() + half, num.end()), T);
}

void Solve()
{
    ll N, T;

    cin >> N >> T;

    vector<ll> num(N);

    for (int i = 0; i < N; i++)
        cin >> num[i];

    cout << sumt(num, T);
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