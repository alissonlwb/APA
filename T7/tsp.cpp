#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <math.h>
#include <list> 
#include <iterator>
#include <vector> 


using namespace std;

#define __INT_MAX__ 2147483647

// calcula distancia euclidiana entre dois pontos 
int euclidian_distance(double xi, double yi, double xj, double yj)
{

	double x = xi - xj; // calcula x e y pra elevar ao quadrado
	double y = yi - yj;
	int distance;

	distance = pow(x, 2) + pow(y, 2); // calcula distancia euclidiana
	distance = sqrt(distance);
	round(distance);                  

	return distance;

}

// heuristica de construcao do vizinho mais proximo 
void nearest_neighbour(int *adj_matrix)
{
	// vetor booleano pra marcar os visitados 
	vector<bool> visited_node(1500, false);
	
	// acumular o custo do caminho
	int cost = 0;
	
	// guardo o no atual 
	int curr_node = 0;
	
	// marca o no "0" visitado
	visited_node[curr_node] = true;

	// vistado anteriormente
	int past_visited = 0;
	
	// lista para os nos do caminho
	vector<int> path;
	path.push_back(curr_node);

	// enquanto o tamanho do vetor path for menor que 1500
	while(path.size() < 1500)
	{
		// min = maior valor possivel 
		int min = __INT_MAX__;
		for(int i = 0; i < 1500; ++i)
		{
			// se nó i nao tiver sido visitado, e o nó atual for menor que o minimo
			// adj_matrix[curr_node][i]
			if((!visited_node[i]) && (adj_matrix[curr_node*1500 + i] < min))
			{
				// minimo recebe o no atual
				min = adj_matrix[curr_node*1500 + i];
				// visitado anterior recebe i
				past_visited = i;
			}
		}

		// acumula valores de custo
		cost += min;
		
		// marca coluna j como visitada
		visited_node[past_visited] = true;
		// no atual vai ser o anterior
		curr_node = past_visited;
		// coloca o anterior na lista do caminho
		path.push_back(past_visited);
	}

	// imprime o custo total
	cout<<"Custo minimio total: "<<cost<<"\n";

	cout<<"Caminho: ";
	//imprime o caminho
	for (int i = 0; i < path.size(); ++i)
	{
		cout<<path[i]<<", ";
	}

	cout<<"0";
}


int main(int argc, char *argv[])
{

	// array pra posicoes x e y
	double pos_x[1500];
	double pos_y[1500];
	// contador
	int count = 0;
	
	// alocacao dinamica matriz[1500][1500]
	int *adj_matrix = new int[1500*1500];

	// abre o arquivo com os pontos x e y
	ifstream in("tsp1.txt");
	// pega 1500 valores
	while(count!=1500)
	{
		// pega os valores de x e y
		in >> pos_x[count];
  		in >> pos_y[count];
  		count++;		
	}

	for (int i = 0; i < 1500; i++)
	{
		for (int j = 0; j < 1500; j++)
		{
			//adj_matrix[i][j]
			adj_matrix[i*1500 + j] = euclidian_distance(pos_x[i], pos_y[i], pos_x[j], pos_y[j]);
		}
	}

	// chama heuristica de construcao do vizinho mais proximo passando a matriz de adjacencia
	nearest_neighbour(adj_matrix);

	// deleta a matriz alocada
	delete[] adj_matrix;
	return 0;
}



























