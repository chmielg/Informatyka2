#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rk4.h"

double analitycznie(double t0, double t, double y0);
double euler(double t0, double y0, double h, int n, double (*f)(double, double));
double f(double t0, double y0);

double lambda = 1;

void main()
{
	double t0, y0, h, t, wynik, epseu, epsrk, an;
	int n;
	FILE *plik;
	plik = fopen("wyniki.txt", "w");
	
	printf("Rozpatrujemy zagadnienie:\n\n");
	printf("y' = l*y(t)\ny(t0)=y(0)\n");

	t0 = 1; y0 = 1; n = 1;
	
	fprintf(plik, "Liczba krokow:\t Dlugosc kroku:\tBlad metody Eulera:\tBlad metody RK4:\n");
	while(n <= 64)
	{
		h = 1.0/n;
		printf("\n\n\nn=%d\n", n);

		t = t0+h*n;
		y0=1;
		an = analitycznie(t0, t, y0);
		printf("Wynik metody analitycznej: %lf\n", an);
		
		printf("METODA EULUERA\n");
		wynik = euler(t0, y0, h, n, f);
		printf("Wynik metody Eulera: %lf\n", wynik);
		epseu = (abs(wynik-an)/abs(an));
		
		printf("METODA RUNGEGO-KUTTY\n");
		for(int i=0; i<n; i++)
		{
			y0 = rk4(t, y0, h, f);
			printf("t%d=%lf\n", i+1, t0);
			printf("y%d=%lf\n", i+1, y0);
			epsrk = (abs(y0-an))/(abs(an));
			printf("eps%d=%lf\n\n", i+1, epsrk);
		}
		printf("Wynik metody Rungego-Kutty: %lf\n", y0);
		fprintf(plik, "%d\t\t%lf\t%lf\t\t%lf\n", n, h, epseu, epsrk);
		n = n*2;
	}
}

double analitycznie(double t0, double t, double y0)
{
	return y0*exp(lambda*(t-t0));
}

double euler(double t0, double y0, double h, int n, double (*f)(double, double))
{
	double eps, t, an;
	t = t0+n*h;
	an = y0*exp(lambda*(t-t0));
	for(int i=0; i<n; i++)
	{
		t0 = t0+h;
		printf("t%d=%lf\n", i+1, t0);
		y0 = y0+h*f(t0, y0);
		printf("y%d=%lf\n", i+1, y0);
		eps = (abs(an-y0))/(abs(an));
		printf("eps%d=%lf\n\n", i+1, eps);
	}
	return y0;
}

double f(double t0, double y0)
{
	return lambda*y0;
}