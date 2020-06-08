#include <stdio.h>
#include <math.h>
#include "rk4.h"
#include "winbgi2.h"

double a = -1;
double g = 9.81;
double PI = acos(a);
double h = 0.001;
double R = -1;
double m = -1;
int t_max = 5;
double r=-0.05;


void rhs_fun(double t, double *X, double *F);
void dane(double *X);

void main()
{
	double t = 0;
	double tt;
	double X[2];
	double X1[2] = {0, 0};
	int n = 2;
	double iter = (1/h);
	int wykres = 0;
	double E;
	double omega;

	printf("Praca domowa - Zadanie 2\n\n");
	printf("Prosze podac warunki poczatkowe.\n");
	while(m <= 0)
	{
		printf("Masa kulki = ");
		scanf("%lf", &m);
		if(m <= 0)
		{
			printf("Masa kulki musi byc wieksza od 0.\n");
			scanf("%lf", &m);
		}
	}
	while(R <= 0)
	{
		printf("Promien krzywizny rampy = ");
		scanf("%lf", &R);
		if(R <= 0)
		{
			printf("Promien musi byc wiekszy od 0.\n");
			scanf("%lf", &R);
		}
	}
	while(r <= 0)
	{
		printf("Promien kuli = ");
		scanf("%lf", &r);
		if(r <= 0)
		{
			printf("Promien musi byc wiekszy od 0.\n");
			scanf("%lf", &r);
		}
	}
	dane(X);

	printf("\nProsze wybrac sposob wyswietlenia wynikow:\n\nAby uzyskac wykres wychylenia w czasie wybierz 1.\nAby uzyskac wykres predkosci katowej");
	printf(" w czasie wybierz 2.\nAby uzyskac wykres predkosci katowej i wychylenia wybierz 3.\nAby uzyskac wykres energii mechanicznej od czasu wybierz 4.\n");
	while((wykres < 1) || (wykres > 4))
	{
		scanf("%d", &wykres);
	}

	printf("t=%.lf\nw=%lf\na=%lf\n", t, X[0], (X[1]/acos(a))*180);
	
	graphics(500, 500);
	if(wykres == 1)
	{
		scale(0, -90, t_max, 90);
		setcolor(4);
	}
	else if(wykres == 2)
	{
		scale(0, -7.1, t_max, 7.1);
		setcolor(4);
	}
	else if(wykres == 3)
	{
		scale(-90, -7.1, 90, 7.1);
		setcolor(4);
	}
	else if(wykres == 4)
	{
		scale(0, 0, t_max, 20);
		setcolor(5);
	}

	while(t<t_max)
	{
		tt=t;
		for(int j=0; j<(iter/100); j++)
		{
			vrk4(tt, X, h, n, rhs_fun, X1);
			tt=tt+h;
			for(int i=0; i<n; i++)
			{
				X[i] = X1[i];
			}
		}
		
		

		omega = X[0]*(R/r);
		E = (0.2*m*pow(r, 2)*pow(omega, 2))+(m*g*(R)*(1-cos(X[1])));
		printf("t=%lf\nw=%lf\na=%lf\nE=%lf\n\n", t, X[0], (X[1]/acos(a))*180, E);
		
		if(wykres == 1)
		{
			point(t, (X[1]/PI)*180);
		}
		else if(wykres == 2)
		{
			point(t, X[0]);
		}
		else if(wykres == 3)
		{
			point((X[1]/PI)*180, X[0]);
		}
		else if(wykres == 4)
		{
			point(t, E);
		}
		t=t+0.01;
	}
	wait();
}

void rhs_fun(double t, double *X, double *F)
{
	F[0] = -(5*g*sin(X[1]))/(2*R);
	F[1] = X[0];
}

void dane(double *X)
{
	printf("Poczatkowe wychylenie = ");
	scanf("%lf", &X[1]);
	while((X[1] > 90) || (X[1] < -90))
	{
		printf("Podano nieprawidlowe wychylenie. Prosze podac poczatkowe wychylenie.\nPoczatkowe wychylenie =");
		scanf("%lf", &X[0]);
	}
	X[1] = (X[1]/180)*PI;

	printf("Poczatkowa predkosc katowa = ");
	scanf("%lf", &X[0]);

	while((X[0] == 0) && (X[1] == 0))
	{
		printf("Predkosc katowa i wychylenie nie moga byc jednoczesnie rowne 0.\n");
		dane(X);
	}
}
