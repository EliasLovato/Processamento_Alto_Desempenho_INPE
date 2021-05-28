#include <iostream>
#include <math.h>
#include <mpi.h>
using namespace std;

int main(){
	int n;
	double a, b, h, trapezio;

	double soma(int x0, double passo, int interval);
	double funcao(double var);
	
	a = -3;
	b = 8;
	n = 5;

	h = (b - a)/n;
	
	trapezio = 0.5*h*( funcao(a) + funcao(b) + 2*soma(a, h, n) );
	
	cout << "A área é: " << trapezio << endl;
	cout << "Passo: " << h << endl;
	cout << "Soma: " << soma(a, h, n) << endl;

	return 0;
}

double soma(int x0, double passo, int interval){
	int i;
	double sum;
	static double x[5];
	
	double funcao(double var);
	
	sum = 0;
	
	for(i=1; i < interval; i++){
		x[i] = x0 + i*passo;
		
		sum = sum + funcao(x[i]);
	}

	return sum;
}

double funcao(double var){
	double func;
	
	func = sin(var) + var;

	return func;
}
