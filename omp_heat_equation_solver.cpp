
// g++-6 -o omp_heat_equation_solver omp_heat_equation_solver.cpp -fopenmp
#include <chrono>
#include <iostream>
#include <algorithm>
#include <omp.h>
using namespace std;

typedef std::chrono::high_resolution_clock Clock;

int heat_equation_cal(int n, int num_of_threads){

	// Initiate variable
	double c = 0.1;
	double ds = 1.0 / (n+1);
	double dt = (ds)*(ds) * 1.0 / (4*c);

  	// Set up 2D array
  double** input_temp = new double*[n+2];
  for(int i = 0; i < n+2; ++i){
  	input_temp[i] = new double[n+2];  
  }  	
	double** output_temp = new double*[n+2];
	for(int i = 0; i < n+2; ++i){
		output_temp[i] = new double[n+2];
	}
    	
    // Initialization
    for (int i =0; i < n+2; ++i){
    	for (int j=0; j < n+2; ++j){
    		if(i <= n & j <= n & i > 0 & j > 0){
    			if (i ==1 | i == n | j == 1 | j == n){
    				input_temp[i][j] = 100;
    				output_temp[i][j] = 100;
    			}else{
    				input_temp[i][j] = -100;
    				output_temp[i][j] = -100;
    			}
    		}else{
    			input_temp[i][j] = 0;
    			output_temp[i][j] = 0;
    		}
    	}
	}
  int i, j;
  auto t1 = Clock::now();

	// Calculation
  for ( int iter = 0; iter < 10000 ; iter++ ) {	
    #pragma omp parallel for schedule(static) shared(output_temp, input_temp) private(i, j) num_threads(num_of_threads) 
    for ( int i = 1; i < n +1; ++ i ) {
      for ( int j = 1; j < n +1; ++ j) {
				output_temp[i][j] = input_temp[i][j]+c*dt/(ds*ds)*(input_temp[i+1][j]+input_temp[i-1][j]-4*input_temp[i][j]+input_temp[i][j+1]+input_temp[i][j-1]);
			}
		}
	 swap(input_temp, output_temp);
    
	}

  auto t2 = Clock::now();

  double timer = chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1000000000.0;
  cout << "n = " << n << ", threads = " << num_of_threads << endl;
  cout << "Runtime: "
    << timer
    << " nanoseconds" << std::endl;

  return 0; 
}

int main(){

  int n[] = {100, 1000, 10000, 100000};
  int threads[] = {1, 2, 4, 8, 16};
  for (int i =0 ;i < 4; i++){
    for (int j=0 ; j < 5; j++ ){
      heat_equation_cal(n[i], threads[j]);
    }
  }

	return 0;
}