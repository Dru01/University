#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

void OddEvenSort(int *num, int N)
{

    int exch = 1, start = 0, i;
    int temp;

    while (exch || start)
    {
       exch = 0; 

       #pragma omp parallel for private(temp) shared(start, exch)
       for (i = start; i < N-1; i += 2) {
           if (num[i] > num[i+1]) {
             temp = num[i]; 
             num[i] = num[i+1]; 
             num[i+1] = temp;
             exch = 1;
           }
       }

       if (start == 0) start = 1;
       else start = 0;
    }
}
 
int main()
{
    omp_set_num_threads(4);
    
    int N;
    cin >> N;
    int *num = new int[N];
    for(int i = 0; i < N; i++)
        cin >> num[i];

    auto tstart = steady_clock::now();

    OddEvenSort(num, N);

    auto tend = steady_clock::now();
    auto ttotal = duration_cast<microseconds>(tend - tstart).count();

    cout << ttotal;

    return (0);
}