/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide encontrar las combinaciones y permutaciones de los puntajes de lanzar tres dardos tal que el total de puntos sea N.

Primero veamos que la cantidad de puntajes posibles es a lo mas 60. Luego iterando sobre todos los posibles puntajes que pueden obtener los tres dardos (i, j, k), y checando si la suma de sus puntajes sea N obtendriamos la cantidad de permutaciones, si por cada vez que encontremos una permutacion marcamos como visitado las 6 permmutaciones de esos 3 puntajes entonces contariamos una vez cada eleccion de puntajes i,j,k, claro preguntando siempre si la elección no fue visitada antes.

Complejidad

O(T*M). Donde T es la cantidad de casos, y M la cantidad de puntajes distintos.
*/
#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>
using namespace std;

#define FILE_STREAM
#define ll long long
#define left(x) (x << 1 | 1)
#define right(x) (left(x) + 1)
#define half (l + r) / 2
#define all(x) (x).begin(), (x).end()
#define fill(x, y) memset(x, y, sizeof(x))
#define out_range_map(x,y) ((x) < 0 || (y) < 0 || (x) == N || (y) == M)
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#ifdef FILE_STREAM
streambuf* cin_backup = cin.rdbuf(), * cout_backup = cout.rdbuf();
ifstream f_in("shortcut.in");
ofstream f_out("shortcut.out");
#endif // FILE_STREAM

const ll LN = (int)(26 + 1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, K, T;
ll dp[LN][LN][LK], partial_sum[LN][LN][LK];
set<int> score_type;
bool taken[61][61][61];
vector<int> score_value;

bool taken_check(int i, int j, int k)
{
    return taken[score_value[i]][score_value[j]][score_value[k]];
}

void taken_set(int i, int j, int k)
{
    taken[score_value[i]][score_value[j]][score_value[k]] = true;
}

int main()
{
    optimizar_io;

    score_type.insert(50);

    for (int i = 0; i <= 20; i++)
    {
        score_type.insert(i);
        score_type.insert(i * 2);
        score_type.insert(i * 3);
    }

    score_value = vector < int >(all(score_type));

    while (cin >> N)
    {
        if (N <= 0)
            break;

        fill(taken, 0);

        int comb = 0, permut = 0;

        for (int i = 0; i < score_value.size(); i++)
        {
            for (int j = 0; j < score_value.size(); j++)
            {
                for (int k = 0; k < score_value.size(); k++)
                {
                    if (score_value[i] + score_value[j] + score_value[k] != N)
                        continue;

                    permut++;
                    if (!taken_check(i,j,k)) 
                    {
                        taken_set(i, j, k);
                        taken_set(i, k, j);
                        taken_set(j, i, k);
                        taken_set(j, k, i);
                        taken_set(k, i, j);
                        taken_set(k, j, i);
                        comb++;
                    }
                }
            }
        }

        if (comb == 0 && permut == 0)
            cout << "THE SCORE OF " << N << " CANNOT BE MADE WITH THREE DARTS.\n";
        else
        {
            cout << "NUMBER OF COMBINATIONS THAT score_type " << N << " IS " << comb << ".\n";
            cout << "NUMBER OF PERMUTATIONS THAT score_type " << N << " IS " << permut << ".\n";
        }

        cout << "**********************************************************************\n";
    }

    cout << "END OF OUTPUT\n";
}