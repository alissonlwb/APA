// Algoritmo: Counting sort e Radix sort
// Aluno: Alisson Lacerda - 11228368

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

// funcoes pro counting sort

void Counting_Sort(int number[], int output[], int size, int k){

	int count[size];


	for (int i = 0; i < k; i++){
		count[i] = 0;
	}

	for (int i=0; i < k; i++){
		count[number[i]] = count[number[i]]+1;

	}

	for (int i=1; i < size; i++){
		count[i] = count[i] + count[i-1];
	}

	for (int i=k-1; i >= 0; i--){
		output[count[number[i]]-1] = number[i];
		count[number[i]] = count[number[i]]-1;

	}
}

// funcao geral pra imprimir valores
void print_values(int number[], int size){

	for (int i = 0; i < size; ++i){
        cout << "Pos(" << i+1 << ") ; Num(" << number[i] << ")" << endl;
    }

}