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

    CBO<double> cbo{vector < CLine_Segment < double > >()};

    f_in.close();
    f_out.close();

    return 0;
}
