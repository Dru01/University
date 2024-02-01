#include "geometry.h"
using namespace std;

int main()
{
    //1) Deberas agregar en la última linea de cada uno de los source el tipo de dato que quieras instanciar de CConvex_Hull ahorita esta int.
    //2) Se puedo utilizar un tipo de dato propio para la CConvex_Hull deberá cumplir que sea un campo ese tipo de dato (tricotomia, adición, etc...).
    //3) Para agregar el tipo de dato deberas incluir el archivo de declaración en cada uno de los archivos de Source y seguir el paso 1).
    //El relajo de los puntos anteriores es debido a la encapsulación y abstracción de las clases para mayor entendimiento
    vector < CPoint < int > > a(4);
    a[1].x = 1;
    a[1].y = 1;
    a[2].x = 3;
    a[2].y = 1;
    a[3].x = 3;
    a[3].y = 3;
    a[0].x = 1;
    a[0].y = 3;

    CConvex_Hull < int > CH(a);
    CH.imp();

    a.push_back({ 2,4 });
    CConvex_Hull < int > CH1(a);
    CH1.imp();

    a.push_back({ 2,2 });
    CConvex_Hull < int > CH2(a);
    CH2.imp();


    return 0;
}
