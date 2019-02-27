// Algoritmo: Heapsort
// Aluno: Alisson Lacerda - 11228368

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

void heap(int input[], int n, int i)
{
   int maior = i;
   int esquerda = 2*i + 1;
   int direita = 2*i + 2;

   if (esquerda < n && input[esquerda] > input[maior])
     maior = esquerda;

   if (direita < n && input[direita] > input[maior])
     maior = direita;

   if (maior != i)
   {
     swap(input[i], input[maior]);
     heap(input, n, maior);
   }
}

int main(){

	string input;
	int size = 100000;
	int array[100000];// caso maximo 100000
	int linhas = 0;// indice das linhas do array
	int option;// opcao pra selecionar insertion ou selection sort

	cout << "Digite 1 para começar o HEAPSORT: " << endl;
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

	// menu switch case
	switch (option){
		case 1:
			heapsort(array, linhas);
			print_values(array, linhas);
			break;
		case 2:
			// empty
			break;
		default:
			cout << "Opcao invalida, digite 1 ou 2";
			break;

	}
	
	

}