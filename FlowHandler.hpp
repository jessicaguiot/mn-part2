#ifndef FlowHandler_hpp
#define FlowHandler_hpp

#include <stdio.h>
#include <iostream>
#include "EquationSolver.hpp"

using namespace std;

class FlowHandler {
public:

	string precisionString, nString, colString;
	double precision, n, col;
	bool shouldContinue = true;
	double b[10], A[10][10];
	EquationSolver equationSolver;

	void startInteraction() {

		askForDeslocationValue();

		if(shouldContinue){
			askForColumnValue();
		}

		if(shouldContinue){
			askForMatrixAValues();
		}

		if(shouldContinue){
			askForBValues();
		}

		if(shouldContinue){
			askForPrecisionValue();
		}

		calculateAndPrintValues();
	}

	bool isNumber(string s) {

		char* end = nullptr;
		double val = strtod(s.c_str(), &end);
		return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
	}

	void askForDeslocationValue() {

		cout << "Bem vindo. \n\nInsira o quantidade n: ";
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
	}

	void askForColumnValue() {

		cout << "\n\nDigite o número de colunas da Matriz A: ";
		cin >> colString;
		if(isNumber(colString)) {
			col = stod(colString);
		} else {
			cout << "\n" << colString << " é inválido. Não é um número.\n";
			shouldContinue = false;
		}
	}

	void askForMatrixAValues() {

		cout << "\n\nValores da Matriz A\n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < col; j++) {
				cout << "Digite o valor de A[" << i+1 << "][" << j+1 << "]: ";
				string value;
				cin >> value;
				if (isNumber(value)){
					A[i][j] = stod(value);
					equationSolver.A[i][j] = A[i][j];
				} else {
					cout << "Número inválido!";
					shouldContinue = false;
				}
			}
		}
	}

	void askForBValues() {

		cout << "\n\nValores da Matriz b\n\n";
		for (int i = 0; i < n; i++) {
			cout << "Digite valor de b[" << i+1 << "]: ";
			string value;
			cin >> value;
			if (isNumber(value)){
				b[i] = stod(value);
				equationSolver.b[i] = b[i];
				equationSolver.x[i] = 0;
			} else {
				cout << "Número inválido";
				shouldContinue = false;
			}
		}
	}

	void askForPrecisionValue() {

		cout << "\n\nDigite a precisão desejada: ";
		cin >> precisionString;
		if (isNumber(precisionString)){
			precision = stod(precisionString);
		} else {
			cout << "\n" << precisionString << " é inválido. Não é um número.\n";
			shouldContinue = false;
		}
	}

	void printMatrix() {

		cout << "\nMATRIZ A: \n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < col; j++) {
				cout << A[i][j] << "  ";
			}
			cout << "\n";
		}
		cout << "\nMATRIZ b: \n\n";
		for (int m = 0; m < n; m++) {
			cout << b[m];
			cout << "\n";
		}
	}

	void calculateAndPrintValues() {

		equationSolver.vector_iter();
		//printMatrix();
	}
};

#endif /* FlowHandler_hpp */
