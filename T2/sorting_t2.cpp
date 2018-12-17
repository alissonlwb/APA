// Algoritmo: Merge sort e Quick sort
// Aluno: Alisson Lacerda - 11228368

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

void quick_sort(int number[],int size){


}

void merge_sort(int number[],int size){

	
}

int main(){

	string input;
	int array[100000];// caso maximo 100000
	int linhas = 0;// indice das linhas do array
	int option;// opcao pra selecionar insertion ou selection sort

	cout << "Digite 1 para merge sort ou 2 pra quick sort: " << endl;
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

	// menu switch case
	switch(option){
		case 1:
			merge_sort(array, linhas);
			break;
		case 2:
			quick_sort(array, linhas);
			break;
		default:
			cout << "Opcao invalida, digite 1 ou 2";
			break;

	}
	
	// fecha arquivo
	file.close();

}