#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
#include <omp.h>
using namespace std;
using namespace chrono;

int i, j, n;
int Nx, Ny, Nt;
float kx, ky;
float xI, xF, yI, yF;
float tF, tI;
float Dx, Dy, Dt;

vector < float > x;
vector < float > y;
vector < vector < float > > Uold;
vector < vector < float > > Unew;

float rx, ry;
float aC, aN, aS, aE, aW;

float suma;

int main()
{
    //**************
    //INICIALIZACION
    //**************

    //__________
    //Parametros
    kx = 1.0;        //Termino difusivo en x
    ky = 1.0;        //Termino difusivo en y

    xI = 0.0;        //Inicio del dominio en x
    xF = 1.0;        //Fin del dominio en x
    yI = 0.0;        //Inicio del dominio en y
    yF = 1.0;        //Fin del dominio en y

    tI = 0.0;        //Tiempo inicial
    tF = 0.5;        //Tiempo final

    Nt = 100000;     //Numero de divisiones en el tiempo
    Nx = 200;        //Numero de divisiones en x
    Ny = 200;        //Numero de divisiones en y

    //______________
    //Discretización
    Dx = (xF - xI) / (Nx - 1);
    Dy = (yF - yI) / (Ny - 1);
    Dt = (tF - tI) / (Nt - 1);
    rx = kx * (Dt / (Dx * Dx));
    ry = ky * (Dt / (Dy * Dy));

    //--------
    //Imprimir
    cout << "(Nx,Ny)=" << "(" << Nx << ", " << Ny << ")\n";
    cout << "Criterio CFL < 1/2 :" << rx + ry << "\n";

    //******
    //MALLAS
    //******

    x.resize(Nx + 1);
    y.resize(Ny + 1);

    for (int i = 1; i <= Nx; i++)
        x[i] = xI + (i - 1) * Dx;
    for (int j = 1; j <= Nx; j++)
        y[j] = yI + (j - 1) * Dy;

    //******************
    //PROGRAMA PRINCIPAL
    //******************

    auto start_time = steady_clock::now();

    //__________________________
    //Condiciones en la solución

    Uold.resize(Nx + 1);
    for (int i = 1; i <= Nx; i++)
        Uold[i].resize(Ny + 1);
    Unew.resize(Nx + 1);
    for (int i = 1; i <= Nx; i++)
        Unew[i].resize(Ny + 1);

    //---------------------
    //Condiciones iniciales
    for (int i = 1; i <= Nx; i++)
        for (int j = 1; j <= Ny; j++)
            Uold[i][j] = sin(x[i] + y[j]) * sin(x[i] + y[j]);
    Unew = Uold;

    //-----------------------
    //Condiciones de frontera
    for (int j = 1; j <= Ny; j++)
    {
        Unew[1][j] = 1.0;  //Oeste
        Unew[Nx][j] = 1.0;  //Este
    }
    for (int i = 1; i <= Nx; i++)
    {
        Unew[i][1] = 1.0;  //Oeste
        Unew[i][Ny] = 1.0;  //Este
    }

    //_________________________________
    //Calculos en los puntos interiores
    for (int n = 1; n <= Nt; n++)
    {
        //--------------
        //Nuevos valores
        for (int i = 2; i < Nx; i++)
        {
            for (int j = 2; j < Ny; j++)
            {
                aC = 1 - 2.0 * (rx + ry);
                aE = rx;
                aW = rx;
                aS = ry;
                aN = ry;
                Unew[i][j] = aC * Uold[i][j] + aW * Uold[i - 1][j] + aE * Uold[i + 1][j] + aS * Uold[i][j - 1] + aN * Uold[i][j + 1];
            }
        }
        //--------------
        //Actualizacion
        Uold = Unew;
    }

    auto end_time = steady_clock::now();

    //********************
    //VERIFICAR RESULTADOS
    //********************

    //_____________________________________________
    //Imprimir suma de los elementos para verificar
    suma = 0.0;
    for (int i = 1; i <= Nx; i++)
    {
        for (int j = 1; j <= Ny; j++)
        {
            suma = suma + Unew[i][j];
        }
    }
    //--------
    //IMPRIMIR
    cout << "Suma total = " << suma << "\n";

    //____________
    //Tiempo final
    auto total_time = duration_cast<microseconds>(end_time - start_time).count();

    //--------
    //IMPRIMIR
    cout << "tiempo = " << total_time / 1000000;

    return 0;
}