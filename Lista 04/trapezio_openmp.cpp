#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <math.h>
using namespace std;

int main(){
	int n;
	double a, b, h, trapeze;

	double t_start, t_end, t_total;

	double partial_sum(int a, double h, int n);
	double function(double x);

	t_start = omp_get_wtime();
	
	a = 0;
	b = 5;
     	n = 2048000000;
	//	n = 10;

	h = (b - a)/n;
	
	trapeze = 0.5*h*( function(a) + function(b) + 2*partial_sum(a, h, n) );
	
	printf("The area is: %lf\nStep: %lf\nSum: %lf\n", trapeze, h, partial_sum(a, h, n));

	t_end = omp_get_wtime();
	t_total = t_end - t_start;

	printf("The total time was %lf seconds.\n", t_total);

	return 0;
}

double partial_sum(int a, double h, int n){
	int i;
	double sum;
	static double x[5];
	
	double function(double x);
		
#pragma omp parallel for private(i) reduction(+:sum) schedule(static, 4)	
	for(i=1; i < n; i++){
		
		x[i] = a + i*h;
		
		sum = sum + function(x[i]);
//		printf("The total sum of the thread number %d for %d is: %lf\n", omp_get_thread_num(), i, sum);
	}
	
//	printf("Total: %lf\n", sum);
		
	return sum;
}

double function(double x){
	double func;
	
	func = x*x;

	return func;
}

