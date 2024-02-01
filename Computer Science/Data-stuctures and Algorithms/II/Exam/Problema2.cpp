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

string min_circ_pemutation(string word)
{
    N = word.size();
    vector < bool > circular_permutation(N,1);
    char c, tmin;
    int tpos, curr_pos, ans = N;
    for (int i = 0; i < N; i++)
    {
        tmin = 'z' + 1;
        for (int j = 0; j < N; j++)
        {
            curr_pos = (i + j) % N;
            if (circular_permutation[j] && word[curr_pos] < tmin)
                tmin = word[curr_pos], tpos = curr_pos - i;
        }
        for (int j = 0; j < N; j++)
        {
            curr_pos = (i + j) % N;
            if (word[curr_pos] != tmin && circular_permutation[j])
                circular_permutation[j] = false, ans--;
        }
        if (ans == 1)
        {
            return word.substr(tpos, N - tpos) + word.substr(0, tpos);
        }
    }
}

int main()
{
    optimizar_io;

    string word;

    cin >> word;

    cout << min_circ_pemutation(word);

    return 0;
}