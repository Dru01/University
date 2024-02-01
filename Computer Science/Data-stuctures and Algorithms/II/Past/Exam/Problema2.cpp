#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
stringstream ans;

int lps(string S)
{
    int N = S.size();
    vector < int > memo(N);
    int temp;

    for (int i = N - 1; i >= 0; i--)
    {
        temp = 0;

        for (int j = i; j < N; j++)
        {
            if (j == i)
                memo[j] = 1;
            else if (S[i] == S[j])
            {
                swap(memo[j], temp);
                memo[j] += 2;
            }
            else
            {
                temp = memo[j];
                memo[j] = max(memo[j - 1], memo[j]);
            }
        }
    }

    return memo[N - 1];
}

int main()
{
    optimizar_io;

    string S;

    cin >> S;

    cout << lps(S);

    return 0;
}