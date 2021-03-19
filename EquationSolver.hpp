#ifndef EquationSolver_hpp
#define EquationSolver_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

class EquationSolver {

public:

  long double error;
  int n, i, j, k;
  
  //cálculo da norma para o critério de parada
  long double calcula_norma(int n, vector<long double> x, vector<long double> v) {
    
    vector<long double> diff;
    diff.reserve(n); 

    for(k = 0; k < n; k++) 
      diff.push_back(fabs(x[k]-v[k])); 

    long double max1 = diff[0], max2 = fabs(v[0]);

    for (i = 1; i < n; i++) {

      if (diff[i] > max1) {
        max1 = diff[1];
      }   
      
      if (fabs(v[i]) > max2) {
        max2 = fabs(v[i]);
      }
    } 

    return max1/max2; 
  }

  vector<long double> gauss_jacobi(vector<vector<long double> > matrix, int ITER_MAX) {
 
    vector<vector<long double> > m = move(matrix);
    vector<long double> x; 

    for(i = 0; i < n; i++) {
      x.push_back(0);
      long double r = m[i][i];
      for (j = 0; j <= n ; j++) {
        m[i][j] = m[i][j] / r; 
      }
    }

    vector<long double> v;
    for(k = 0; k < n; k++)   
      v.push_back(m[k][n]);

    bool flag = true; 
    int iter = 0; 

    while(flag) {

      iter++; 

      for(i = 0; i < n; i++) {
      long double soma = 0;  
        for (j = 0; j < n; j++) {
          if (i != j) {
            soma = soma + x[j] * m[i][j];
          }
        }
        v[i] = m[i][n] - soma; 
      }

      if (calcula_norma(n, x, v) <= error || iter > ITER_MAX) {
         
        flag = false; 
        std::cout << "\n-- INTERAÇÕES -- \n" << iter << '\n';
      } 

      for(k = 0; k < n; k++){
        x[k] = v[k]; 
      }       
    }
 
    return x;   
  }

  bool line_criterion(vector<vector<long double> > matrix) {

    bool converge = true; 

    for(i = 0; i < n; i++) {
      long double pivo = matrix[i][i]; 
      long double soma = 0; 
      for (j = 0; j < n; j++) {
        if (i != j) {
           soma += matrix[i][j];
        }
      }
      if (pivo < soma) {
        converge = false; 
      }
    }
    return converge;
  }
  
};

#endif /*EquationSolver_hpp */
