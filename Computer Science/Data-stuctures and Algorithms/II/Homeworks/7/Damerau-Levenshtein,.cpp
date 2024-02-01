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
string S[2];
short int memo[LN][LN];
short int visited[LN][LN];
char ant[LN][LN];

short int dp(int pos_0, int pos_1)
{
    if (pos_1 == M && pos_0 == N)
        return 0;

    if (visited[pos_0][pos_1] == T + 1)
        return memo[pos_0][pos_1];

    short int ans = SHRT_MAX, operation;
    if (pos_0 < N && pos_1 < M)
    {
        operation = dp(pos_0 + 1, pos_1 + 1);
        if ((S[0][pos_0] != S[1][pos_1]) + operation < ans)
        {
            ans = (S[0][pos_0] != S[1][pos_1]) + operation;
            ant[pos_0][pos_1] = (S[0][pos_0] != S[1][pos_1] ? 'S' : 'I');
        }
    }
    if (pos_1 < M)
    {
        operation = dp(pos_0, pos_1 + 1);
        if (operation + 1 < ans)
        {
            ans = 1 + operation;
            ant[pos_0][pos_1] = 'A';
        }
    }
    if (pos_0 < N)
    {
        operation = dp(pos_0 + 1, pos_1);
        if (operation + 1 < ans)
        {
            ans = 1 + operation;
            ant[pos_0][pos_1] = 'E';
        }
    }
    if (pos_0 < N - 1 && pos_1 < M - 1 && S[0][pos_0 + 1] == S[1][pos_1] && S[0][pos_0] == S[1][pos_1 + 1])
    {
        operation = dp(pos_0 + 2, pos_1 + 2);
        if (operation + 1 < ans)
        {
            ans = 1 + operation;
            ant[pos_0][pos_1] = 'T';
        }
    }
    visited[pos_0][pos_1] = T + 1;
    return memo[pos_0][pos_1] = ans;
}

int main()
{
    optimizar_io;

    cin >> T;
    
    int pos_0, pos_1;
    while (T--)
    {
        cin >> S[0] >> S[1];
        N = S[0].size();
        M = S[1].size();
        cout << dp(0, 0) << "\n";
        pos_0 = pos_1 = 0;
        while (pos_0 < N || pos_1 < M)
        {
            cout << ant[pos_0][pos_1];
            //cout << ant[pos_0][pos_1] << " " << pos_0 << " " << pos_1 << "\n";
            if (ant[pos_0][pos_1] == 'I' || ant[pos_0][pos_1] == 'S')
                pos_0++, pos_1++;
            else if (ant[pos_0][pos_1] == 'A')
                pos_1++;
            else if (ant[pos_0][pos_1] == 'E')
                pos_0++;
            else
                pos_0 += 2, pos_1 += 2;
        }
        cout << "\n";
    }

    return 0;
}