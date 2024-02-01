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

    int N, M;
    cin >> N >> M;

    vi health(N);
    for (auto &&h : health)
        cin >> h;
    
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> spell;
    array<int,3> s;
    while(M--)
    {
        cin >> s[0] >> s[1] >> s[2];
        s[0]--;
        s[1]--;
        spell.push(s);
    }

    int ans = 0;
    vi sweep(N+1);
    priority_queue < pii > active; 
    for (int i = 0; i < N; i++)
    {
        while(!spell.empty() && spell.top()[0] <= i)
        {
            active.emplace(spell.top()[1], spell.top()[2]);
            spell.pop();
        }
        sweep[i] += (i ? sweep[i-1] : 0);
        int h = max(health[i] - sweep[i], 0);
        while(!active.empty() && h && active.top().first >= i)
        {
            pii tmp = active.top(); active.pop();
            int tmin = min(h, tmp.second);
            h -= tmin;
            tmp.second -= tmin;
            sweep[i] += tmin;
            sweep[tmp.first+1] -= tmin;
            ans += tmin;
            if(tmp.second)
                active.push(tmp);
        }
        if(h)
        {
            cout << "NO\n";
            return;
        }
    }
    
    cout << "YES " << ans << '\n'; 
    
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
    cin >> Tc;

    forn(i, Tc)
        Solve();

    return 0;
}