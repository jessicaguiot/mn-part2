#ifndef EquationSolver_hpp
#define EquationSolver_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdlib>

class EquationSolver {

public:

  double A[10][10], error, row;
  int ITER_MAX = 20;
  int n, i, j, k;
  std::vector<double> x;

  //construção matriz e vetor de iteração
  std::vector<double> vector_iter(std::vector<double> b) {
    for(i = 0; i < n; i++) {
        row = 1/A[i][i];
        //std::cout << row << "\n";
        for (j = 0; j < n; j++) {
            if (i != j) {
              A[i][j] *= row;
            }
         }

         b[i] = b[i]*row;
         x[i] = b[i];
         //print_matrix();
    }
    return x;
  }

  //metodo gaus-jacobi
  int metodo_gauss_jacobi(std::vector<double> b) {
    std::vector<double> v;

    for (int m : b) {
      v.push_back(0);
    }

    for (k = 0; k < ITER_MAX; k++) {
      for (i = 0; i < n; i++) {
        double soma = 0;
        for (j = 0; j < n; j++) {
            //std::cout << std::setprecision(3) << std::fixed << A[i][j] << '\n';
            if (i != j) {
              soma = soma + (A[i][j]*x[j]);
            }
        }

          v[i] = b[i] - soma;
          //print_vector(v);
      }

       double norma = calcula_norma(n, x, v);
       //print_vector(x);
       //std::cout << norma << "\n";
       if (norma <= error) {
         //print_vector(x);
         //std::cout << "\nNúmero de iterações: " << k << '\n';

         std::cout << "\n\nITERAÇÕES: " << k << "\n\n";
         print_vector(x);
         return 0;
       }
    }
    return 1;
  }

  //cálculo da norma para o critério de parada
  double calcula_norma(int n, std::vector<double> x, std::vector<double> v) {
    double norma;
    double normaNum = 0, normaDen = 0;
    for (i = 0; i < n; i++) {
      double t;
      t = std::abs(v[i]-x[i]);
      //std::cout << std::setprecision(4) << std::fixed << "T: " << t << '\n';
      if (t > normaNum) {
        normaNum = t;
      }
      if (std::abs(v[i]) > normaDen) {
        normaDen = std::abs(v[i]);
      }
      x[i] = v[i];
    }
    norma = normaNum/normaDen;
    //std::cout << std::setprecision(4) << std::fixed << "T: " << normaNum << '\n' << normaDen;
    return norma;
  }

  void print_matrix() {

    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
              std::cout << std::setprecision(2) << std::fixed << A[i][j] << "  ";
         }
         std::cout << '\n';
    }
  }

  void print_vector(std::vector<double> v) {
    for(i = 0; i < n; i++) {
      std::cout << std::setprecision(3) << std::fixed << v[i] << '\n';
    }
  }
};

#endif /*EquationSolver_hpp */
