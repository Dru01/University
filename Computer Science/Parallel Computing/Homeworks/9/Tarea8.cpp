#include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string>
#include <filesystem>
#include <omp.h>
#include <fstream>

using namespace std;

#define all(x) x.begin(),x.end()

class CRS
{
public:
    int N, M;
    vector < vector < int > > indexJ;
    vector < vector < double > > vals;
    vector < double > diag;

    void build(int N, int M, int nonzero, vector < double > vals, vector < int > indexI, vector < int > indexJ)
    {
        this->N = N;
        this->M = M;
        this->indexJ.resize(N);
        this->vals.resize(N);
        diag.resize(N);

        for (int k = 0; k < nonzero; k++)
        {
            this->indexJ[indexI[k]].push_back(indexJ[k]);
            this->vals[indexI[k]].push_back(vals[k]);
            if (indexI[k] == indexJ[k])
                diag[indexI[k]] = vals[k];
        }
    }
};

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
    MPI_Status status;
    procesor_range(rank, nprocs, N, tl, tr);

    for (int i = tl; i <= tr; i++)
        local_sum += a[i] * b[i];

    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
        for(int i = 1; i < nprocs; i++)
            MPI_Send(&sum, 1, MPI_DOUBLE, i, 104, MPI_COMM_WORLD);
    else
        MPI_Recv(&sum, 1, MPI_DOUBLE, 0, 104, MPI_COMM_WORLD, &status);

    return sum;
}

vector < double > mat_vec_prod( const int rank, const int nprocs, const CRS& A, const vector < double >& x)
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

        for(int i = 1; i < nprocs; i++)
            MPI_Send(&ans[0], N, MPI_DOUBLE, i, 104, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Send(&tl, 1, MPI_INT, 0, 101, MPI_COMM_WORLD);
        MPI_Send(&tsize, 1, MPI_INT, 0, 102, MPI_COMM_WORLD);
        MPI_Send(&ans[tl], tsize, MPI_DOUBLE, 0, 103, MPI_COMM_WORLD);
        MPI_Recv(&ans[0], N, MPI_DOUBLE, 0, 104, MPI_COMM_WORLD, &status);
    }

    return ans;
}

void phill_heat_matrix(int rank, int N, double lambda, CRS& A, string border_type)
{
    int nonzero = 3*N-4;
    vector < double > vals(nonzero);
    vector < int > indexI(nonzero), indexJ(nonzero);
    int pos = 0;

    vals[pos] = 1;
    indexI[pos] = 0;
    indexJ[pos] = 0;
    pos++;
    
    for(int i = 1; i < N-1; i++)
    {
        vals[pos] = -lambda;
        indexI[pos] = i;
        indexJ[pos] = i - 1;
        pos++;
        vals[pos] = 1 + 2 * lambda;
        indexI[pos] = i;
        indexJ[pos] = i;
        pos++;
        vals[pos] = -lambda;
        indexI[pos] = i;
        indexJ[pos] = i + 1;
        pos++;
    }

    vals[pos] = 1;
    indexI[pos] = N-1;
    indexJ[pos] = N-1;
    pos++;

    A.build(N, N, nonzero, vals, indexI, indexJ);
}

double f(double x)
{
    return 4 * x + 4 * x * x; 
}

void border_condition(vector < double > &x, string border_type)
{
    int N = x.size();
    if(border_type == "Neumann")
    {
        x[0] = x[1];
        x[N-1] = x[N-2];
    }
    else if(border_type == "Periodic")
        x[0] = x[N-1] = (x[1] + x[N-2]) / 2;
    else
        x[0] = x[N-1] = 0;
}

void initial_condition(vector < double > &x, string border_type)
{
    int N = x.size();
    double xx;
    for(int i = 1; i < N-1; i++)
    {
        xx = (double) i / (N-1);
        x[i] = f(xx);
    }
}

void conjugate_gradient_jacobi(const int rank, const int nprocs, CRS A, vector < double >& x, vector < double > b, int max_iter, double eps)
{
    int N = A.N;
    vector < double > r(N), p(N), M(N), q(N), w(N);

    double dot_rr = 0, dot_rq = 0;
    w = mat_vec_prod(rank, nprocs, A, x);
    for (int i = 0; i < N; i++)
    {
        r[i] = w[i] - b[i];
        M[i] = A.diag[i];
        q[i] = r[i] / M[i];
        p[i] = -q[i];
    }
    dot_rr = dot_prod(rank, nprocs, r, r);
    dot_rq = dot_prod(rank, nprocs, r, q);

    while (max_iter-- && dot_rr > eps * eps)
    {
        double dot_pow = 0;
        w = mat_vec_prod(rank, nprocs, A, p);
        dot_pow = dot_prod(rank, nprocs, p,w);

        double alpha = dot_rq / dot_pow;
        double new_dot_rr = 0, new_dot_rq = 0;
        for (int i = 0; i < N; i++)
        {
            x[i] += alpha * p[i];
            r[i] += alpha * w[i];
            q[i] = r[i] / M[i];
        }
        
        new_dot_rr = dot_prod(rank, nprocs, r, r);
        new_dot_rq = dot_prod(rank, nprocs, r, q);
        double beta = new_dot_rq / dot_rq;
        for (int i = 0; i < N; i++)
            p[i] = beta * p[i] - q[i];
        
        dot_rr = new_dot_rr;
        dot_rq = new_dot_rq;
    }

}

int main(int argc, char *argv[])
{
    const int N = stoi(argv[1]), M = stoi(argv[2]);
    if(N < 1)
        return 0;
    const double t = stod(argv[3]), heat_constant = stod(argv[4]);
    const string border_type = argv[5];
    const double h = 1.0/(double)(N-1), k = t/(double)(M-1);
    const double lambda = (k * heat_constant)/(h*h);
    ofstream f_out("Implicit_" + border_type + "_" + to_string(N) + "x" + to_string(M) + ".txt");
    
    MPI_Init(&argc, &argv);

    int processCount, processId;
    MPI_Comm_rank(MPI_COMM_WORLD, &processId);
    MPI_Comm_size(MPI_COMM_WORLD, &processCount);

    CRS A;
    vector < double > x(N), x_sol(N,1);
    phill_heat_matrix(processId, N, lambda, A, border_type);
    initial_condition(x, border_type);
    border_condition(x, border_type);

    if(processId == 0)
    {
        for(int i = 0; i < N; i++)
            f_out << x[i] << " ";
        f_out << "\n";
    }

    for(int i = 0; i < M; i++)
    {
        conjugate_gradient_jacobi(processId, processCount, A, x_sol, x, A.M, 0.00001);
        border_condition(x_sol, border_type);
        x = x_sol;
        for(auto &xx : x_sol)
            xx = 1;
        if(processId == 0)
        {
            for(int i = 0; i < N; i++)
                f_out << x[i] << " ";
            f_out << "\n";
        }
    }

    MPI_Finalize();

    return 0;
}