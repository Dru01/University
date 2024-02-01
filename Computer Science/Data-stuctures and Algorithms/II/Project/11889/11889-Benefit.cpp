/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema nos da dos enteros A y C, y nos pide encontrar el mínimo B tal que LCM(A,B) = C.

Primero notemos que si A no divide a C entonces C no puede ser un LCM de A, esto por definición. Ahora fijemonos en un primo p que divide a A y por lo tanto a C. Ahora sea pf_A y pf_C las potencias maximas de p tal que esta divide a A y C respectivamente, tenemos dos casos el primero es cuando pf_A==pf_C en este caso no importa quien sea B, p**pf_A|LCM(A,B), caso contrario si pf_C>pf_A (porque puede ser que pf_C>pf_B y entonces p**pf_C no divida a LCM(A,B) y por lo tanto LCM(A,B) no sería C). Entonces si pf_C>pf_A p**pf_C|B. recorriendo sobre todos los p, y multiplicando todos los p**pf_C (cuando pf_C>pf_A) obtenemos un BB. Sabemos que por lo dicho anteriormente BB|B el cual es el que buscamos pero también sabemos que por construcción C|lCM(A,B) y LCM(A,B)|C, por lo tanto BB es el B que buscamos.

Precalculamos con una criba los primos menores o iguales a la raiz del entero maximo que nos puedan dar. Y hacemos el proceso dicho anteriormente.

Complejidad

O(T*sqrt(C)). Donde T es el numero de casos y C el entero que nos dan.
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

const ll LN = (int)(5e4 + 1), LK = (int)(351 + 1), INF = (ll)(1e9), MOD = 1000000007;
ll N, M, K, T;
bool is_prime[LN];
vector < int > prime;

void sieve_eratosthenes(ll N)
{
    is_prime[0] = is_prime[1] = false;
    fill(is_prime, 1);
    for (ll p = 2; p <= N; p++) {
        if (is_prime[p])
        {
            for (ll num = p * p; num <= N; num += p)
                is_prime[num] = false;
            prime.push_back(p);
        }
    }
}

ll B(ll A, ll C)
{
    ll ans = 1;
    for (auto p : prime)
    {
        if (C % p)
            continue;
        if (p * p > C)
            break;
        ll pf_A = 1, pf_C = 1;
        while (!(A % p))
        {
            pf_A *= p;
            A /= p;
        }
        while (!(C % p))
        {
            pf_C *= p;
            C /= p;
        }
        if (pf_C > pf_A)
            ans *= pf_C;
    }
    if (C != 1 && A == 1)
        ans *= C;
    return ans;
}

int main()
{
    optimizar_io;

    sieve_eratosthenes(LN - 10);

    cin >> T;

    ll A, C;
    while (T--)
    {
        cin >> A >> C;
        if (C % A)
            cout << "NO SOLUTION";
        else
            cout << B(A, C);
        cout << "\n";
    }
}