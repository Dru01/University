#include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string>
#include <filesystem>
#include <omp.h>

using namespace std;

#define all(x) x.begin(),x.end()

class CRS
{
public:
    int N, M;
    vector < vector < int > > indexJ;
    vector < vector < double > > vals;
    vector < double > diag;

    void fill_from_sparse(int N, int M, int nonzero, double* vals, double* indexI, double* indexJ)
    {
        this->N = N;
        this->M = M;
        this->indexJ.resize(N);
        this->vals.resize(N);
        diag.resize(N);

        for (int k = 0; k < nonzero - 1; k++)
        {
            this->indexJ[indexI[k] - 1].push_back(indexJ[k] - 1);
            this->vals[indexI[k] - 1].push_back(vals[k]);
            if (indexI[k] == indexJ[k])
                diag[indexI[k]-1] = vals[k];
        }
    }
};

void to_vector(int N, double* arr, vector < double >& vec)
{
    vec.resize(N);
    for (int i = 0; i < N; i++)
        vec[i] = arr[i];
}

void read_system_eq(const char* filename, CRS& A, vector < double >& b, vector < double >& x)
{
    FILE* file = fopen(filename, "rb");

    int header[5], format, temp, name_size;
    char name[100];

    fread(header, sizeof(int), 5, file);
    format = header[0] % 10;
    temp = header[0] - format;

    int N, M, nonzero;
    double* indexI, * indexJ, * vals, * tb, * tx;

    nonzero = header[1];
    name_size = header[4];
    fread(name, name_size, 1, file);

    indexI = new double[nonzero - 1];
    fread(indexI, sizeof(double), nonzero - 1, file);
    double NN;
    fread(&NN, sizeof(double), 1, file);

    indexJ = new double[nonzero - 1];
    fread(indexJ, sizeof(double), nonzero - 1, file);
    double MM;
    fread(&MM, sizeof(double), 1, file);

    vals = new double[nonzero - 1];;
    fread(vals, sizeof(double), nonzero - 1, file);
    double temp1;
    fread(&temp1, sizeof(double), 1, file);

    N = NN;
    M = MM;

    A.fill_from_sparse(N, M, nonzero, vals, indexI, indexJ);

    fread(header, sizeof(int), 5, file);
    name_size = header[4];
    fread(name, name_size, 1, file);
    tb = new double[N];
    fread(tb, sizeof(double), N, file);
    to_vector(N, tb, b);

    fread(header, sizeof(int), 5, file);
    name_size = header[4];
    fread(name, name_size, 1, file);
    tx = new double[M];
    fread(tx, sizeof(double), M, file);
    to_vector(M, tx, x);

    fclose(file);

}

void procesor_range( const int rank, const int nprocs, const int N, int& tl, int& tr )
{
    int count = N / nprocs;
    int remainder = N % nprocs;

    if (rank < remainder)
    {
        tl = rank * (count + 1);
        tr = tl + count;
    }
    else
    {
        tl = rank * count + remainder;
        tr = tl + count - 1;
    }
    return;
}

double dot_prod( const int rank, const int nprocs, const vector < double > & a, const vector < double >& b )
{
    const int N = a.size();
    int tl, tr;
    double local_sum = 0.0, sum = 0.0;
    procesor_range(rank, nprocs, N, tl, tr);

    for (int i = tl; i <= tr; i++)
        local_sum += a[i] * b[i];

    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    return sum;
}

vector < double > mat_vec_prod( const int rank, const int nprocs, const CRS& A, const vector < double >& x )
{
    const int N = A.N;
    int tl, tr, tsize;
    MPI_Status status;

    procesor_range(rank, nprocs, N, tl, tr);
    tsize = tr - tl + 1;

    vector < double > ans(N);
    for (int i = tl; i <= tr; i++)
        for (int j = 0; j < A.indexJ[i].size(); j++)
            ans[i] += A.vals[i][j] * x[(int)A.indexJ[i][j]];

    if (rank == 0)
    {
        for (int i = 1; i < nprocs; i++)
        {
            int local_tl, local_sz;
            MPI_Recv(&local_tl, 1, MPI_INT, i, 101, MPI_COMM_WORLD, &status);
            MPI_Recv(&local_sz, 1, MPI_INT, i, 102, MPI_COMM_WORLD, &status);
            MPI_Recv(&ans[local_tl], local_sz, MPI_DOUBLE, i, 103, MPI_COMM_WORLD, &status);
        }
    }
    else
    {
        MPI_Send(&tl, 1, MPI_INT, 0, 101, MPI_COMM_WORLD);
        MPI_Send(&tsize, 1, MPI_INT, 0, 102, MPI_COMM_WORLD);
        MPI_Send(&ans[tl], tsize, MPI_DOUBLE, 0, 103, MPI_COMM_WORLD);
    }

    return ans;
}

int main(int argc, char *argv[])
{
    
    const char* filename = argv[1];
    CRS A;
    vector < double > x;
    vector < double > b;
    read_system_eq(filename, A, b, x);

    MPI_Init(&argc, &argv);

    int processCount, processId;
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);

    double xb = dot_prod(processId, processCount, x, b);
    if (processId == 0)
        cout << "xb = " << xb << '\n';
    
    vector < double > Ab = mat_vec_prod(processId, processCount, A, b);
    if (processId == 0)
    {
        cout << "Ab = (";
        for (int i = 0; i < A.N; i++) 
            cout << Ab[i] << ( (i < A.N - 1) ? ", " : ")\n" );
    }

    MPI_Finalize();

    return 0;
}