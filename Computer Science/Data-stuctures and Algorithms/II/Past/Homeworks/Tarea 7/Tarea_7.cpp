#include <bits/stdc++.h>
using namespace std;

#define left(x) (x << 1 | 1)
#define right(x) (left(x) + 1)
#define half ((l+r) >> 1)
#define fill(x, y) memset(x, y, sizeof(x))
#define ll long long
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)

const int LN = 102, LK = 101, LT = 1e6 + 1;

ll dp[LN][10][1 << 10];
int N, M, T, visit[LN][10][1 << 10];

ll call(int i, int j, int mask)
{
    if (i == N)
        return mask == 0;
    if (j == M)
        return call(i + 1, 0, mask);

    if (visit[i][j][mask] == T)
        return dp[i][j][mask];

    visit[i][j][mask] = T;
    ll ans = 0;

    if (mask & (1 << j))
        return dp[i][j][mask] = call(i, j + 1, mask & (~(1 << j)));

    ans = call(i, j + 1, mask | (1 << j));
    if (j + 1 < M && !(mask & (1 << (j + 1))))
        ans += call(i, j + 2, mask);

    return dp[i][j][mask] = ans;
}

int main()
{
    while (cin >> N >> M)
    {
        T++;
        if (N < M)
            swap(N, M);
        cout << call(0, 0, 0) << "\n";
    }

    return 0;
}