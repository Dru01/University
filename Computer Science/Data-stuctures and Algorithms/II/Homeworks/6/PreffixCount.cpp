#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <algorithm>

using namespace std;

#define all(x) x.begin(),x.end()

void prefix_function(string &word, vector < int > &lps);

void KMPSearch(string word)
{
    int N = word.size();
    vector < int > lps(N);
    prefix_function(word, lps);
    
    int tsize = N;
    string tword = word;
    vector < int > ans(N+1);

    //Precalculo apariciones prefijos
    //Agregar los prefijos propios mas grande que son sufijos que terminan en i
    for (int i = 0; i < N; i++)
        ans[lps[i]]++;
    //Agregar el siguiente prefijo propio mas grande que es sufijo y termina en i, y acumular
    for (int i = N - 1; i > 0; i--)
        ans[lps[i - 1]] += ans[i];
    //Agregar la aparicion de los prefijos perse
    for (int i = 0; i <= N; i++)
        ans[i]++;

    stack < string > toutput;
    stringstream temp;
    
    while (tsize)
    {
        //Codigo para imprimir en orden creciente
        temp << tword << " " << ans[tsize] << "\n";
        toutput.push(temp.str());
        temp.str("");
        temp.clear();
        //Encontrar el siguiente prefijo propio mas grande que es sufijo de w
        while (tword.size() > lps[tsize-1])
            tword.pop_back();
        //Actualizar el tamaño
        tsize = lps[tsize - 1];
    }

    //Impresion
    while (!toutput.empty())
    {
        cout << toutput.top();
        toutput.pop();
    }

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
    KMPSearch(word);
    return 0;
}