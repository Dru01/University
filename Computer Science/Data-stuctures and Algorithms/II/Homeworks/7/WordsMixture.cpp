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

const ll LN = (int)(1e4 + 1), LK = (int)(5e3 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, T;
string S[3];
bool memo[LN][LN];

bool dp(int pos_0, int pos_1)
{
    if (pos_0 == N + M)
        return true;

    if (memo[pos_0][pos_1])
        return true;

    int ans = 0;
    if (pos_1 < N && S[0][pos_1] == S[2][pos_0])
        ans |= dp(pos_0 + 1, pos_1 + 1);
    if (pos_0-pos_1 < M && S[1][pos_0-pos_1] == S[2][pos_0])
        ans |= dp(pos_0 + 1, pos_1);

    return memo[pos_0][pos_1] = ans;
}

int main()
{
    optimizar_io;

    cin >> T;
    
    while (T--)
    {
        fill(memo, 0);
        cin >> S[0] >> S[1] >> S[2];
        N = S[0].size();
        M = S[1].size();
        cout << (N + M == S[2].size() ? dp(0, 0) : 0) << "\n";
    }

    return 0;
}