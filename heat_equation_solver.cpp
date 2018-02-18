
// g++ -o heat_equation_solver heat_equation_solver.cpp

#include <iostream>
#include <algorithm>
using namespace std;

int heat_equation_cal(int n, int niters){

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

	// Calculation
	for ( int iter = 0; iter < niters ; iter++ ) {	
		for ( int i = 1; i < n +1; ++ i ) {
			for ( int j = 1; j < n +1; ++ j) {
				output_temp[i][j] = input_temp[i][j]+c*dt/(ds*ds)*(input_temp[i+1][j]+input_temp[i-1][j]-4*input_temp[i][j]+input_temp[i][j+1]+input_temp[i][j-1]);
			}
		}
		swap(input_temp, output_temp);
	}

  return 0; 
}

int main(){
	heat_equation_cal(5, 10000);
	return 0;
}