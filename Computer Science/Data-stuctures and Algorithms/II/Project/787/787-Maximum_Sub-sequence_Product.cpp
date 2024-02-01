/*
Ruben Perez Palacios
ruben.perez@cimat.mx

Solucion:

El problema pide el producto maximo de todos los subarreglos de un arreglo $a$.

Para ello llevamos tanto el producto maximo y minimo (puesto que hay numeros negativos) hasta la posicion i.
Cuando actualizamos para la posicion i+1, calculamos max*a[i+1] y min*a[i+1], actualizamos con estos valores y a[i+1] nuestro maximo y minimo.
En todo momento vamos actualizando nuestra respuesta.

Puesto que el producto de los números puede ser muy grande ¡10**600! Entonces debemos representar con strings a estos números e implementar
el producto de ellos así como las funciones max y min de dos de estos números.

Complejidad:

O(T*N*C*C). Donde T es la cantidad de casos, N es la cantidad de elementos del arreglo, C la cantidad de dígitos máxima del producto.
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

const ll LN = (int)(1e4 + 1), LK = (int)(5e3 + 1), INF = (ll)(1e9), MOD = 1000000007;
int N, M, T;

string big_num_prod(const string& lhs, const string& rhs)
{
    int N_lhs = lhs.size();
    int N_rhs = rhs.size();
    if (N_lhs == 0 || N_rhs == 0)
        return "0";

    bool negativity_lhs = (lhs[0] == '-');
    bool negativity_rhs = (rhs[0] == '-');

    vector<int> ans(N_lhs + N_rhs, 0);

    int i_n1 = 0;
    int i_n2 = 0;

    for (int i = N_lhs - 1; i >= negativity_lhs; i--)
    {
        int carry = 0;
        int n1 = lhs[i] - '0';

        i_n2 = 0;

        for (int j = N_rhs - 1; j >= negativity_rhs; j--)
        {
            int n2 = rhs[j] - '0';

            int sum = n1 * n2 + ans[i_n1 + i_n2] + carry;

            carry = sum / 10;

            ans[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        if (carry > 0)
            ans[i_n1 + i_n2] += carry;

        i_n1++;
    }

    int i = ans.size() - 1;
    while (i >= 0 && ans[i] == 0)
        i--;

    if (i == -1)
        return "0";


    string s = "";

    while (i >= 0)
        s += to_string(ans[i--]);

    return (negativity_lhs != negativity_rhs ? "-" : "") + s;
}

string big_num_max(const string& lhs, const string& rhs)
{
    int N_lhs = lhs.size();
    int N_rhs = rhs.size();
    if (N_lhs == 0 || N_rhs == 0)
        return "0";

    bool negativity_lhs = (lhs[0] == '-');
    bool negativity_rhs = (rhs[0] == '-');

    if (negativity_lhs != negativity_rhs)
        return (negativity_lhs ? rhs : lhs);

    if (N_lhs != N_rhs)
        if (!negativity_lhs)
            return ((N_lhs > N_rhs) ? lhs : rhs);
        else
            return (!(N_lhs > N_rhs) ? lhs : rhs);

    for (int i = negativity_lhs; i < N_lhs; i++)
        if (lhs[i] != rhs[i])
            if(!negativity_lhs)
                return ((lhs[i] > rhs[i]) ? lhs : rhs);
            else
                return (!(lhs[i] > rhs[i]) ? lhs : rhs);

    return lhs;
}

string big_num_min(const string& lhs, const string& rhs)
{
    int N_lhs = lhs.size();
    int N_rhs = rhs.size();
    if (N_lhs == 0 || N_rhs == 0)
        return "0";

    bool negativity_lhs = (lhs[0] == '-');
    bool negativity_rhs = (rhs[0] == '-');

    if (negativity_lhs != negativity_rhs)
        return (!negativity_lhs ? rhs : lhs);

    if (N_lhs != N_rhs)
        if (!negativity_lhs)
            return (!(N_lhs > N_rhs) ? lhs : rhs);
        else
            return ((N_lhs > N_rhs) ? lhs : rhs);

    for (int i = negativity_lhs; i < N_lhs; i++)
        if (lhs[i] != rhs[i])
            if (!negativity_lhs)
                return (!(lhs[i] > rhs[i]) ? lhs : rhs);
            else
                return ((lhs[i] > rhs[i]) ? lhs : rhs);

    return lhs;
}

int main()
{
    optimizar_io;

    string num, ans, prod_max, prod_min;

    while (cin >> num)
    {
        
        ans = prod_max = prod_min = num;
        while (num != "-999999")
        {
            cin >> num;
            if (num != "-999999")
            {
                string temp = big_num_max(num, big_num_max(big_num_prod(num , prod_max), big_num_prod(num, prod_min)));
                prod_min = big_num_min(num, big_num_min(big_num_prod(num, prod_max), big_num_prod(num, prod_min)));
                prod_max = temp;
                ans = big_num_max(ans, prod_max);
            }
        }
        cout << ans << "\n";
    }

    return 0;
}