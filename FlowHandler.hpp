#ifndef FlowHandler_hpp
#define FlowHandler_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class FlowHandler {
public:
	string precisionString, deslocationString, columnsString;
	double precision, n, columnsNumber;
	bool shouldContinue = true;
	double b[20], A[][20];

	void startInteraction() {
		askForDeslocationValue();
		if(shouldContinue){
			askForMatrixColumnsValue();
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
		cout << "Bem vindo. \n\nInsira o quantidade n de deslocamentos: ";
		cin >> deslocationString;
		cout << "Você escolheu " << deslocationString << ".\n";
		cout << "Verificando..\n\n";
		if(isNumber(deslocationString)) {
			n = stoi(deslocationString);
			cout << "Ok, " << deslocationString << " é um valor válido.\n";
		} else {
			cout << deslocationString << " é inválido. Não é um número.\n";
			shouldContinue = false;
		}
	}

	void askForMatrixColumnsValue() {
		cout << "\n\nDigite a quantidade de colunas: ";
		cin >> columnsString;
		if(isNumber(columnsString)) {
			columnsNumber = stod(columnsString);
		} else {
			cout << "\n" << columnsString << " é inválido. Não é um número.\n";
			shouldContinue = false;
		}
	}

	void askForMatrixAValues() {
		cout << "\n\nValores da Matriz A\n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < columnsNumber; j++) {
				cout << "Digite o valor de A[" << i+1 << "][" << j+1 << "]: ";
				string value;
				cin >> value;
				if (isNumber(value)){
					A[i][j] = stod(value);
				} else {
					cout << "Número inválido!";
					shouldContinue = false;
				}
			}
		}
	}

	void askForBValues() {
		cout << "\n\nValores da Matriz B\n\n";
		for (int i = 0; i < n; i++) {
			cout << "Digite valor de B[" << i+1 << "]: ";
			string value;
			cin >> value;
			if (isNumber(value)){
				b[i] = stod(value);
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
		cout << "MATRIZ A: \n\n";
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < columnsNumber; j++) {
				cout << A[i][j] << "  ";
			}
			cout << "\n";
		}
		cout << "MATRIZ b: \n\n";
		for (int m = 0; m < n; m++) {
			cout << b[m];
			cout << "\n";
		}
	}

	void calculateAndPrintValues() {
		printMatrix();
	}
};

#endif /* FlowHandler_hpp */
