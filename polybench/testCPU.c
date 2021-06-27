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

#define BILLION  1000000000.0;
int NUMBEROFTEST = 1024;
typedef float DATA_TYPE;
#define sqrt_of_array_cell(x,j) sqrt(x[j])

#define DATA_PRINTF_MODIFIER "%0.2f "

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

void print_array_atax(int ny, DATA_TYPE* y) //FIXING ERRPR NY insetad of nx
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
        for (i1 = 0; i1 < _PB_N; i1++)
            for (i2 = 1; i2 < _PB_N; i2++)
            {
                X[i1*n+i2] = X[i1*n+i2] - X[(i1*n)+i2-1] * A[i1*n+i2] / B[i1*n+i2-1];
                B[i1*n+i2] = B[i1*n+i2] - A[i1*n+i2] * A[i1*n+i2] / B[i1*n+i2-1];
            }

        for (i1 = 0; i1 < _PB_N; i1++)
            X[i1*n+_PB_N-1] = X[i1*n+_PB_N-1] / B[i1*n+_PB_N-1];

        for (i1 = 0; i1 < _PB_N; i1++)
            for (i2 = 0; i2 < _PB_N-2; i2++)
            X[i1*n+_PB_N-i2-2] = (X[i1*n+_PB_N-2-i2] - X[i1*n+_PB_N-2-i2-1] * A[i1*n+_PB_N-i2-3]) / B[i1*n+_PB_N-3-i2];

        for (i1 = 1; i1 < _PB_N; i1++)
            for (i2 = 0; i2 < _PB_N; i2++) {
                X[i1*n+i2] = X[i1*n+i2] - X[(i1-1)*n+i2] * A[i1*n+i2] / B[(i1-1)*n+i2];
                B[i1*n+i2] = B[i1*n+i2] - A[i1*n+i2] * A[i1*n+i2] / B[(i1-1)*n+i2];
            }

        for (i2 = 0; i2 < _PB_N; i2++)
            X[(_PB_N-1)*n+i2] = X[(_PB_N-1)*n+i2] / B[(_PB_N-1)*n+i2];

        for (i1 = 0; i1 < _PB_N-2; i1++)
            for (i2 = 0; i2 < _PB_N; i2++)
                X[(_PB_N-2-i1)*n+i2] = (X[(_PB_N-2-i1)*n+i2] - X[(_PB_N-i1-3)*n+i2] * A[(_PB_N-3-i1)*n+i2]) / B[(_PB_N-2-i1)*n+i2];
    }

}

 void kernel_atax(int nx, int ny, DATA_TYPE* a, DATA_TYPE* x, DATA_TYPE* y,DATA_TYPE* tmp)
{
    int i, j;
    for (i = 0; i < ny; i++)
        y[i] = 0;
    for (i = 0; i < nx; i++)
    {
        tmp[i] = 0;
        for (j = 0; j < ny; j++)
            tmp[i] = tmp[i] + a[i*ny + j] * x[j];

        for (j = 0; j < ny; j++)
            y[j] = y[j] + a[i*ny + j] * tmp[i];
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
		mean[j] = 0.0;
		for (i = 0; i < N; i++)
			mean[j] += data[i*N+j];
		mean[j] /= float_n;
         }	

	/* Determine standard deviations of column vectors of data matrix. */
	for (j = 0; j < M; j++)
	{
		stddev[j] = 0.0;
		for (i = 0; i < N; i++)
			stddev[j] += (data[i*N+j] - mean[j]) * (data[i*N+j] - mean[j]);
		stddev[j] /= float_n;
		stddev[j] = sqrt_of_array_cell(stddev, j);
/* The following in an inelegant but usual way to handle
*      near-zero std. dev. values, which below would cause a zero-
*           divide. */
		stddev[j] = stddev[j] <= eps ? 1.0 : stddev[j];
	}	

/* Center and reduce the column vectors. */
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
		{
			data[i*N+j] -= mean[j];
			data[i*N+j] /= sqrt(float_n) * stddev[j];
		}

/* Calculate the m * m correlation matrix. */
	for (j1 = 0; j1 < M-1; j1++)
	{
		symmat[j1*M+j1] = 1.0;
		for (j2 = j1+1; j2 < M; j2++)
		{
			symmat[j1*M+j2] = 0.0;
			for (i = 0; i < N; i++)
				symmat[j1*M+j2] += (data[i*N+j1] * data[i*N+j2]);
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
        mean[j] = 0.0;
        for (i = 0; i < n; i++)
        mean[j] += data[i*n + j];
        mean[j] /= float_n;
    }

    /* Center the column vectors. */
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            data[i*n + j] -= mean[j];

    /* Calculate the m * m covariance matrix. */
    for (j1 = 0; j1 < m; j1++)
        for (j2 = j1; j2 < m; j2++)
        {
            symmat[j1*m + j2] = 0.0;
            for (i = 0; i < n; i++)
                symmat[j1*m + j2] += (data[i*n + j1] * data[i*n + j2]);
            symmat[j2*m +j1] = symmat[j1*m + j2];
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
        beta[k] = beta[k-1] - alpha[k-1] * alpha[k-1] * beta[k-1];
        sum[k] = r[k];
        for (i = 0; i <= k - 1; i++)
            sum[(i+1)*n+k] = sum[i*n+k] + r[k-i-1] * y[i*n+k-1];
        alpha[k] = -sum[k*n+k] * beta[k];
        for (i = 0; i <= k-1; i++)
            y[i*n+k] = y[i*n+k-1] + alpha[k] * y[(k-i-1)*n+k-1];
        y[k*n+k] = alpha[k];
    }
    for (i = 0; i < n; i++)
        out[i] = y[i*n+n-1];
}

void init_array_dynprog(int length,
		DATA_TYPE* c,
		DATA_TYPE* W)
{
  int i, j;
  for (i = 0; i < length; i++)
    for (j = 0; j < length; j++) {
      c[i*length+j] = i*j % 2;
      W[i*length+j] = ((DATA_TYPE) i-j) / length;
    }
}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
void print_array_dynprog(DATA_TYPE out)
{
  printf (DATA_PRINTF_MODIFIER, out);
  //printf(stdout, "\n");
}

/* Main computational kernel. The whole function will be timed,
including the call and return. */

 void kernel_dynprog(int tsteps, int length,
	DATA_TYPE* c,
	DATA_TYPE* W, DATA_TYPE* sum_c, DATA_TYPE *out)
{
	int iter, i, j, k;
	int _PB_TSTEPS = tsteps;
	int _PB_LENGTH = length;
	DATA_TYPE out_l = 0;
	for (iter = 0; iter < _PB_TSTEPS; iter++)
	{
		for (i = 0; i <= _PB_LENGTH - 1; i++)
			for (j = 0; j <= _PB_LENGTH - 1; j++)
				c[i*length+j] = 0;

		for (i = 0; i <= _PB_LENGTH - 2; i++)
		{
			for (j = i + 1; j <= _PB_LENGTH - 1; j++)
			{
				sum_c[(length*i)+(length*length*j)+i] = 0;
				for (k = i + 1; k <= j - 1; k++)
					sum_c[(length*i)+(length*j*length)+k] = sum_c[(length*i)+(length*length*j)+(k - 1)] + c[i*length+k] + c[k*length+j];
				c[i*length+j] = sum_c[(i*length)+(length*length*j)+(j - 1)] + W[i*length+j];
			}
		}
		out_l += c[0*length+ (_PB_LENGTH - 1)];
	}
	*out = out_l;

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
        for (i = 1; i <n ; i++)
            for (j = 1; j < n ; j++)
                B[i*n+j] = 0.2 * (A[i*n+j] + A[i*n+j-1] + A[i*n+1+j] + A[(1+i)*n+j] + A[(i-1)*n+j]);
        for (i = 1; i < n; i++)
            for (j = 1; j < n; j++)
                A[i*n+j] = B[i*n+j];
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
        for (j = i+1; j <= n; j++)
        {
            w = A[j*(n+1)+i];
            for (k = 0; k < i; k++)
            w = w- A[j*(n+1)+k] * A[k*(n+1)+i];
            A[j*(n+1)+i] = w / A[i*(n+1)+i];
        }
        for (j = i+1; j <= n; j++)
        {
            w = A[(i+1)*(n+1)+j];
            for (k = 0; k <= i; k++)
            w = w  - A[(i+1)*(n+1)+k] * A[k*(n+1)+j];
            A[(i+1)*(n+1)+j] = w;
        }
    }
    y[0] = b[0];
    for (i = 1; i <= n; i++)
    {
        w = b[i];
        for (j = 0; j < i; j++)
            w = w - A[i*(n+1)+j] * y[j];
        y[i] = w;
    }
    x[n] = y[n] / A[n*(n+1)+n];
    for (i = 0; i <= n - 1; i++)
    {
        w = y[n - 1 - (i)];
        for (j = n - i; j <= n; j++)
            w = w - A[(n - 1 - i)*(n+1)+j] * x[j];
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
        for (j = 0; j <= maxgrid - 1; j++)
            for (i = j; i <= maxgrid - 1; i++)
                for (cnt = 0; cnt <= length - 1; cnt++)
                    diff[j*maxgrid+ (i*maxgrid*length) + cnt] = sum_tang[j*maxgrid+i];

        for (j = 0; j <= maxgrid - 1; j++)
        {
            for (i = j; i <= maxgrid - 1; i++)
            {
                sum_diff[j*maxgrid+(i*maxgrid*length)] = diff[j*maxgrid+ (i*maxgrid*length)];
                for (cnt = 1; cnt <= length - 1; cnt++)
                sum_diff[j*maxgrid+(i*maxgrid*length) + cnt] = sum_diff[j*maxgrid+(i*maxgrid*length) + (cnt - 1)] + diff[j*maxgrid+(i*maxgrid*length) + cnt];
                mean[j*maxgrid+i] = sum_diff[j*maxgrid+(i*maxgrid*length) + (length - 1)];
            }
        }

        for (i = 0; i <= maxgrid - 1; i++)
            path[0*maxgrid+i] = mean[0*maxgrid+i];

        for (j = 1; j <= maxgrid - 1; j++)
            for (i = j; i <= maxgrid - 1; i++)
                path[j*maxgrid+i] = path[(j - 1)*maxgrid+ (i - 1)] + mean[j*maxgrid+i];
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
   for (i = 0; i < ni; i++)
        for (j = 0; j < ni; j++)
            C[i*ni+j] *= beta;
            for (i = 0; i < ni; i++)
                for (j = 0; j < ni; j++)
                    for (k = 0; k < nj; k++)
                    {
                        C[i*ni+j] += alpha * A[i*nj+k] * B[j*nj+k];
                        C[i*ni+j] += alpha * B[i*nj+k] * A[j*nj+k];
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
        for(i = 0; i < _PB_N; i++)
        for (j = 0; j < _PB_N; j++)
            path[i*_PB_N+j] = path[i*_PB_N+j] < path[i*_PB_N+k] + path[k*_PB_N+j] ? path[i*_PB_N+j] : path[i*_PB_N+k] + path[k*_PB_N+j];
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

void myKernel(inputData *data, outputData* outD)
{
	int i = 0;//blockIdx.x * blockDim.x + threadIdx.x;
	for(;i<NUMBEROFTEST; i++){
    switch(data[i].choice){
        case 0:
            kernel_adi(data[i].ny, data[i].nx,outD[i].result, data[i].a, data[i].x);
            break;
        case 1:
            kernel_atax(data[i].nx, data[i].ny,data[i].a, data[i].x, outD[i].result, data[i].tmp);
            break;
	    case 2:
	        correlation(data[i].a,data[i].x,data[i].tmp,outD[i].result,data[i].nx,data[i].ny,data[i].float_n);
	        break;
	    case 3:
            kernel_covariance(data[i].nx, data[i].ny, data[i].float_n, data[i].a, outD[i].result, data[i].x);
            break;
       case 4:
            kernel_durbin(data[i].nx, data[i].a, data[i].x, data[i].tmp, data[i].beta, data[i].r, outD[i].result);
            break;
	   case 5:
            kernel_floyd_warshall(data[i].nx, outD[i].result);
            break;
     case 6:
            kernel_jacobi_2d_imper(data[i].ny, data[i].nx, outD[i].result, data[i].x);
            break;
       case 7:
            kernel_ludcmp(data[i].nx, data[i].a,data[i].x, outD[i].result, data[i].r);
            break;
        case 8:
            kernel_reg_detect(data[i].niter, data[i].nx, data[i].ny,data[i].a, data[i].x,outD[i].result, data[i].tmp, data[i].r);
            break;
        case 9:
            kernel_syr2k(data[i].nx, data[i].ny, data[i].float_n, data[i].n2, outD[i].result, data[i].a, data[i].x);
            break;
	default:
	    break;
    }
}
}
//************************************* Writing time in a FILE ******************************************
void writeFile(double time, char* fileName){
    FILE *fp;
    fp = fopen("CPUResults.txt", "a");
    if (fp == NULL){
        printf("Problem in a file");
        return;
    }
    fprintf(fp, "%s", fileName);
    fputs(": ", fp);
    fprintf(fp, "%f seconds\n", time);
    fclose(fp);
}
int main(int argc, char* argv[])
{
    inputData *dataCPU = (inputData*)malloc(sizeof(inputData)* NUMBEROFTEST);
    outputData *outD = (outputData*)malloc(sizeof(outputData)* NUMBEROFTEST);
    readingInput(dataCPU, outD);
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    myKernel(dataCPU,outD);
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;
    writeFile(time_spent,argv[1]);
    int i=0;
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
