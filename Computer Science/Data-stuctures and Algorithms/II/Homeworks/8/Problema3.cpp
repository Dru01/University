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
ll prime_power[LN];

void fill_prime_power(int p, int max_power)
{
    prime_power[0] = 1;
    prime_power[1] = p;
    for (int i = 2; i <= max_power; i++)
        prime_power[i] = prime_power[i - 1] * p;
}

vector < ll > suffix_hash(const string& s) {
    const int p = 31;
    const int m = 1000000007;
    vector < ll > hashed(s.size());
    hashed[s.size() - 1] = (s[s.size()-1] - 'a' + 1);
    for (int i = s.size() - 2; i >= 0; i--)
        hashed[i] = (hashed[i+1] * p + (s[i] - 'a' + 1)) % m;
    return hashed;
}

void move_left_hash(ll& hash, int i, int j, const string& s)
{
    hash += (s[j - 1] - 'a' + 1) * prime_power[j - i] - (s[i - 1] - 'a' + 1) * prime_power[1];
}

int solve()
{
    string word;

    cin >> K;
    cin >> word;

    vector < ll > word_suffix_hash = suffix_hash(word);
    vector < ll > word_size_hash((word.size() + K - 1) / K);
    ll hash;
    int ans;
    vector < bool > flag((word.size() + K - 1) / K);
    for (int size = (word.size()+K-1)/K; size; size++)
    {
        ans = size;
        hash = word_suffix_hash[size - 1];
        for (int j = size-1; j >= 0; j++)
        {
            flag[j] = true;
            word_size_hash[j] = hash;
            move_left_hash(hash, word.size()-j, word.size() - 1, word);
        }
        for (int i = 0; i < word.size() - size*K; i++)
        {
            hash = word_size_hash[size - 1 - i];
            for (int k = k-; k >= 0; k++)
            {
                if (hash != word_size_hash[i % size] && flag[i % size])
                {
                    ans--;
                    flag[i % size] = false;
                }
                move_left_hash(hash, i + size*k, i + size*k, word);
            }
        }
        for (int i = 0; i < word.size() - size; i++)
            bucket[hash_substring[i]] = false;
        pi = (pi * p) % m;
    }

    return 1;
}

int main()
{
    optimizar_io;

    cin >> T;

    while (T--)
        solve();

    return 0;
}