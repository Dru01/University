//Las definiciones de funciones templates se hicieron dentro de los headers debido a la incompatibilidad de separarlos de ellos al momento de compilar

#include "geometry.h"
#include <iostream>
#include <fstream>
using namespace std;
#define optimizar_io ios_base::sync_with_stdio(false);cin.tie(NULL)
streambuf *cin_backup = cin.rdbuf(), *cout_backup = cout.rdbuf();
ifstream f_in;
ofstream f_out;

int main(int argc, char *argv[])
{

    f_in.open(string(argv[1]));
    f_out.open(string(argv[2])+".qh");

    CQuick_Hull <double> ch_qh;

    f_in >> ch_qh;

    f_out << ch_qh;

    f_in.close();
    f_out.close();

    f_in.open(string(argv[1]));
    f_out.open(string(argv[2])+".gs");

    CGraham_Scan <double> ch_gs;

    f_in >> ch_gs;

    f_out << ch_gs;

    f_in.close();
    f_out.close();    

    return 0;
}
