# CIS431-LabAssignment3

2D Heat Equation with OpenMP CIS 431/531 Parallel Computing

Calculate heat distribution, optimizing by OpenMp.

For serial one, the compling command line is:

~~~
   g++ -o heat_equation_solver heat_equation_solver.cpp
~~~

For openmp one, the compling command line is:

~~~
   g++-6 -o omp_heat_equation_solver omp_heat_equation_solver.cpp -fopenmp
~~~

I've tested the output, listed below: （unit = second)

~~~
        p = 1   p = 2   p = 4   p = 8   p = 16
        
n=100   1.49    1.05    1.06    1.19    1.63 

n=1000  163.12  81.44   88.38   85.94   80.28

n=1e4   25806   6853.9  6922.5  6871.0  6835.9

n=1e5
~~~

I cannot run 1e5*1e5 in my Mac because the magnitude is too large to compute. However, from the gragh listed above, we can see when the magnitude is not quite large, optimization is not significant, while if the magnitude is large enough, multiple threads can run much faster.
