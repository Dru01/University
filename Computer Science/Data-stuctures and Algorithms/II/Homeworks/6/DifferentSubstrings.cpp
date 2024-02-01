#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define all(x) x.begin(),x.end()

void prefix_function(string &word, vector < int > &lps);

//Funcion que devuelve la cantidad de subcadenas distintas de una palabra
int KMPSearch(string word)
{
    int N = word.size();
    vector < int > lps(N);
    string t = "";
    int ans = 0;
    
    //Calculo
    for (int i = 0; i < N; i++)
    {
        //sufijo actual
        t += word[i];
        //Invertir para aprovechar el lsp y no tener que implementar un lps
        reverse(all(t));
        prefix_function(t, lps);
        //Nuevas cadenas para el prefijo t
        ans += i + 1 - *max_element(all(lps));
        //Regresar al prefijo
        reverse(t.begin(), t.end());
    }

    return ans;
}

//Devuelve un arreglo, en el cual la posicion i representa el tamano del sufijo propio mas grande que tambien es un prefijo de la subcadena word[0...i]
void prefix_function(string &word, vector < int > &lps) {
    
    int N = (int)word.length();
    
    //Calculo
    for (int i = 1; i < N; i++) {
		//Primer intento
        int j = lps[i - 1];
		//Encontrar el prefijo propio mas grande que tambien sea sufijo y tenga como ultima letra word[i]
        while (j > 0 && word[i] != word[j])
            j = lps[j - 1];
		//Verificar que haya coincidido la ultima letra
        if (word[i] == word[j])
            j++;
		//Guardar el resultado
        lps[i] = j;
    }
}

int main()
{
    string word;
    cin >> word;
    cout << KMPSearch(word);
    return 0;
}