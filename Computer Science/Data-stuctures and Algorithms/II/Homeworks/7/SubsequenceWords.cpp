#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define out_range_map(x,y) ((x) < 0 || (y) < 0 || (x) == N || (y) == M)
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#ifdef FILE_STREAM
streambuf* cin_backup = cin.rdbuf(), * cout_backup = cout.rdbuf();
ifstream f_in("shortcut.in");
ofstream f_out("shortcut.out");
#endif // FILE_STREAM

const ll LN = (int)(1e2 + 1), LK = (int)(5e3 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
string S[3];
ll memo[LN][LN][LN];

ll dp(int pos_0, int pos_1, int pos_2)
{
    if (pos_2 == K)
        return 1;

    if (memo[pos_0][pos_1][pos_2] != -1)
        return memo[pos_0][pos_1][pos_2];

    ll ans = 0;
    for (int i = pos_0; i < N; i++)
        if (S[0][i] == S[2][pos_2])
            ans += dp(i + 1, pos_1, pos_2 + 1);

    for (int i = pos_1; i < M; i++)
        if (S[1][i] == S[2][pos_2])
            ans += dp(pos_0, i + 1, pos_2 + 1);

    return memo[pos_0][pos_1][pos_2] = ans;
}

int main()
{
    optimizar_io;

    cin >> T;

    while (T--)
    {
        fill(memo, -1);
        cin >> S[0] >> S[1] >> S[2];
        N = S[0].size();
        M = S[1].size();
        K = S[2].size();
        cout << dp(0, 0, 0) << "\n";
    }

    return 0;
}