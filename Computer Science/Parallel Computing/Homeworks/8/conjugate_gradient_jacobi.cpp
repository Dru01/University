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

        cout << N << endl;

        for (int k = 0; k < nonzero - 1; k++)
        {
            this->indexJ[indexI[k] - 1].push_back(indexJ[k] - 1);
            this->vals[indexI[k] - 1].push_back(vals[k]);
            if (indexI[k] == indexJ[k])
                diag[indexI[k]-1] = vals[k];
        }
    }
};

void conjugate_gradient_jacobi(CRS A, vector < double >& x, vector < double > b, int max_iter, double eps)
{
    int N = A.N;
    vector < double > r(N), p(N), M(N), q(N), w(N);

    double dot_rr = 0, dot_rq = 0;
#pragma omp parallel for default(shared) reduction(+:dot_rr, dot_rq)
    for (int i = 0; i < N; i++)
    {
        double sum = 0;
        for (int k = 0; k < A.indexJ[i].size(); k++)
            sum += A.vals[i][k] * x[A.indexJ[i][k]];
        r[i] = sum - b[i];
        M[i] = A.diag[i];
        q[i] = r[i] / M[i];
        p[i] = -q[i];
        dot_rr += r[i] * r[i];
        dot_rq += r[i] * q[i];
    }

    while (max_iter-- && dot_rr > eps * eps)
    {
        double dot_pow = 0;
#pragma omp parallel for default(shared) reduction(+:dot_pow)
        for (int i = 0; i < N; i++)
        {
            double sum = 0;
            for (int k = 0; k < A.indexJ[i].size(); k++)
                sum += A.vals[i][k] * p[A.indexJ[i][k]];
            w[i] = sum;
            dot_pow += p[i] * w[i];
        }
        double alpha = dot_rq / dot_pow;
        double new_dot_rr = 0, new_dot_rq = 0;
#pragma omp parallel for default(shared) reduction(+:new_dot_rr,new_dot_rq)
        for (int i = 0; i < N; i++)
        {
            x[i] += alpha * p[i];
            r[i] += alpha * w[i];
            q[i] = r[i] / M[i];
            new_dot_rr += r[i] * r[i];
            new_dot_rq += r[i] * q[i];
        }
        double beta = new_dot_rq / dot_rq;
#pragma omp parallel for default(shared)
        for (int i = 0; i < N; i++)
            p[i] = beta * p[i] - q[i];
        dot_rr = new_dot_rr;
        dot_rq = new_dot_rq;
    }

}

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
    for(int i = 0; i < nonzero-1;i++)
        cout << indexI[i] << " ";
    cout << endl;
    double NN;
    fread(&NN, sizeof(double), 1, file);
    cout << NN << endl;

    indexJ = new double[nonzero - 1];
    fread(indexJ, sizeof(double), nonzero - 1, file);
    double MM;
    fread(&MM, sizeof(double), 1, file);
    cout << MM << endl;

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

double norm_inf(const vector < double >& vec)
{
    double ans = abs(vec[0]);
    for (const auto& v : vec)
        ans = std::max(ans, abs(v));
    return ans;
}

double norm_2(const vector < double >& vec)
{
    double ans = 0.0;
    for (const auto& it : vec)
        ans += it * it;
    return sqrt(ans);
}

int main(int argc, char* argv[])
{
    omp_set_num_threads(8);
    const char* filename = argv[1];
    CRS A;
    vector < double > xsol;
    vector < double > b;
    read_system_eq(filename, A, b, xsol);
    vector < double > x(A.M);
    vector < double > difx(A.M);

    conjugate_gradient_jacobi(A, x, b, A.M, 0.00001);

    for (int i = 0; i < A.M; i++)
        difx[i] = x[i] - xsol[i];

    cout << "Error (L2): " << norm_2(difx) << "\n";
    cout << "Error (Linf): " << norm_inf(difx) << "\n";
    return 0;
}