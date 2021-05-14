#include <iostream>
using namespace std;

int main(){

	static double A[2048][2048], B[2048][2048], C[2048][2048];
	static double soma_C;
	int N, i, j, k;
	
	N = 2048;
	
	for(j=0; j<N; j++){
		for(i=0; i<N; i++){
			
			A[i][j] = (i*j)/3.e9;
			B[i][j] = (i*j)/5.e9;
			C[i][j] = 0.0;
		}
	}
	
	soma_C = 0.0;
	
	for(i=0; i<N; i++){
		for(k=0; k<N; k+=4){
			for(j=0; j<N; j++){
			
				C[i][j] = A[i][k]*B[k][j];
				C[i][j] = A[i][k+1]*B[k+1][j];
				C[i][j] = A[i][k+2]*B[k+2][j];
				C[i][j] = A[i][k+3]*B[k+3][j];
			}
		}
	}
	
	for(j=0; j<N; j++){
		for(i=0; i<N; i++){
		
			soma_C = soma_C + C[i][j];
		}
	}
	
	cout << soma_C << endl;
	
	return 0;
}
