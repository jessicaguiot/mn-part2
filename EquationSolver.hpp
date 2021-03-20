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
  long double norm_calculator(int n, vector<long double> x, vector<long double> v) {
    
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

      if (norm_calculator(n, x, v) <= error || iter > ITER_MAX) {
         
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
  
  // CALCULO SEIDEL
  vector<long double> gaussSeidel(vector<vector<long double> > matrix, int n, long double error) {
      vector<vector<long double> > m = move(matrix);
      vector<long double> x;
      x.push_back(0); x.push_back(0); x.push_back(0);
      for (int i = 0; i < n; i++) {
          long double r = m[i][i];
          for (int j = 0; j < n + 1; j++)
              m[i][j] = m[i][j] / r;
      }
      vector<long double> s;
      s.push_back(m[0][n]); s.push_back(m[1][n]); s.push_back(m[2][n]);
      bool flag = true;
      while (flag) {
          for (int i = 0; i < n; i++) {
          long double soma = 0;
              for (int j = 0; j < n; j++) {
                  if (i != j) {
                      soma = soma + s[j] * m[i][j];
                  }
              }
              s[i] = m[i][n] - soma;
          }
          if (norm_calculator(n, s, x) <= error)
              flag = false;

          for (int i = 0; i < n; i++)
              x[i] = s[i];
      }
      return x;
  }

  // GERADORA DE COLUNAS DE MATRIZES IDENTIDADES
  // columnOrder: Vai de 1 a size
  vector<long double> matrixIdentityGenerator(int columnOrder, int size) {
      vector<long double> resultIdentityColumn; 
      for (int i = 0; i <= size - 1; i++) {
        if (i == columnOrder - 1) {
          resultIdentityColumn.push_back(1);
        } else {
          resultIdentityColumn.push_back(0);
        }
      }
      for (int i = 0; i < 4; i++) {
        cout << resultIdentityColumn[i];
      }
      return resultIdentityColumn;
  }

  vector<long double> multiply(vector<vector<long double> > matrix, vector<long double> b) {

    vector<vector<long double> > m = move(matrix);
    vector<long double> res; 

    for (i = 0; i < n; i++) {
      long double sum = 0;
      for (j = 0; j < n; j++) {
        sum += m[i][j] * b[j];
      }
      res.push_back(sum);
    }   

    return res;  
  }

};

#endif /*EquationSolver_hpp */
