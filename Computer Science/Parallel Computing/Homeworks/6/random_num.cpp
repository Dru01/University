#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{

    int N, A, B;
    
    cin >> N >> A >> B;
    vector < int >  num(N);

    srand(time(NULL));

    auto tstart = steady_clock::now();
    
    for (int i = 0; i < N; i++)
        num[i] = ((double)rand() / RAND_MAX) * (B - A) + A;

    auto tend = steady_clock::now();
    auto ttotal = duration_cast<microseconds>(tend - tstart).count();

    cout << N << "\n";
    for (int i = 0; i < N; i++)
        cout << num[i] << " ";

    return 0;
}