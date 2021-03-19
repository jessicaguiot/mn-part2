#ifndef FlowHandler_hpp
#define FlowHandler_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "EquationSolver.hpp"

using namespace std;

class FlowHandler {
public:

	string precisionString, nString;
	long double precision, n, ITER_MAX;
	bool shouldContinue = true;
	vector<vector<long double> > matrix;
	EquationSolver equationSolver;

	void startInteraction() {

		askForNValue();

		if(shouldContinue){
			askForMatrixAValues();
		}

		if(shouldContinue){
			askForBValues();
		}

		if(shouldContinue){
			askForPrecisionValue();
		}

		if(shouldContinue) {
			askForIterValue();
		}

		calculateAndPrintValues();
	}

	bool isNumber(string s) {

		char* end = nullptr;
		double val = strtod(s.c_str(), &end);
		return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
	}

	void askForNValue() {

		cout << "Bem vindo. \n\nInsira a quantidade n: ";
		cin >> nString;
		cout << "Você escolheu " << nString << ".\n";
		cout << "Verificando..\n\n";
		if(isNumber(nString)) {
			n = stoi(nString);
			equationSolver.n = n;
			cout << "Ok, " << nString << " é um valor válido.\n";
		} else {
			cout << nString << " é inválido. Não é um número.\n";
			shouldContinue = false;
		}

		matrix.reserve(n); 
	}

	void askForMatrixAValues() {

		cout << "\n\nValores da Matriz A\n\n";

		for (int i = 0; i < n; i++) {

			vector<long double> row;
			for (int j = 0; j < n; j++) {

				cout << "Digite o valor de A[" << i+1 << "][" << j+1 << "]: ";

				string number;
				cin >> number;
				if (isNumber(number)){

					row.push_back(stod(number));
				} else {

					cout << "Número inválido!";
					shouldContinue = false;
				}
			}
			matrix.push_back(row);
		}
	}

	void askForBValues() {

		vector<long double> b;
		cout << "\n\nValores da Matriz b\n\n";

		for (int i = 0; i < n; i++) {
			cout << "Digite valor de b[" << i+1 << "]: ";

			string number;
			cin >> number;
			if (isNumber(number)){

				
				b.push_back(stod(number));
				matrix[i].push_back(b[i]);

			} else {

				cout << "Número inválido!";
				shouldContinue = false;
			}
		}
	}

	void askForPrecisionValue() {

		cout << "\n\nDigite a precisão desejada: ";
		cin >> precisionString;
		if (isNumber(precisionString)){
			precision = stod(precisionString);
			equationSolver.error = precision;
		} else {
			cout << "\n" << precisionString << " é inválido. Não é um número.\n";
			shouldContinue = false;
		}
	}

	void askForIterValue() {

		cout << "\n\nDigite o número max de iterações: ";

		string number;
		cin >> number;
		if (isNumber(number)){
			ITER_MAX = stod(number);
		} else {
			cout << "\n" << precisionString << " é inválido. Não é um número.\n";
			shouldContinue = false;
		}
	}

	void print_matrix(vector<vector<long double> > matrix) {

		cout << "\n--- MATRIZ --- \n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= n; j++) {
				std::cout << std::setprecision(2) << std::fixed << matrix[i][j] << "  ";
			}
			cout << "\n";
		} 
	}

	void print_vector(std::vector<long double> v) {

		std::cout << "\n-- VETOR RESULTADO -- \n";
		for(int i = 0; i < n; i++) {
			std::cout << std::setprecision(2) << std::fixed << v[i] << '\n';
		}
		cout << endl;
  	}

	void calculateAndPrintValues() {

		std::cout << "\n--- MÉTODO GAUSS-JACOBI --- \n";
		print_vector(equationSolver.gauss_jacobi(matrix, ITER_MAX)); 
    }
};

#endif /* FlowHandler_hpp */
