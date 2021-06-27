/**
 * correlation.cu: This file is part of the PolyBench/GPU 1.0 test suite.
 *
 *
 * Contact: Scott Grauer-Gray <sgrauerg@gmail.com>
 * Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU
 /**
 * 3mm.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <time.h>

int NUMBEROFTEST = 1024;
typedef float DATA_TYPE;
#define sqrt_of_array_cell(x,j) sqrt(x[j])

#define DATA_PRINTF_MODIFIER "%0.2f "
unsigned long long int visited[1024][76];

unsigned long long int counter=0;
unsigned long long int NumberOfBranch =76;
unsigned long long int MaxNumber = 0;//9223372036854775807;
int testID=0;

typedef struct{
    DATA_TYPE* a;
    DATA_TYPE* x;
    DATA_TYPE* tmp;
    DATA_TYPE* beta;
    DATA_TYPE* r;
    int nx;
    int ny;
    int niter;
    DATA_TYPE float_n;
    DATA_TYPE n2;
    char choice;
}inputData;

typedef struct{
    DATA_TYPE* result;
}outputData;

char fileName[100];

void init_arrays_atax(int nx, int ny, DATA_TYPE* a, DATA_TYPE* x)
{
    int i, j;
    
    for (i = 0; i < ny; i++){
        x[i] = i * M_PI;
    }
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            a[i*ny + j] = ((DATA_TYPE) i*(j+1)) / nx;
        }
    }
}

/* Array initialization. */
static
void init_array_adi (int n,DATA_TYPE* X,DATA_TYPE* A,DATA_TYPE* B)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            X[i*n + j] = ((DATA_TYPE) i*(j+1) + 1) / n;
            A[i*n + j] = ((DATA_TYPE) i*(j+2) + 2) / n;
            B[i*n + j] = ((DATA_TYPE) i*(j+3) + 3) / n;
        }
}

void print_array_atax(int ny, DATA_TYPE* y)//FIXING ERRPR NY insetad of nx
{
    int i;
    for (i = 0; i < ny; i++) {
        fprintf (stdout, DATA_PRINTF_MODIFIER, y[i]);
        if (i % 20 == 0) fprintf (stdout, "\n");
    }
    fprintf (stdout, "\n");
}

void print_array_adi(int n,DATA_TYPE* X)

{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            fprintf(stdout, DATA_PRINTF_MODIFIER, X[i*n+j]);
            if ((i * n+ j) % 20 == 0) fprintf(stdout, "\n");
        }
    fprintf(stderr, "\n");
}

/* Main computational kernel. The whole function will be timed,
 including the call and return. */
void kernel_adi(int tsteps,int n,DATA_TYPE* X,DATA_TYPE* A,DATA_TYPE* B)
{
    int t, i1, i2;
    int _PB_TSTEPS = tsteps;
    int _PB_N = n;
    for (t = 0; t < _PB_TSTEPS; t++)
    {
        visited[testID][0]  =  (++counter);

        for (i1 = 0; i1 < _PB_N; i1++){
            visited[testID][1] =  (++counter);
            ////counter = visited[1];
            for (i2 = 1; i2 < _PB_N; i2++)
            {
                visited[testID][2] =  (++counter);
                ////counter = visited[2];
                X[i1*n+i2] = X[i1*n+i2] - X[(i1*n)+i2-1] * A[i1*n+i2] / B[i1*n+i2-1];
                B[i1*n+i2] = B[i1*n+i2] - A[i1*n+i2] * A[i1*n+i2] / B[i1*n+i2-1];
            }
        }

        for (i1 = 0; i1 < _PB_N; i1++){
            visited[testID][3] =  (++counter);
            ////counter = visited[3];
            X[i1*n+_PB_N-1] = X[i1*n+_PB_N-1] / B[i1*n+_PB_N-1];
        }
        for (i1 = 0; i1 < _PB_N; i1++){
            visited[testID][4] =  (++counter);
            ////counter = visited[4];
            for (i2 = 0; i2 < _PB_N-2; i2++){
                visited[testID][5] =  (++counter);
                ////counter = visited[testID][5];
                X[i1*n+_PB_N-i2-2] = (X[i1*n+_PB_N-2-i2] - X[i1*n+_PB_N-2-i2-1] * A[i1*n+_PB_N-i2-3]) / B[i1*n+_PB_N-3-i2];
            }
        }
        for (i1 = 1; i1 < _PB_N; i1++){
            visited[testID][6] =  (++counter);
            ////counter = visited[6];
            for (i2 = 0; i2 < _PB_N; i2++) {
                visited[testID][7] =  (++counter);
                ////counter = visited[7];
                X[i1*n+i2] = X[i1*n+i2] - X[(i1-1)*n+i2] * A[i1*n+i2] / B[(i1-1)*n+i2];
                B[i1*n+i2] = B[i1*n+i2] - A[i1*n+i2] * A[i1*n+i2] / B[(i1-1)*n+i2];
            }
        }

        for (i2 = 0; i2 < _PB_N; i2++){
            visited[testID][8] =  (++counter);
            ////counter = visited[8];
            X[(_PB_N-1)*n+i2] = X[(_PB_N-1)*n+i2] / B[(_PB_N-1)*n+i2];
        }
        for (i1 = 0; i1 < _PB_N-2; i1++){
            visited[testID][9] =  (++counter);
            ////counter = visited[testID][9];
            for (i2 = 0; i2 < _PB_N; i2++){
                X[(_PB_N-2-i1)*n+i2] = (X[(_PB_N-2-i1)*n+i2] - X[(_PB_N-i1-3)*n+i2] * A[(_PB_N-3-i1)*n+i2]) / B[(_PB_N-2-i1)*n+i2];
            }
        }
    }
}

void kernel_atax(int nx, int ny, DATA_TYPE* a, DATA_TYPE* x, DATA_TYPE* y,DATA_TYPE* tmp)
{
    int i, j;
    for (i = 0; i < ny; i++){
        visited[testID][10] =  (++counter);
        ////counter = visited[testID][10];
        y[i] = 0;
    }
    for (i = 0; i < nx; i++)
    {
        visited[testID][11] =  (++counter);
        ////counter = visited[testID][11];
        tmp[i] = 0;
        for (j = 0; j < ny; j++){
            visited[testID][12] =  (++counter);
            ////counter = visited[testID][12];
            tmp[i] = tmp[i] + a[i*ny + j] * x[j];
        }
        for (j = 0; j < ny; j++){
            visited[testID][13] =  (++counter);
            ////counter = visited[testID][13];
            y[j] = y[j] + a[i*ny + j] * tmp[i];
        }
    }
}
void init_arrays_correlation(DATA_TYPE* data,int M, int N, DATA_TYPE *float_n)
{
    int i, j;
    *float_n = 1.2;
    for (i=0; i < M; i++)
    {
        for (j=0; j< N; j++)
        {
            data[i*N + j] = (DATA_TYPE) (i*j) /M+i;
        }
    }
}
void print_array_correlation(int m, DATA_TYPE* symmat)
{
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < m; j++) {
            fprintf (stdout, DATA_PRINTF_MODIFIER, symmat[i * m + j]);
            if ((i * m + j) % 20 == 0) fprintf (stdout, "\n");
        }
    }
    fprintf (stdout, "\n");
}
void correlation(DATA_TYPE* data, DATA_TYPE* mean, DATA_TYPE* stddev, DATA_TYPE* symmat, int M, int N, DATA_TYPE float_n)
{
    int i, j, j1, j2;

    DATA_TYPE eps = 0.1f;

    /* Determine mean of column vectors of input data matrix */
    for (j = 0; j < M; j++)
    {
        visited[testID][14] =  (++counter);
        //counter = visited[testID][14];
        mean[j] = 0.0;
        for (i = 0; i < N; i++){
            visited[testID][15] =  (++counter);
            //counter = visited[testID][15];
            mean[j] += data[i*N+j];
        }
        mean[j] /= float_n;
    }

    /* Determine standard deviations of column vectors of data matrix. */
    for (j = 0; j < M; j++)
    {
        visited[testID][16] =  (++counter);
        //counter = visited[testID][16];
        stddev[j] = 0.0;
        for (i = 0; i < N; i++){
            visited[testID][17] =  (++counter);
            //counter = visited[testID][17];
            stddev[j] += (data[i*N+j] - mean[j]) * (data[i*N+j] - mean[j]);
        }
        stddev[j] /= float_n;
        stddev[j] = sqrt_of_array_cell(stddev, j);
        /* The following in an inelegant but usual way to handle
         *      near-zero std. dev. values, which below would cause a zero-
         *           divide. */
        stddev[j] = stddev[j] <= eps ? 1.0 : stddev[j];
    }

    /* Center and reduce the column vectors. */
    for (i = 0; i < N; i++){
        visited[testID][18] =  (++counter);
        //counter = visited[testID][18];
        for (j = 0; j < M; j++)
        {
            visited[testID][19] =  (++counter);
            //counter = visited[testID][19];
            data[i*N+j] -= mean[j];
            data[i*N+j] /= sqrt(float_n) * stddev[j];
        }
    }

    /* Calculate the m * m correlation matrix. */
    for (j1 = 0; j1 < M-1; j1++)
    {
        visited[testID][20] =  (++counter);
        //counter = visited[testID][20];
        symmat[j1*M+j1] = 1.0;
        for (j2 = j1+1; j2 < M; j2++)
        {
            visited[testID][21] =  (++counter);
            //counter = visited[testID][21];
            symmat[j1*M+j2] = 0.0;
            for (i = 0; i < N; i++){
                visited[testID][22] =  (++counter);
                //counter = visited[testID][22];
                symmat[j1*M+j2] += (data[i*N+j1] * data[i*N+j2]);
            }
            symmat[j2*M+j1] = symmat[j1*M+j2];
        }
    }
    symmat[(M-1)*M+M-1] = 1.0;

}

void init_array_covariance(int m, int n, DATA_TYPE *float_n, DATA_TYPE *data)
{
    int i, j;

    *float_n = 1.2;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            data[i*n + j] = ((DATA_TYPE) i*j) / m;
}


void print_array_covariance(int m, DATA_TYPE *symmat)

{
    int i, j;

    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++) {
            printf (DATA_PRINTF_MODIFIER, symmat[i*m + j]);
            if ((i * m + j) % 20 == 0) fprintf (stdout, "\n");
        }
    //printf (stderr, "\n");
}


/* Main computational kernel. The whole function will be timed,
 including the call and return. */
void kernel_covariance(int m, int n,DATA_TYPE float_n,DATA_TYPE *data,DATA_TYPE *symmat,DATA_TYPE *mean)
{
    int i, j, j1, j2;
    // printf("FRoM kernel_covariance ");
    /* Determine mean of column vectors of input data matrix */
    for (j = 0; j < m; j++)
    {
        visited[testID][23] =  (++counter);
        //counter = visited[testID][23];
        mean[j] = 0.0;
        for (i = 0; i < n; i++){
            visited[testID][24] =  (++counter);
            //counter = visited[testID][24];
            mean[j] += data[i*n + j];
        }
        mean[j] /= float_n;
    }

    /* Center the column vectors. */
    for (i = 0; i < n; i++){
        visited[testID][25] =  (++counter);
        //counter = visited[testID][25];
        for (j = 0; j < m; j++){
            visited[testID][26] =  (++counter);
            //counter = visited[testID][26];
            data[i*n + j] -= mean[j];
        }
    }
    /* Calculate the m * m covariance matrix. */
    for (j1 = 0; j1 < m; j1++){
        visited[testID][27] =  (++counter);
        //counter = visited[testID][27];
        for (j2 = j1; j2 < m; j2++)
        {
            visited[testID][28] =  (++counter);
            //counter = visited[testID][28];
            symmat[j1*m + j2] = 0.0;
            for (i = 0; i < n; i++){
                visited[testID][29] =  (++counter);
                //counter = visited[testID][29];
                symmat[j1*m + j2] += (data[i*n + j1] * data[i*n + j2]);
            }
            symmat[j2*m +j1] = symmat[j1*m + j2];
        }
    }

}

void init_array_durbin (int n,DATA_TYPE* y,DATA_TYPE* sum,DATA_TYPE* alpha,DATA_TYPE* beta,DATA_TYPE* r)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        alpha[i] = i;
        beta[i] = (i+1)/n/2.0;
        r[i] = (i+1)/n/4.0;
        for (j = 0; j < n; j++) {
            y[i*n+j] = ((DATA_TYPE) i*j) / n;
            sum[i*n+j] = ((DATA_TYPE) i*j) / n;
        }
    }
}


/* DCE code. Must scan the entire live-out data.
 Can be used also to check the correctness of the output. */
void print_array_durbin(int n,
                        DATA_TYPE* out)

{
    int i;

    for (i = 0; i < n; i++) {
        fprintf (stdout, DATA_PRINTF_MODIFIER, out[i]);
        if (i % 20 == 0) fprintf (stdout, "\n");
    }
}

/* Main computational kernel. The whole function will be timed,
 including the call and return. */
void kernel_durbin(int n,DATA_TYPE* y,DATA_TYPE* sum,DATA_TYPE* alpha,DATA_TYPE* beta,DATA_TYPE* r,DATA_TYPE* out)
{
    int i, k;

    y[0] = r[0];
    beta[0] = 1;
    alpha[0] = r[0];
    for (k = 1; k < n; k++)
    {
        visited[testID][30] =  (++counter);
        //counter = visited[testID][30];
        beta[k] = beta[k-1] - alpha[k-1] * alpha[k-1] * beta[k-1];
        sum[k] = r[k];
        for (i = 0; i <= k - 1; i++){
            sum[(i+1)*n+k] = sum[i*n+k] + r[k-i-1] * y[i*n+k-1];
            visited[testID][31] =  (++counter);
            //counter = visited[testID][31];
        }
        alpha[k] = -sum[k*n+k] * beta[k];
        for (i = 0; i <= k-1; i++){
            visited[testID][32] =  (++counter);
            //counter = visited[testID][32];
            y[i*n+k] = y[i*n+k-1] + alpha[k] * y[(k-i-1)*n+k-1];
        }
        y[k*n+k] = alpha[k];
    }
    for (i = 0; i < n; i++){
        visited[testID][33] =  (++counter);
        //counter = visited[testID][33];
        out[i] = y[i*n+n-1];
    }
}


/* Array initialization. */
void init_array_jacobi(int n,
                       DATA_TYPE* A,
                       DATA_TYPE* B)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            A[i*n+j] = ((DATA_TYPE) i*(j+2) + 2) / n;
            B[i*n+j] = ((DATA_TYPE) i*(j+3) + 3) / n;
        }
}

static void print_array_jacobi(int n, DATA_TYPE* A)

{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            printf("%f ", A[i*n+j]);
            // if ((i * n + j) % 20 == 0) fprintf(stderr, "\n");
        }
    //fprintf(stderr, "\n");
}

/* Main computational kernel. The whole function will be timed,
 including the call and return. */

void kernel_jacobi_2d_imper(int tsteps, int n, DATA_TYPE* A,DATA_TYPE* B)
{
    int t, i, j;
    for (t = 0; t < tsteps; t++)
    {
        visited[testID][34] =  (++counter);
        //counter = visited[testID][34];
        for (i = 1; i <n ; i++){
            visited[testID][35] =  (++counter);
            //counter = visited[testID][35];
            for (j = 1; j < n ; j++){
                visited[testID][36] =  (++counter);
                //counter = visited[testID][36];
                B[i*n+j] = 0.2 * (A[i*n+j] + A[i*n+j-1] + A[i*n+1+j] + A[(1+i)*n+j] + A[(i-1)*n+j]);
            }
        }
        for (i = 1; i < n; i++){
            visited[testID][37] =  (++counter);
            //counter = visited[testID][37];
            for (j = 1; j < n; j++){
                visited[testID][38] =  (++counter);
                //counter = visited[testID][38];
                A[i*n+j] = B[i*n+j];
            }
        }
    }
}

/* Array initialization. */
void init_array_ludcmp (int n,DATA_TYPE* A,DATA_TYPE* b,DATA_TYPE* x,DATA_TYPE* y)
{
    int i, j;

    for (i = 0; i <= n; i++)
    {
        x[i] = i + 1;
        y[i] = (i+1)/n/2.0 + 1;
        b[i] = (i+1)/n/2.0 + 42;
        for (j = 0; j <= n; j++) {
            A[i*(n+1)+j] = ((DATA_TYPE) (i+1)*(j+1)) / n;
        }
    }
}


/* DCE code. Must scan the entire live-out data.
 Can be used also to check the correctness of the output. */
void print_array_ludcomp(int n,DATA_TYPE* x)

{
    int i;

    for (i = 0; i <= n; i++) {
        printf ( DATA_PRINTF_MODIFIER, x[i]);
    }
}


/* Main computational kernel. The whole function will be timed,
 including the call and return. */
void kernel_ludcmp(int n,DATA_TYPE* A,DATA_TYPE* b,DATA_TYPE* x,DATA_TYPE* y)
{
    int i, j, k;

    DATA_TYPE w;

    b[0] = 1.0;
    for (i = 0; i < n; i++)
    {
        visited[testID][39] =  (++counter);
        //counter = visited[testID][39];
        for (j = i+1; j <= n; j++)
        {
            visited[testID][40] =  (++counter);
            //counter = visited[testID][40];
            w = A[j*(n+1)+i];
            for (k = 0; k < i; k++){
                visited[testID][41] =  (++counter);
                //counter = visited[testID][41];
                w = w- A[j*(n+1)+k] * A[k*(n+1)+i];
            }
            A[j*(n+1)+i] = w / A[i*(n+1)+i];
        }
        for (j = i+1; j <= n; j++)
        {
            visited[testID][42] =  (++counter);
            //counter = visited[testID][42];
            w = A[(i+1)*(n+1)+j];
            for (k = 0; k <= i; k++){
                visited[testID][43] =  (++counter);
                //counter = visited[testID][43];
                w = w  - A[(i+1)*(n+1)+k] * A[k*(n+1)+j];
            }
            A[(i+1)*(n+1)+j] = w;
        }
    }
    y[0] = b[0];
    for (i = 1; i <= n; i++)
    {
        visited[testID][44] =  (++counter);
        //counter = visited[testID][44];
        w = b[i];
        for (j = 0; j < i; j++){
            visited[testID][45] =  (++counter);
            //counter = visited[testID][45];
            w = w - A[i*(n+1)+j] * y[j];
        }
        y[i] = w;
    }
    x[n] = y[n] / A[n*(n+1)+n];
    for (i = 0; i <= n - 1; i++)
    {
        visited[testID][46] =  (++counter);
        //counter = visited[testID][46];
        w = y[n - 1 - (i)];
        for (j = n - i; j <= n; j++){
            visited[testID][47] =  (++counter);
            //counter = visited[testID][47];
            w = w - A[(n - 1 - i)*(n+1)+j] * x[j];
        }
        x[n - 1 - i] = w / A[(n - 1 - (i))*(n+1)+ (n - 1-(i))];
    }
}


/* Array initialization. */
void init_array_reg (int maxgrid,DATA_TYPE* sum_tang,DATA_TYPE* mean,DATA_TYPE* path)
{
    int i, j;

    for (i = 0; i < maxgrid; i++)
        for (j = 0; j < maxgrid; j++) {
            sum_tang[i*maxgrid+j] = (DATA_TYPE)((i+1)*(j+1));
            mean[i*maxgrid+j] = ((DATA_TYPE) i-j) / maxgrid;
            path[i*maxgrid+j] = ((DATA_TYPE) i*(j-1)) / maxgrid;
        }
}


void print_array_reg(int maxgrid,
                     DATA_TYPE* path)
{
    int i, j;

    for (i = 0; i < maxgrid; i++)
        for (j = 0; j < maxgrid; j++) {
            printf ("%f", path[i*maxgrid+j]);
        }
}

/* Main computational kernel. The whole function will be timed,
 including the call and return. */

void kernel_reg_detect(int niter, int maxgrid, int length,DATA_TYPE* sum_tang,DATA_TYPE* mean,DATA_TYPE* path,DATA_TYPE* diff,DATA_TYPE* sum_diff)
{
    int t, i, j, cnt;
    //   int _PB_NITER = niter;
    //  int _PB_LENGTH = length;
    // int _PB_MAXGRID = maxgrid;
    for (t = 0; t < niter; t++)
    {
        visited[testID][48] =  (++counter);
        //counter = visited[testID][48];
        for (j = 0; j <= maxgrid - 1; j++){
            visited[testID][49] =  (++counter);
            //counter = visited[testID][49];
            for (i = j; i <= maxgrid - 1; i++){
                visited[testID][50] =  (++counter);
                //counter = visited[testID][50];
                for (cnt = 0; cnt <= length - 1; cnt++){
                    visited[testID][51] =  (++counter);
                    //counter = visited[testID][51];
                    diff[j*maxgrid+ (i*maxgrid*length) + cnt] = sum_tang[j*maxgrid+i];
                }
            }
        }
        for (j = 0; j <= maxgrid - 1; j++)
        {
            visited[testID][52] =  (++counter);
            //counter = visited[testID][52];
            for (i = j; i <= maxgrid - 1; i++)
            {
                visited[testID][53] =  (++counter);
                //counter = visited[testID][53];
                sum_diff[j*maxgrid+(i*maxgrid*length)] = diff[j*maxgrid+ (i*maxgrid*length)];
                for (cnt = 1; cnt <= length - 1; cnt++){
                    visited[testID][54] =  (++counter);
                    //counter = visited[testID][54];
                    sum_diff[j*maxgrid+(i*maxgrid*length) + cnt] = sum_diff[j*maxgrid+(i*maxgrid*length) + (cnt - 1)] + diff[j*maxgrid+(i*maxgrid*length) + cnt];
                }
                mean[j*maxgrid+i] = sum_diff[j*maxgrid+(i*maxgrid*length) + (length - 1)];
            }
        }

        for (i = 0; i <= maxgrid - 1; i++){
            visited[testID][55] =  (++counter);
            //counter = visited[testID][55];
            path[0*maxgrid+i] = mean[0*maxgrid+i];
        }
        for (j = 1; j <= maxgrid - 1; j++){
            visited[testID][56] =  (++counter);
            //counter = visited[testID][56];
            for (i = j; i <= maxgrid - 1; i++){
                visited[testID][57] =  (++counter);
                //counter = visited[testID][57];
                path[j*maxgrid+i] = path[(j - 1)*maxgrid+ (i - 1)] + mean[j*maxgrid+i];
            }
        }
    }
}


/* Array initialization. */
static
void init_array_syr2k(int ni, int nj,DATA_TYPE *alpha,DATA_TYPE *beta,DATA_TYPE* C,DATA_TYPE* A,DATA_TYPE* B)
{
    int i, j;

    *alpha = 32412;
    *beta = 2123;
    for (i = 0; i < ni; i++)
        for (j = 0; j < nj; j++) {
            A[i*nj+j] = ((DATA_TYPE) i*j) / ni;
            B[i*nj+j] = ((DATA_TYPE) i*j) / ni;
        }
    for (i = 0; i < ni; i++)
        for (j = 0; j < ni; j++)
            C[i*ni+j] = ((DATA_TYPE) i*j) / ni;
}


/* DCE code. Must scan the entire live-out data.
 Can be used also to check the correctness of the output. */
void print_array_syr2k(int ni,
                       DATA_TYPE* C)
{
    int i, j;

    for (i = 0; i < ni; i++)
        for (j = 0; j < ni; j++) {
            printf (DATA_PRINTF_MODIFIER, C[i*ni+j]);

        }
}


/* Main computational kernel. The whole function will be timed,
 including the call and return. */
void kernel_syr2k(int ni, int nj,DATA_TYPE alpha, DATA_TYPE beta,DATA_TYPE* C,DATA_TYPE* A,DATA_TYPE* B)
{
    int i, j, k;

    /*    C := alpha*A*B' + alpha*B*A' + beta*C */
    for (i = 0; i < ni; i++){
        visited[testID][58] =  (++counter);
        //counter = visited[testID][58];
        for (j = 0; j < ni; j++){
            visited[testID][59] =  (++counter);
            //counter = visited[testID][59];
            C[i*ni+j] *= beta;
        }
        for (i = 0; i < ni; i++){
            visited[testID][60] =  (++counter);
            //counter = visited[testID][60];
            for (j = 0; j < ni; j++){
                visited[testID][61] =  (++counter);
                //counter = visited[testID][61];
                for (k = 0; k < nj; k++)
                {
                    visited[testID][62] =  (++counter);
                    //counter = visited[testID][62];
                    C[i*ni+j] += alpha * A[i*nj+k] * B[j*nj+k];
                    C[i*ni+j] += alpha * B[i*nj+k] * A[j*nj+k];
                }
            }
        }
    }
}

void init_array_floyd (int n, DATA_TYPE *path)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            path[i*n+j] = ((DATA_TYPE) (i+1)*(j+1)) / n;
}


/* DCE code. Must scan the entire live-out data.
 Can be used also to check the correctness of the output. */
void print_array_floyd(int n,DATA_TYPE *path)

{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            printf ( DATA_PRINTF_MODIFIER, path[i*n+j]);
        }
}


/* Main computational kernel. The whole function will be timed,
 including the call and return. */
void kernel_floyd_warshall(int _PB_N, DATA_TYPE *path)
{
    int i, j, k;

    for (k = 0; k < _PB_N; k++)
    {
        visited[testID][63] =  (++counter);
        //counter = visited[testID][63];
        for(i = 0; i < _PB_N; i++){
            visited[testID][64] =  (++counter);
            //counter = visited[testID][64];
            for (j = 0; j < _PB_N; j++){
                visited[testID][65] =  (++counter);
                //counter = visited[testID][65];
                path[i*_PB_N+j] = path[i*_PB_N+j] < path[i*_PB_N+k] + path[k*_PB_N+j] ? path[i*_PB_N+j] : path[i*_PB_N+k] + path[k*_PB_N+j];
            }
        }
    }

}

void readingInput(inputData *dataCPU, outputData *outD){
    int index=0;
    int X, Y, n;
    char choice;
    int ret = fscanf(stdin, "%d %d %d", &choice, &X, &Y);
    while(ret != EOF){
        //   printf("index %d \n", index);
        dataCPU[index].choice = choice;
        switch(choice){
            case 0:
                dataCPU[index].nx = X;
                dataCPU[index].ny = Y;
                outD[index].result =(DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].a = (DATA_TYPE *)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE *)malloc(X*X* sizeof(DATA_TYPE));
                init_array_adi(dataCPU[index].nx, outD[index].result,dataCPU[index].a,dataCPU[index].x);
                break;
            case 1:
                dataCPU[index].nx = X ;
                dataCPU[index].ny = Y;
                dataCPU[index].a =(DATA_TYPE*)malloc(X*Y*sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE *)malloc(Y * sizeof(DATA_TYPE));
                outD[index].result = (DATA_TYPE *)malloc(Y * sizeof(DATA_TYPE));
                dataCPU[index].tmp = (DATA_TYPE*)malloc(X*sizeof(DATA_TYPE));
                init_arrays_atax(dataCPU[index].nx,dataCPU[index].ny, dataCPU[index].a,dataCPU[index].x);
                break;
            case 2:
                dataCPU[index].nx = X ;
                dataCPU[index].ny = Y;
                dataCPU[index].a =(DATA_TYPE*)malloc(X*Y*sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE *)malloc(X * sizeof(DATA_TYPE));
                outD[index].result = (DATA_TYPE *)malloc(X*X * sizeof(DATA_TYPE));
                dataCPU[index].tmp = (DATA_TYPE*)malloc(X*sizeof(DATA_TYPE));
                init_arrays_correlation(dataCPU[index].a, X, Y,&dataCPU[index].float_n);
                break;
            case 3:
                dataCPU[index].nx = X ;
                dataCPU[index].ny = Y;
                dataCPU[index].a =(DATA_TYPE*)malloc(X*Y*sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE *)malloc(X * sizeof(DATA_TYPE));
                outD[index].result = (DATA_TYPE *)malloc(X*X * sizeof(DATA_TYPE));
                init_array_covariance( X, Y,&dataCPU[index].float_n,dataCPU[index].a);
                break;
            case 4:
                dataCPU[index].nx = X ;
                dataCPU[index].a = (DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].tmp= (DATA_TYPE*)malloc(X*sizeof(DATA_TYPE));
                dataCPU[index].beta= (DATA_TYPE*)malloc(X*sizeof(DATA_TYPE));
                dataCPU[index].r = (DATA_TYPE*)malloc(X*sizeof(DATA_TYPE));
                outD[index].result = (DATA_TYPE*)malloc(X*sizeof(DATA_TYPE));
                init_array_durbin(dataCPU[index].nx,dataCPU[index].a, dataCPU[index].x,dataCPU[index].tmp,dataCPU[index].beta, dataCPU[index].r );
                break;
            case 5:
                dataCPU[index].nx = X ;
                dataCPU[index].ny = Y;
                outD[index].result = (DATA_TYPE *)malloc(X*X*sizeof(DATA_TYPE));
                init_array_floyd(X,outD[index].result);
                break;
            case 6:
                dataCPU[index].ny = Y ;
                dataCPU[index].nx = X;
                outD[index].result = (DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                init_array_jacobi(X, outD[index].result ,dataCPU[index].x);
                break;
            case 7:
                dataCPU[index].nx = X;
                X++;
                dataCPU[index].a =(DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE *)malloc(X * sizeof(DATA_TYPE));
                outD[index].result = (DATA_TYPE*)malloc(X*sizeof(DATA_TYPE));
                dataCPU[index].r = (DATA_TYPE*)malloc(X * sizeof(DATA_TYPE));
                init_array_ludcmp(dataCPU[index].nx,dataCPU[index].a, dataCPU[index].x,outD[index].result,dataCPU[index].r);
                break;
            case 8:
                ret = fscanf(stdin, "%d ", &n);
                dataCPU[index].niter = n;
                dataCPU[index].nx = X;
                dataCPU[index].ny = Y;
                dataCPU[index].a = (DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                outD[index].result  = (DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].tmp = (DATA_TYPE*)malloc(X*X*Y*sizeof(DATA_TYPE));
                dataCPU[index].r = (DATA_TYPE*)malloc(X*X*Y*sizeof(DATA_TYPE));
                init_array_reg(X, dataCPU[index].a,dataCPU[index].x, outD[index].result);
                break;
            case 9:
                dataCPU[index].nx = X ;
                dataCPU[index].ny = Y;
                outD[index].result  = (DATA_TYPE*)malloc(X*X*sizeof(DATA_TYPE));
                dataCPU[index].a = (DATA_TYPE*)malloc(X * Y* sizeof(DATA_TYPE));
                dataCPU[index].x = (DATA_TYPE*)malloc(X*Y* sizeof(DATA_TYPE));
                init_array_syr2k(dataCPU[index].nx,dataCPU[index].ny,&dataCPU[index].float_n, &dataCPU[index].n2,outD[index].result, dataCPU[index].a,dataCPU[index].x);
                break;
            default:
                break;
        }
        index++;
        ret = fscanf(stdin, "%d %d %d", &choice, &X, &Y);
    }
    NUMBEROFTEST = index;
}
void write(){
    FILE *fp1;
    fp1 = fopen("Traces2D.txt", "a");
    if (fp1 == NULL){
        printf("Problem in a file");
        return;
    }
    int i, j;
    for(i=0; i<NUMBEROFTEST; i++){
        for(j=0; j<NumberOfBranch; j++){
            if(visited[i][j] ==-1)
                visited[i][j] = NumberOfBranch * MaxNumber;
            fprintf(fp1, "%lu ", visited[i][j]);
        }
        fputs("\n",fp1);
    }
    fclose(fp1);
}

void myKernel(inputData *data, outputData* outD)
{
    int i;
    for(i=0 ;i<NUMBEROFTEST; i++){
        testID =i;
        counter =0;
        switch(data[i].choice){
            case 0:
                kernel_adi(data[i].ny, data[i].nx,outD[i].result, data[i].a, data[i].x);
                visited[testID][66] =   -1;
                counter++;
                break;
            case 1:
                kernel_atax(data[i].nx, data[i].ny,data[i].a, data[i].x, outD[i].result, data[i].tmp);

                visited[testID][67] = -1;
                counter++;
                break;
            case 2:
                correlation(data[i].a,data[i].x,data[i].tmp,outD[i].result,data[i].nx,data[i].ny,data[i].float_n);

                visited[testID][68] = -1;
                counter++;
                break;
            case 3:
                kernel_covariance(data[i].nx, data[i].ny, data[i].float_n, data[i].a, outD[i].result, data[i].x);

                visited[testID][69] = -1;
                counter++;
                break;
            case 4:
                kernel_durbin(data[i].nx, data[i].a, data[i].x, data[i].tmp, data[i].beta, data[i].r, outD[i].result);

                visited[testID][70] = -1;
                counter++;
                break;
            case 5:
                kernel_floyd_warshall(data[i].nx, outD[i].result);

                visited[testID][71] = -1;
                counter++;
                break;
            case 6:
                kernel_jacobi_2d_imper(data[i].ny, data[i].nx, outD[i].result, data[i].x);

                visited[testID][72] = -1;
                counter++;
                break;
            case 7:
                kernel_ludcmp(data[i].nx, data[i].a,data[i].x, outD[i].result, data[i].r);

                visited[testID][73] = -1;
                counter++;
                break;
            case 8:
                kernel_reg_detect(data[i].niter, data[i].nx, data[i].ny,data[i].a, data[i].x,outD[i].result, data[i].tmp, data[i].r);

                visited[testID][74] = -1;
                counter++;
                break;
            case 9:
                kernel_syr2k(data[i].nx, data[i].ny, data[i].float_n, data[i].n2, outD[i].result, data[i].a, data[i].x);

                visited[testID][75] = -1;
                counter++;
                break;
            default:
                break;
        }
        if(MaxNumber<counter)
            MaxNumber = counter;
    }
}

//************************************* Writing time in a FILE ******************************************
int main(int argc, char* argv[])
{
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *outD = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU, outD);
    int i,j;
    for(i=0; i<NUMBEROFTEST; i++)
        for(j=0; j<NumberOfBranch; j++)
            visited[i][j]=0;
    myKernel(dataCPU,outD);
    write();
    i=0;
    for(; i<NUMBEROFTEST;i++){
        printf("ID# %d ",i);
        printf("%d", dataCPU[i].choice);
        switch(dataCPU[i].choice){
            case 0:
                print_array_adi(dataCPU[i].nx, outD[i].result);
                break;
            case 1:
                print_array_atax(dataCPU[i].ny, outD[i].result);
                break;
            case 2:
                print_array_correlation(dataCPU[i].nx, outD[i].result);
                break;
            case 3:
                print_array_covariance(dataCPU[i].nx, outD[i].result);
                break;
            case 4:
                print_array_durbin(dataCPU[i].nx, outD[i].result);
                break;
            case 5:
                print_array_floyd(dataCPU[i].nx,outD[i].result);
                break;
            case 6:
                print_array_jacobi(dataCPU[i].nx, outD[i].result);
                break;
            case 7:
                print_array_ludcomp(dataCPU[i].nx, outD[i].result);
                break;
            case 8:
                print_array_reg(dataCPU[i].nx, outD[i].result);
                break;
            case 9:
                print_array_syr2k(dataCPU[i].nx, outD[i].result);
                break;
        }
        fprintf(stdout, "------\n");
    }
    return 0;
}
