#ifndef EquationSolver_hpp
#define EquationSolver_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <iomanip>

class EquationSolver {

public:

  double A[10][10], x[10], b[10], error, row;
  int ITER_MAX = 10;
  int n, i, j, k;

  //construção matriz e vetor de iteração
  void vector_iter() {

    for(i = 0; i < n; i++) {
        row = 1/A[i][i];
        for (j = 0; j < n; j++) {
            if (i != j) {
              A[i][j] *= row;
            }
         }
         b[i] = b[i]*row;
         x[i] = b[i];
         //std::cout << std::setprecision(2) << std::fixed << x[i] << '\n';
    }
  }

  //metodo gaus-jacobi
  void metodo_gauss_jacobi() {
    double v[10];
    for (k = 0; k < ITER_MAX; k++) {
      for (i = 0; i < n; i++) {
        double soma = 0;
        for (j = 0; j < n; j++) {
            if (i != j) {
              soma = soma + (A[i][j]*x[j]);
            }
        }
        v[i] = b[i] - soma;
      }

       double norma = calcula_norma(n, x, v);
       if (norma <= error) {
         std::cout << "\n\n --- VETOR RESULTADO x --- \n\n";
         print_vector(x);
         std::cout << "\nNúmero de iterações: " << k << '\n';
         break;
       }
    }
  }

  //cálculo da norma para o critério de parada
  double calcula_norma(int n, double (x)[10], double (v)[10]) {

    double norma;
    double normaNum = 0.000, normaDen = 0.0000;
    for (i = 0; i < n; i++) {
      double t = abs(v[i] - x[i]);
      if (t > normaNum) {
        normaNum = t;
      }

      if (abs(v[i]) > normaDen) {
        normaDen = abs(v[i]);
      }
      x[i] = v[i];
    }

    return norma = (normaNum/normaDen);
  }

  void print_matrix() {

    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
              std::cout << std::setprecision(2) << std::fixed << A[i][j] << "  ";
         }
         std::cout << '\n';
    }
  }

  void print_vector(double (v)[10]) {
    for(i = 0; i < n; i++) {
      std::cout << v[i] << '\n';
    }
  }
};

#endif /*EquationSolver_hpp */
