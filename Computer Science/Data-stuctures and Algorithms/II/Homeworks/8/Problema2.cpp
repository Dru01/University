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
int N, M, K, T;
bool undesired[30];

int main()
{
    optimizar_io;

    string word, list_undesired;
    cin >> list_undesired;

    for (auto c : list_undesired)
        undesired[c - 'a'] = true;

    cin >> K;
    cin >> word;

    vector < ll > hash_substring(word.size(), 0);
    vector < int > cont(word.size(), 0);
    const int p = 37;
    const int m = 2000003413;
    ll pi = 1;
    int ans = 0;
    vector < bool > bucket(m);
    for (int size = 0; size < word.size(); size++)
    {
        for (int i = 0; i < word.size() - size; i++)
        {
            cont[i] += undesired[word[i + size] - 'a'];
            hash_substring[i] = (hash_substring[i] + (word[i + size] - 'a' + 1) * pi) % m;
            if (cont[i] <= K && !bucket[hash_substring[i]])
                ans++;
            bucket[hash_substring[i]] = true;
        }
        for (int i = 0; i < word.size() - size; i++)
            bucket[hash_substring[i]] = false;
        pi = (pi * p) % m;
    }

    cout << ans;

    return 0;
}x