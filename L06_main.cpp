#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

void HilbertMatrix(int N, double **H);
void displayMatrix(int N, double **H);
void computeVec(int N, double **H, double *b);
void plotVec(int N, double *v);

void main()
{
	int N=9;
	double **H;
	H = (double**)malloc(N*sizeof(double*));
	for(int i=0; i<N; i++)
	{
		H[i] = (double*)malloc(N*sizeof(double));
	}

	double *x;
	x = (double*)malloc(N*sizeof(double));

	double *b;
	b = (double*)malloc(N*sizeof(double));
	for(int i=0; i<N; i++)
	{
		b[i] = 0;
	}

	HilbertMatrix(N, H);
	displayMatrix(N, H);
	computeVec(N, H, b);
	gauss(N, H, x, b);

	printf("\n\n");
	plotVec(N, x);
}

void HilbertMatrix(int N, double **H)
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			H[i][j] = (1.0/(1+i+j));
		}
	}
}

void displayMatrix(int N, double **H)
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			printf("%.4lf\t", H[i][j]);
		}
		printf("\n");
	}
}

void computeVec(int N, double **H, double *b)
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			b[i] = b[i] + H[i][j];
		}
	}
}

void plotVec(int N, double *v)
{
	for(int i=0; i<N; i++)
	{
		printf("%lf\n", v[i]);
	}
}
