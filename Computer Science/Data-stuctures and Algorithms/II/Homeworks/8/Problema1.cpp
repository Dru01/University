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

int main()
{
    optimizar_io;

    string word;
    cin >> word;

    vector < ll > hash_substring(word.size(), 0);
    const int p = 31;
    const int m = 100000007;
    long long pi = 1;
    short int ans = 0;
    vector < short int > bucket(m);
    for (int size = 0; size < word.size(); size++, pi = (pi * p) % m)
    {
        ans = 0;
        for (int i = 0; i < word.size() - size; i++)
        {
            bucket[(hash_substring[i] + (word[i+size] - 'a' + 1) * pi) % m]++;
            ans = max(ans, bucket[(hash_substring[i] + (word[i+size] - 'a' + 1) * pi) % m]);
        }
        for (int i = 0; i < word.size() - size; i++)
        {
            hash_substring[i] = (hash_substring[i] + (word[i+size] - 'a' + 1) * pi) % m;
            bucket[hash_substring[i]]--;
        }
        if (ans == 1)
            break;
        cout << ans << "\n";
    }

    return 0;
}