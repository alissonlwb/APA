// Algoritmo: Merge sort e Quick sort
// Aluno: Alisson Lacerda - 11228368

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

// funcoes pro quick sort

// recebe array de inteiros, indice de inicio e fim
void quick_sort(int number[], int inicio, int fim){

	int i, j, pivo, aux;// variaveis auxiliares
	i = inicio;
	j = fim-1;
	pivo = number[(inicio + fim) / 2];// pivo = numero do meio

	while (i <= j){

			// enquanto numero inicial for menor que pivo e menor que o final, incrementa
            while (number[i] < pivo && i < fim){
                i++;
            }

            // enquanto numero final for maior que pivo e maior que o inicial, decrementa
            while (number[j] > pivo && j > inicio){
                j--;
            }

            if (i <= j){
                aux = number[i];// passa pra variavel auxiliar
                number[i] = number[j];
                number[j] = aux;// faz a troca
                i++;
                j--;
            }
    }

    // saiu do loop e j maior que inicio, faz o quicksort comecando em inicio ate j+1
	if (j > inicio)
        quick_sort(number, inicio, j+1); 

    // saiu do loop e i menor que fim, faz o quicksort comecando em i até fim
	if (i < fim)
		quick_sort(number, i, fim);

}


// funcoes pro merge sort

// recebe array de inteiros, indice de inicio, meio e fim e array de inteiros auxiliar
void join(int number[], int inicio, int meio, int fim, int aux[]){
    
    int esquerda = inicio;
    int direita = meio;
    
    // percorre do inicio ao fim testando se (ESQ < MEIO) && ((DIR >= FIM) OU (NUMERO ESQ < NUMERO  DIR))
    for (int i = inicio; i < fim; i++) {
        if ( (esquerda < meio) && ((direita >= fim) || (number[esquerda] < number[direita])) ) {
            aux[i] = number[esquerda];// condicao satisfeita, vetor auxiliar recebe numero da esquerda
            esquerda++;// incrementa indice da esquerda
        }
        // se nao, vetor auxiliar recebe numero da direita
        else {
            aux[i] = number[direita];
            direita++;// incrementa indice da direita
        }
    }
    
    // manda os valores do vetor auxiliar de volta ao original
    for(int i = inicio; i < fim; ++i) {
        number[i] = aux[i];
    }
}

// recebe array de inteiros, indice de inicio e fim e array de inteiros auxiliar
void merge(int number[], int inicio, int fim, int aux[]){

	// se a condicao for satisfeita, terminou e retorna
	if ((fim - inicio) < 2) 
		return;

	// media do inicio + fim pra achar o meio
    int meio = ((inicio + fim)/2);

    // merge inicio e meio
    merge(number, inicio, meio, aux);
    
    // merge inicio e fim
    merge(number, meio, fim, aux);

    // junta tudo
    join(number, inicio, meio, fim, aux);

	
}

// faz o merge sort
void merge_sort(int number[], int size){

	// cria vetor auxiliar vazio pra passar pra funcao merge
    int aux[size];

    merge(number, 0, size, aux);
}

// funcao geral pra imprimir valores
void print_values(int number[], int size){

	for (int i = 0; i < size; ++i){
        cout << "Pos(" << i+1 << ") ; Num(" << number[i] << ")" << endl;
    }

}

int main(){

	string input;
	int array[100000];// caso maximo 100000
	int linhas = 0;// indice das linhas do array
	int option;// opcao pra selecionar insertion ou selection sort

	cout << "Digite 1 para QUICK SORT ou 2 pra MERGE SORT: " << endl;
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
	switch (option){
		case 1:
			quick_sort(array, 0, linhas);
			print_values(array, linhas);
			break;
		case 2:
			merge_sort(array, linhas);
			print_values(array, linhas);
			break;
		default:
			cout << "Opcao invalida, digite 1 ou 2";
			break;

	}
	
	// fecha arquivo
	file.close();

}