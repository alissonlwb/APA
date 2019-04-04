// Algoritmo: Heapsort
// Aluno: Alisson Lacerda - 11228368

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

// funcao heap() converte os valores de input[] em um heap
// de forma recursiva cria um heap maximo (P >= C) comecando de "i" (raiz)

// cria subarvore com tamanho "n" e raíz em "i" 
void heap(int input[], int n, int i)
{
	int maior = i;// maior vai ser a raíz
	int esquerda = 2*i + 1;
	int direita = 2*i + 2;
	int aux = 0;// utilizado pra troca

	// se folha da esquerda for maior que a raiz, maior = esquerda 
	if (esquerda < n && input[esquerda] > input[maior])
		maior = esquerda;

	// se folha da direita for maior que a raiz, maior = direita 
	if (direita < n && input[direita] > input[maior])
		maior = direita;

	// por fim, testa se o maior nao é raiz
	if (maior != i)
	{
		// se for troca os valores de input[i] e input[maior]		
		aux = input[i];
		input[i] = input[maior];
		input[maior] = aux;
		// faz recursao do heap pra subarvore tamanho "n" e raiz "maior"
		heap(input, n, maior);
	}
}

// heapsort() ordena a entrada (input[]) 
void heapsort(int input[], int n)
{
	int aux = 0;// utilizado pra troca

	// constroi o heap comecando pelo nós pais chamando 
	// o construtor heap() pra cada um deles, convertendo 
    // a entrada num heap maximo
	for (int i = n / 2-1; i >= 0; i--)
		heap(input, n, i);

	// retira os elementos do heap um por vez e por fim se obtem um vetor ordenado
	for (int i=n-1; i>=0; i--)
	{
		// move a raiz atual "i" pro final "0"
		// pega cada no raiz e coloca no fim do vetor
		aux = input[0];
		input[0] = input[i];
		input[i] = aux;
		// faz recursao do heap reduzido com tamanho "i" e raíz "0"
		// chama heap pra ter certeza que o resto dos elementos formam um heap maximo
		heap(input, i, 0);
	}
}

// funcao geral pra imprimir valores
void print_values(int input[], int size){

	for (int i = 0; i < size; ++i){
        cout << "Pos(" << i+1 << ") ; Num(" << input[i] << ")" << endl;
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