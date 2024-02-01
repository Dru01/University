#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <algorithm>

using namespace std;

#define all(x) x.begin(),x.end()

void prefix_function(string &word, vector < int > &lps);

void KMPSearch(string word, string phrase)
{
    int N = word.size();
    int M = phrase.size();
    vector < int > lps(N);
    prefix_function(word, lps);
    
    stack < int > toutput;

    int ans, i, j;

    //Recorrer todos los shifts, y econtrar el número de ocurrencias de word con c-shifts en phrase
    for (int c = 25; c >= 0; c--)
    {
        ans = i = j = 0;
        while (i < M) {
            //Comparar actual caracter simulando c-shifts
            if (phrase[i] == (((word[j] - 'a') + c) % 26 + 'a'))
            {
                j++;
                i++;
            }
            //Verficar si hay coincidencia
            if (j == N)
            {
                ans++;
                j = lps[j - 1];
            }
            else if (i < M && phrase[i] != (((word[j] - 'a') + c) % 26 + 'a'))
            {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i++;
            }
        }
        //Guardar si exactamente hubo una coincidencia
        if (ans == 1)
            toutput.push(c);
    }

    //Imprimir resultados
    cout << toutput.size();

    while (!toutput.empty())
    {
        cout << " " << toutput.top();
        toutput.pop();
    }

    cout << "\n";
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
    int T;
    string word, phrase;

    cin >> T;
    while (T--)
    {
        cin >> word >> phrase;
        KMPSearch(word, phrase);
    }

    return 0;
}