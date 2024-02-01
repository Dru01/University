#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
stringstream ans;

string product_digit(ll N)
{
    ans.clear();
    stack < char > digits;

    for (int i = 9; i > 1; i--)
    {
        while (!(N % i))
        {
            N /= i;
            digits.push((char)(i + '0'));
        }
    }

    if (N != 1)
        return "-1";

    if (digits.size() == 1)
        digits.push('1');

    while (!digits.empty())
    {
        ans << digits.top();
        digits.pop();
    }

    return ans.str();
}

int main()
{
    optimizar_io;

    ll N;

    cin >> N;

    cout << product_digit(N);

    return 0;
}