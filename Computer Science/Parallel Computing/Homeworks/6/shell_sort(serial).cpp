#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;
 
void shell_sort(int *num, int N)
{
   for(int h = N/2; h; h>>=1)
   {
      for(int k = 0; k < h; k++)
      {
         int v,j;
         for(int i = k; i < N; i+=h)
         {
            v = num[i];
            for(j = i; j >= h && num[j-h] > v; j-=h)
               swap(num[j], num[j-h]);
            num[j] = v;
         }
      }
   }
}

int main()
{
    int N;
    cin >> N;
    int *num = new int[N];
    for(int i = 0; i < N; i++)
       cin >> num[i];

    auto tstart = steady_clock::now();

    shell_sort(num, N);

    auto tend = steady_clock::now();
    auto ttotal = duration_cast<microseconds>(tend - tstart).count();

    cout << ttotal;
    
    return 0;
}