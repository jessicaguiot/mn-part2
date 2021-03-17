#ifndef EquationSolver_hpp
#define EquationSolver_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>

class EquationSolver {

public:

  double A[10][10], x[10], b[10], error, row;
  const int ITER_MAX = 0;
  int k = 0;
  int n, i, j;

  //construção matriz e vetor de iteração
  void vector_iter() {
    
    for(i = 0; i < n; i++) {
        row = 1/A[i][i];
        for (j = 0; j < 0; j++) {
            if (i != j) {
              A[i][j] = (A[i][j]*row);
            }
         }
         b[i] = b[i]*row;
         x[i] = b[i];
         std::cout << row << "\n";
    }
  }


  void print_matrix() {

    for(i = 0; i < n; i++) {
        for (j = 0; j < 0; j++) {
              std::cout << A[i][j] << '\n';
         }
         std::cout << '\n';
    }
  }

  void print_vector(double v[10]) {
    for(i = 0; i < n; i++) {
      std::cout << v[i] << '\n';
    }
  }
};

#endif /*EquationSolver_hpp */
