// Algoritmo: Selection Sort 
// Aluno: Alisson Lacerda - 11228368

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

// funcao selection_sort recebe array de numeros inteiros e o tamanho (size)
void selection_sort(int number[],int size){

	int aux, min;// variavel auxiliar e minima pra guardar valores durante a execucao
    
    // loop pra percorrer o array de numeros
    for(int i=0; i<size; i++){
        min = i;// vairavel minima vai receber o primeiro valor
        for(int j=i+1; j<size; j++){// comecando em j=i+1, percorrendo todo o array de numeros
            if(number[j] < number[min])// testa se o numero seguinte é menor que o numero atual
                min = j;
        }
        aux = number[i];// variavel auxiliar guarda o valor atual
        number[i] = number[min];// numero atual recebe numero com indice min, que pode ser i ou j
        number[min] = aux;// numero min recebe numero[i] guardado na variavel auxiliar
    }
    // loop pra imprimir todos os valores Pos(x) ; Num(y)
    for (int i = 0; i<size; i++){
        cout << "Pos(" << i+1 << ") ; Num(" << number[i] << ")" << endl;
    }

}

// funcao insertion_sort recebe array de numeros inteiros e o tamanho (size)
void insertion_sort(int number[],int size){

	// loop pra percorrer o array de numeros
   	for(int i=1; i<size; i++){
        int current = number[i];// variavel current recebe o numero com indice i
        int j=i-1;// variavel j corresponde ao indice anterior a i

        // loop testa se numero anterior é maior que o atual
        while((j >= 0) && (number[j] > current)){
            number[j+1] = number[j];// se for, o numero seguinte recebe o numero de indice j
            j--;// decrementa j
        }

        number[j+1] = current;// saiu do loop, numero[j+1] recebe o atual

    }

    // loop pra imprimir todos os valores Pos(x) ; Num(y) 
    for (int i = 0; i < size; ++i){
        cout << "Pos(" << i+1 << ") ; Num(" << number[i] << ")" << endl;
    }

}

int main(){

	string input;
	int array[100000];// caso maximo 100000
	int linhas = 0;// indice das linhas do array
	int option;// opcao pra selecionar insertion ou selection sort

	cout << "Digite 1 para selection sort ou 2 pra insertion sort: " << endl;
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
			selection_sort(array, linhas);
			break;
		case 2:
			insertion_sort(array, linhas);
			break;
		default:
			cout << "Opcao invalida, digite 1 ou 2";
			break;

	}
	
	// fecha arquivo
	file.close();

}