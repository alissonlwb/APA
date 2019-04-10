#include <iostream>
#include <algorithm>
#include <fstream>
#include <stdlib.h>

using namespace std;

// recebe numero de produtos, capacidade da mochila, pesos e valores
int MochilaInteira(int n, int M, int pesos[], int valores[])
{	
	// array de inteiros pra representar a tabela 
	int V[n + 1][M + 1];

	// inicializando primeira linha com 0 
	for(int w = 0; w <= M; w++)
    {
        V[0][w] = 0;
    }

    // inicializando primeira coluna com 0
	for(int i = 1; i <= n; i++)
    {
		V[i][0] = 0;
	}

	// loop pra linha
	for(int i = 1; i <= n; i++)
	{
		// loop pra coluna
		for(int w = 1; w <= M; w++)
		{
			// se peso do elemento i - 1 <= valor de w, ele pode fazer parte da solução
			if(pesos[i - 1] <= w)
			{   
				// elemento da tabela recebe valor maximo
				V[i][w] = max(valores[i - 1] + V[i - 1][w - pesos[i - 1]], V[i - 1][w]);
			}
			 
			// se peso do elemento i - 1 > w, pega valor da linha superior, coluna w
			else
			{
				V[i][w] = V[i - 1][w]; 
			}
		}
	}
	// retorna o valor máximo colocado na mochila
	return V[n][M];
}

int main(void)
{
    int M;
    int n;
    int ord[100000];

    // leitura do arquivo
    ifstream in;
    in.open("mochila01.txt");
    char numero[10];
    int fim = 0;
    while(!in.eof())
    {
        in >> numero;
        ord[fim] = atoi(numero);
        fim++;
    }

    // pega valor de n e M
    n = ord[0];
    M = ord[1];

	int pesos[n];
    int valores[n];
    int j=0;

    // preenche os vetores de pesos e valores
    for (int i=2; i < 2*n+2; i = i+2)
    {
        pesos[j] = ord[i];
        valores[j] = ord[i+1];
        j++;
    }

    // chama funcao da mochila inteira e imprime o valor retornado por ela
    cout << "Valor: " <<  MochilaInteira(n,M,pesos,valores) << endl;
    return 0;
}
