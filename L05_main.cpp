#include <stdio.h>
#include <math.h>
#include "rk4.h"
#include "winbgi2.h"

double a = -1;
double g = 9.81;
double l = 1;
double alfa0 = (acos(a))/4;
double m = 1;
double w0 = 0;
double h = 0.001;

void rhs_fun(double t, double *X, double *F);
void veuler(double t, double *X, double h, int n, void (*fun)(double, double*, double*), double *X1);

void main()
{
	double t = 0;
	double tt;
	double X[2];
	double X1[2] = {0, 0};
	int n = 2;
	double iter = 1/h;
	X[0] = w0;
	X[1] = alfa0;
	double met = 2;
	double E;
	
	printf("Wahadlo matematyczne\nWybierz 0 by uzyc metody Eulera.\nWybierz 1 by uzyc metody RK4\n");
	while((met != 0) && (met != 1))
	{
		scanf("%lf", &met);
	}
	if(met == 0)
	{
		printf("METODA EULERA\n");
	}
	else if(met == 1)
	{
		printf("METODA RK4\n");
	}
	printf("t=%.lf\nw=%lf\na=%lf\n", t, X[0], (X[1]/acos(a))*180);
	E = (m*pow(l, 2)/2)*(pow(X[0], 2))+(m*g*l*(1-cos(X[1])));
	printf("E=%lf\n\n", E);
	graphics(500, 500);
	scale(-90, -10, 90, 10);

	if(met == 0)
	{
		setcolor(4);
	}
	while(t<10000)
	{
		tt=t;
		for(int j=0; j<iter; j++)
		{
			if(met == 0)
			{
				tt=tt+h;
				veuler(tt, X, h, n, rhs_fun, X1);
			}
			else if(met == 1)
			{
				vrk4(tt, X, h, n, rhs_fun, X1);
			}
		}
		for(int i=0; i<n; i++)
		{
			X[i] = X1[i];
		}
		printf("t=%.lf\nw=%lf\na=%lf\n", t+1, X[0], (X[1]/acos(a))*180);
		point((X[1]/acos(a))*180, X[0]);

		E = (m*pow(l, 2)/2)*(pow(X[0], 2))+(m*g*l*(1-cos(X[1])));
		printf("E=%lf\n\n", E);
		t++;
	}
	wait();
}

void rhs_fun(double t, double *X, double *F)
{
	//t - czas	
	//X - tablica zmiennych zale¿nych
	//F - tablica do której zapisane zostan¹ obliczone prawe strony równañ ró¿niczkowych
	F[0] = (-g*sin(X[1]))/l;
	F[1] = X[0];
}

void veuler(double t, double *X, double h, int n, void (*fun)(double, double*, double*), double *X1)
{
	//t - zmienna niezale¿na
	//X - tabliva wartoœci zmiennych zale¿nych w kroku t
	//h - krok ca³kowania
	//n - rozmiar tablicy
	//fun - wskaŸnik do funkcji obliczaj¹cej prawe strony równañ
	//X1 - tablica do której zapisane zostan¹ wartoœci zmiennych zale¿nych w kroku t+h
	double F[2];
	fun(t, X, F);
	for(int i=0; i<n; i++)
	{
		X1[i] = X[i]+h*F[i];
	}
}