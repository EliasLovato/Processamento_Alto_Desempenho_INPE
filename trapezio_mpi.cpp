/* PARALLEL TRAPEZOIDAL RULE

Input: None.
Output: Estimate of the integral from a to b of f(x) using the trapezoidal rule and n trapezoids.

ALgorithm:
	1. Each process calculates "its" interval of integration.
	2. Each process estimates the integral of f(x) over its interval using the trapezoidal rule.
	3a. Each process != 0 sends its integral to 0.
	3b. Process 0 sums the calculations received from the individual processes and prints the result.
	
Note: f(x), a, b, and n are all hardwired.

*/

#include <iostream>
#include <math.h>
#include <mpi.h> // We'll be using MPI routines, definitions, etc.
using namespace std;

int main(int argc, char** argv){
	
	int id, nproc, n, local_n; // My process rank, the number of processes, number of trapezoids and the number of trapezoids for my calculation
	double a, b, h, local_a, local_b, accum, sum; // Left endpoint, Right endpoint, trapezoids base length, left endpoint and right endpoint of the my process, integral over my interval, and total integral
	
	int source, dest, tag; // Process sending integral, all messages go to 0
	double t_start, t_end, t_total; //Declare variables for timing
	
	a = 0;
	b = 5;
	n = 2048000000;
	dest = 0;
	tag = 0;
	
	MPI_Status status;
	
	// Calculate local integral
	double Trap(double local_a, double local_b, int local_n, double h);
	
	// Let the system do what it needs to start up MPI
	MPI_Init(&argc, &argv);
	
	// Get myy process rank
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	
	// Find out how many processes are being used
	MPI_Comm_size(MPI_COMM_WORLD, &nproc);
	
	if(id == 0){
		t_start = MPI_Wtime();
	}
	
	h = (b - a)/n;
	local_n = n/nproc;
	
// Length of each process's interval of integration = local_n*h. So my interval starts at:
	local_a = a + id*local_n*h;
	local_b = local_a + local_n*h;
	accum = Trap(local_a, local_b, local_n, h);
	
	// Add up the integral calculated by each process
	if(id == 0){
		sum = accum;
		
		for(source = 1; source < nproc; source++){
			MPI_Recv(&accum, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, &status);
			
			sum = sum + accum;
		}
	}
	else{
		MPI_Send(&accum, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
	}
	
// Print the result and stop the time
	if(id == 0){
		t_end = MPI_Wtime();
		t_total = t_end - t_start;
	
		printf("With n = %d trapezoids, our estimate", n);
		printf(" of the integral from %f to %f = %f\n", a, b, sum);
		printf("The total time was %f seconds.\n", t_total);
	}
		
// Shut down MPI
	MPI_Finalize();
	
}

double Trap(double local_a, double local_b, int local_n, double h){
	
	double accum, x; // Store result in integral
	int i;
	
	double function(double var); // Function we're integrating
	
	accum = ( function(local_a) + function(local_b) )/2;
	x = local_a;
	
	for(i = 1; i <= (local_n - 1); i++){
		x = x + h;
		accum = accum + function(x);
	}
	
	accum = accum*h;
	
	return accum;
}

double function(double var){
	double func;
	
//	func = sin(var) + var;
	func = var*var;

	return func;
}

