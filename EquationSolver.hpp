#ifndef EquationSolver_hpp
#define EquationSolver_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <numeric>

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
      for (j = 0; j < n + 1; j++) {
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
        iter = 0;
      } 

      for(k = 0; k < n; k++){
        x[k] = v[k]; 
      }       
    }
 
    return x;   
  }

  //confere se a matriz passa no critério das linhas
  bool line_criterion(vector<vector<long double> > matrix) {

    bool converge = true; 
    for(i = 0; i < n; i++) {
      long double pivo = fabs(matrix[i][i]); 
      long double soma = 0; 
      for (j = 0; j < n; j++) {
        if (i != j) {
           soma += matrix[i][j];
        }
      }
      if (pivo <= fabs(soma)) {
        converge = false; 
      }
    }
    return converge;
  }

  // confere se a matriz passa no critério de Sassenfeld
  bool sassenfeldCriteria(vector<vector<long double> > matrix) {
    vector<long double> betasArray;
    int line = 1;

    for (int i = 0; i < matrix.size(); i++) {
      long double newBeta = getBetaForLine(matrix[i], betasArray, line);
      line++;
      betasArray.push_back(newBeta);
      if (newBeta >= 1) {
        return false;
      }
    }
    return true;
  }

  long double getBetaForLine(vector<long double> arrayValues, vector<long double> betasArray, int line) {
    long double beta = 0.0;
    int betasArraySize = betasArray.size();
    vector<long double> tmpVector;
    long double sum = 0;

    for (int i = 0; i < arrayValues.size(); i++) {
      if (i <= betasArraySize - 1) {
        tmpVector.push_back(fabs(arrayValues[i] * betasArray[i]));
      } else if (!(i == line -1)) {
        tmpVector.push_back(fabs(arrayValues[i]));
      }
    }

    beta = std::accumulate(tmpVector.begin(), tmpVector.end(), sum) / arrayValues[line - 1];
    return beta;
  }


  
  // CALCULO SEIDEL
  vector<long double> gaussSeidel(vector<vector<long double> > matrix, int n, long double error, int ITER_MAX) {
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
      int iter = 0; 
      while (flag) {
          iter++;
          for (int i = 0; i < n; i++) {
          long double soma = 0;
              for (int j = 0; j < n; j++) {
                  if (i != j) {
                      soma = soma + s[j] * m[i][j];
                  }
              }
              s[i] = m[i][n] - soma;
          }
          if (norm_calculator(n, x, s) <= error || iter > ITER_MAX) {
              flag = false;
              std::cout << "\n-- ITERAÇÕES -- \n" << iter << '\n';
          }
          for (int i = 0; i < n; i++)
              x[i] = s[i];
      }
      return x;
  }

  // GERADORA DE COLUNAS DE MATRIZES IDENTIDADES
  // columnOrder: Vai de 1 a size
  vector<long double> matrixIdentityGenerator(int columnOrder, int size) {
      vector<long double> resultIdentityColumn; 
      for (int i = 0; i < size; i++) {
        if (i == columnOrder - 1) {
          resultIdentityColumn.push_back(1);
        } else {
          resultIdentityColumn.push_back(0);
        }
      }
      return resultIdentityColumn;
  }

  //JUNTADOR DE COLUNAS + MATRIZES
  //PARAMETRO: MATRIZ e COLUNA
  //RETORNA MATRIZ NxN+1
  vector<vector<long double> > columnAppenderToMatrix(vector<vector<long double> > matrix, vector<long double> column) {
    vector<vector<long double> > newMatrix = move(matrix);
    newMatrix.push_back(column);

    return newMatrix;
  }

  vector<vector<long double> > columnAppender(vector<vector<long double> > matrix, vector<long double> column) {
    vector<vector<long double> > newMatrix = move(matrix);
  
    for (i = 0; i < n; i++) {
       newMatrix[i].push_back(column[i]);
    }

    return newMatrix;
  }



  // USA O METODO DE SEIDEL E FAZ TODAS AS CHAMADAS NECESSARIAS
  // A OUTRAS FUNCOES
  vector<long double> getAnswerUsingSeidel( int matrixOrder, 
                                            vector<vector<long double> > matrix, 
                                            vector<long double> b, 
                                            long double error,
                                            int ITER_MAX) {

    vector<long double> answer;
    vector<vector<long double> > inverse;
    int currentColumnOfIdentityMatrix = 1;

    for (int i = 0; i < matrixOrder; i++) {
      // PEGA COLUNA DA IDENTIDADE
      vector<long double> identityColumnToBeAppended = matrixIdentityGenerator(currentColumnOfIdentityMatrix, matrixOrder);
      
      // JUNTA COM MATRIZ
      vector<vector<long double> > appendedMatrixAndIdentity = columnAppender(matrix, identityColumnToBeAppended);

      // RESOLVE ATUAL CASO COM SEIDEL
      vector<long double> seidel = gaussSeidel(appendedMatrixAndIdentity, matrixOrder, error, ITER_MAX);
      inverse.push_back(seidel);
      currentColumnOfIdentityMatrix++;
    }

    print_matrix(inverse);

    answer = multiply(matrixOrder, inverse, b);
    return answer;
  }

  vector<long double> getAnswerUsingJacobi(int matrixOrder, vector<vector<long double> > matrix, vector<long double> b, long double ITER_MAX) {
    
    vector<long double> answer; 
    vector<vector<long double> > inverse;
    int currentColumnOfIdentityMatrix = 1;

    for (int i = 0; i < matrixOrder; i++) {
      
      // PEGA COLUNA DA IDENTIDADE
      vector<long double> identityColumnToBeAppended = matrixIdentityGenerator(currentColumnOfIdentityMatrix, n);

      // JUNTA COM MATRIZ
      vector<vector<long double> > appendedMatrixAndIdentity = columnAppender(matrix, identityColumnToBeAppended);

      //RESOLVE ATUAL CASO COM JACOBI
      vector<long double> jacobi = gauss_jacobi(appendedMatrixAndIdentity, ITER_MAX);
      inverse.push_back(jacobi);
      currentColumnOfIdentityMatrix++;
    }

    answer = multiply(matrixOrder, inverse, b);

    print_matrix(inverse);

    return answer; 
  }

  void print_vector(std::vector<long double> v) {

		std::cout << "\n-- VETOR RESULTADO -- \n";
		for(int i = 0; i < n; i++) {
			std::cout << std::setprecision(2) << std::fixed << v[i] << '\n';
		}
		cout << endl;
  }

  	void print_matrix(vector<vector<long double> > matrix) {

		cout << "\n--- MATRIZ --- \n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << std::setprecision(5) << std::fixed << matrix[j][i] << "  ";
			}
			cout << "\n";
		} 
	}

  vector<long double> multiply(int n, vector<vector<long double> > matrix, vector<long double> b) {

    vector<vector<long double> > m = move(matrix);
    vector<long double> res; 

    for (i = 0; i < n; i++) {
      long double sum = 0;
      for (j = 0; j < n; j++) {
        sum = sum + m[j][i] * b[j];
      }
      res.push_back(sum);
    }   

    return res;  
  }

};

#endif /*EquationSolver_hpp */
