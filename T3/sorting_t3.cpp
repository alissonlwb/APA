// Algoritmo: Counting sort e Radix sort
// Aluno: Alisson Lacerda - 11228368

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

// funcoes pro counting sort (counting_sort)

void counting_sort(int number[], int output[], int size, int k){

	int count[size];

	// zera o vetor auxiliar
	for (int i = 0; i < k; i++){
		count[i] = 0;
	}

	// contagem dos numeros
	for (int i = 0; i < k; i++){
		count[number[i]] = count[number[i]]+1;

	}

	// contagem dos numeros menores ou iguais
	for (int i = 1; i < size; i++){
		count[i] = count[i] + count[i-1];
	}

	// percorre de tras pra frente pra preencher vetor auxiliar e de saida
	for (int i = k-1; i >= 0; i--){
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

int main(){

	string input;
	int size = 100000;
	int array[100000];// caso maximo 100000
	int linhas = 0;// indice das linhas do array
	int option;// opcao pra selecionar insertion ou selection sort

	cout << "Digite 1 para COUNTING SORT ou 2 pra RADIX SORT: " << endl;
	cin >> option;

	cout << "Arquivo com os casos de teste: " << endl;
	cin >> input;

	// leitura do arquivo
	ifstream file;
	file.open(input);
	char output[1000];

	if (file.is_open()){
		while (!file.eof()){
			file >> output;
			array[linhas] = atoi(output);// cada numero vai pra uma linha do array
			linhas++;// incrementa linha pra pegar o proximo numero e por na proxuma linha do array
		}
	}

	// fecha arquivo
	file.close();

	// vetor de saida com numero de linhas do arquivo
	int saida[linhas];

	// menu switch case
	switch (option){
		case 1:
			counting_sort(array, saida, size, linhas);
			print_values(saida, linhas);
			break;
		case 2:
			//radix_sort(array, linhas);
			//print_values(array, linhas);
			break;
		default:
			cout << "Opcao invalida, digite 1 ou 2";
			break;

	}
	
	

}