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
const ll LN = 1e5+10, 
         LM = 0, 
         mod = 998244353;
// ------------------------- Your code ---------------------------------- //
// clang-format on

void Solve()
{
    multiset < pair < int, string>, greater < pair< int, string > > > order;
    map < string, int > food;

    int N;

    cin >> N;

    string o;
    int price;
    string name;
    while (N--)
    {
        cin >> o;

        if (o == "P")
        {
            if (order.empty())
                cout << -1;
            else
                cout << order.begin()->second << " " << order.begin()->first;
            cout << "\n";
        }
        if (o == "IU")
        {
            cin >> name >> price;
            if(food.count(name))
                order.erase(order.find({food[name], name}));
            order.insert({price, name});
            food[name] = price;
        }
        if (o == "DL")
        {
            if(order.empty())
                continue;
            food.erase(order.begin()->second);
            order.erase(order.begin());
        }
        if (o == "D")
        {
            cin >> name;
            if(!food.count(name))
                continue;
            order.erase(order.find({food[name], name}));
            food.erase(name);
        }
    }   
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