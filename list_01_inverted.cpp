#include <iostream>
using namespace std;


int main(){
  
  static double A[4096][4097], B[4096][4096], C[4096][4096], D[4096][4096];
  static double soma;
  int N, i, j;
  
  N = 4096;
  
  for(j=0; j<N; j++){
    for(i=0; i<N; i++){
      
      A[i][j] = i*j*1.;
      B[i][j] = i*j*2.;
      C[i][j] = i*j*5.;
      D[i][j] = 0.0;
    }
  }
  
  soma = 0.0;
  
  for(i=0; i<N; i++){
    for(j=0; j<N; j++){
    
      A[i][j+1] = B[i][j] + C[i][j];
      D[i][j] = A[i][j]*2.;
      
      soma = soma + D[i][j];
    }
  }
  
  cout << soma << endl;
  
  return 0;

}
