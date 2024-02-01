#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
stringstream ans;

template <typename T>
string type_name();

template < typename T >
T solve(T N)
{
    T ans = 1;

    for (int i = 0; i < N; ++i)
    {
        if (i != N - 1)
            ans *= (2 * N - i);
        ans /= (i + 1);
    }

    return ans;
}

//En caso de no existir regresa 0
template < typename T >
T catalan(T N)
{
    T tmax = 0;
    for (; tmax <= 36; tmax++)
        if (solve<unsigned long long >(tmax) > numeric_limits<T>::max())
            break;
    tmax--;
    return (N <= tmax ? solve<T>(N) : 0);
}

int main()
{
    optimizar_io;

    unsigned long long N;

    cin >> N;

    cout << catalan < unsigned long long >(N);

    return 0;
}