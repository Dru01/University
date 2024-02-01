#include <iostream>
#include <bitset>
#include <fstream>
#include <string.h>
#include <set>
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
ll N, M, K, T;
ll m = 1000000007;
ll p[LN];
ll memo[LN][LN];

int respuesta(std::string& word) {
    int N = word.size();
    for (int i = (N + (K - 1)) / K; i >= 1; i--)
    {
        for (int j = 0; j <= N - i * K; j++)
        {
            for (int l = 0; l < K - 1; l++)
            {
                if (memo[j + l * i][j + (l + 1) * i - 1] != memo[j + (l + 1) * i][j + (l + 2) * i - 1])
                    break;
                if (l == K - 2)
                    return i * K;
            }
        }
    }
    return 0;
}

ll ans(int K)
{
    for (int i = (N + (K - 1)) / K; i >= 1; i--)
    {
        for (int j = 0; j <= N - i * K; j++)
        {
            for (int l = 0; l < K - 1; l++)
            {
                if (memo[j + l * i][j + (l + 1) * i - 1] != memo[j + (l + 1) * i][j + (l + 2) * i - 1])
                    break;
                if (l == K - 2)
                    return i * K;
            }
        }
    }
    return 0;
}

int main()
{
    optimizar_io;

    string word;
    cin >> word;
    N = word.size();

    ll prime = 33;
    M = 1e9 + 7;

    p[0] = 1;
    for (int i = 1; i < N+3; i++)
        p[i] = p[i - 1] * prime;

    memo[N - 1][N - 1] = (word[N - 1] - 'A' + 1) % m;
    for (int i = N - 2; i >= 0; i--)
        memo[i][N - 1] = (memo[i + 1][N - 1] * p[1] + (word[i] - 'A' + 1)) % m;

    for (int j = N - 1; j > 0; j--)
        for (int i = j; i > 0; i--)
            memo[i - 1][j - 1] = ((word[i - 1] - 'A' + 1) + p[1] * (memo[i][j] - (word[j] - 'A' + 1) * p[j - i])) % m;

    cout << N << " ";
    for(int i = 2; i <= N; i++)
        cout << ans(i) << " ";

    return 0;
}