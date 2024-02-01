#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;
 
void bubble_sort(int *num, int N)
{
   int i, j;
   bool swapped;
   for (i = 0; i < N-1; i++)
   {
     swapped = false;
     for (j = 0; j < N-i-1; j++)
     {
        if (num[j] > num[j+1])
        {
           swap(num[j], num[j+1]);
           swapped = true;
        }
     }
     if (swapped == false)
        break;
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

    bubble_sort(num, N);

    auto tend = steady_clock::now();
    auto ttotal = duration_cast<microseconds>(tend - tstart).count();

    cout << ttotal;
    
    return 0;
}