/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar la sub-matriz con mayor area tal que la suma de sus valores no exceda K.

Primero recordemos que podemos usar sumas parciales (por el principio de inclusion-exclusion) para encontrar la suma de los valores
de una submatriz. Ahora para encontrar la respuesta podriamos intentar iterar sobre todas las submatrices calcular su area y su suma.
El problema de esto es que su complejidad es O(N**2 M**2), la cual excede el tiempo límite. Pdemos deshacernos de una de estas si
usamos la técnica sliding window, es decir fijamos 2 coordenadas sobre un eje digamos il, ir (el ancho), y para cada par de ellos con el sliding window
nos estiramos mientras la suma no exceda K, asi maximizamos el largo y por lo tanto el area (para cada il, ir). De esta forma obtenemos la respuesta.

Complejidad

O(T*N**2M). Donde T es la cantidad de casos, y N,M las dimensiones de la matriz.
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>
using namespace std;

#define FILE_STREAM
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

const ll LN = (int)(100+1), LK = (int)(5e3 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll parallelepiped[LN][LN];
ll partial_sum[LN][LN];

ll sum_sub_parallelepiped(int il, int ir, int jl, int jr)
{
    return partial_sum[ir][jr] - partial_sum[il - 1][jr] - partial_sum[ir][jl - 1] + partial_sum[il - 1][jl - 1];
}

int main()
{
    optimizar_io;

    cin >> T;

    for (int t = 0; t < T; t++)
    {
        cin >> N >> M >> K;

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= M; j++)
            {
                cin >> parallelepiped[i][j];
                partial_sum[i][j] = 0;
                partial_sum[i][j] = -sum_sub_parallelepiped(i, i, j, j) + parallelepiped[i][j];
            }
        }

        ll ans = 0, total = 1e18, sum, area, cost;
        ll jl, jr;
        for (ll il = 1; il <= N; il++)
        {
            for (ll ir = il; ir <= N; ir++)
            {
                sum = 0;
                for (ll jl = 1, jr = 1; jl <= M;)
                {
                    while (sum <= K && jr <= M)
                    {
                        sum += sum_sub_parallelepiped(il, ir, jr, jr);
                        jr++;
                    }
                    area = (ir - il + 1) * (jr - jl - (sum > K ? 1 : 0));
                    cost = sum - (sum > K ? sum_sub_parallelepiped(il, ir, jr - 1, jr - 1) : 0);
                    if (ans == area)
                        total = min(total, cost);
                    if (ans < area)
                    {
                        ans = area;
                        total = cost;
                    }
                    while (sum > K && jl <= jr)
                    {
                        sum -= sum_sub_parallelepiped(il, ir, jl, jl);
                        jl++;
                    }
                    area = (ir - il + 1) * (jr - jl - (sum > K ? 1 : 0));
                    cost = sum;
                    if (ans == area)
                        total = min(total, cost);
                    if (ans < area)
                    {
                        ans = area;
                        total = cost;
                    }
                    if (jr == M + 1)
                        break;
                }
            }
        }
    
        cout << "Case #" << t + 1 << ": " << ans << " " << (total == 1e18 ? 0 : total) << "\n";
    }

    return 0;
}