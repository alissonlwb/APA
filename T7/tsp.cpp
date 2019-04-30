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
	// imprime o caminho
	for (int i = 0; i < path.size(); ++i)
	{
		cout<<path[i]<<", ";
	}
	// imprime o nó inicial novamente
	cout<<"0";
}

int calcutale_cost()
{
	int cost = 0;

	
}



// 2optSwap(route, i, k) {
//      1. take route[1] to route[i-1] and add them in order to new_route
//      2. take route[i] to route[k] and add them in reverse order to new_route
//      3. take route[k+1] to end and add them in order to new_route
//      return new_route;
//  }

// Here is an example of the above with arbitrary input:

// example route: A ==> B ==> C ==> D ==> E ==> F ==> G ==> H ==> A  
//    example i = 4, example k = 7  
//    new_route:  
//        1. (A ==> B ==> C)  
//        2. A ==> B ==> C ==> (G ==> F ==> E ==> D)  
//        3. A ==> B ==> C ==> G ==> F ==> E ==> D (==> H ==> A)

// recebe o vetor com o caminho antigo e dois indices pra delimitar o "miolo" a ser trocado
vector<int> two_opt_swap(vector<int> old_path, int i, int k)
{
	// inicializa vetor new_path tamanho 1500 e zera tudo 
	vector<int> new_path(1500, 0);

	// pega old_path[1] até old_path[i-1] e os adicione em ordem ao vetor new_path
	for (int j = 1; j <= j-1; ++i)
	{
		new_path.push_back(old_path[j]);
	}

	// pega old_path[i] até old_path[k] e os adicione em na ordem reversa ao vetor new_path
	for (int x = i; x < k; --x)
	{
		new_path.push_back(old_path[x]);
	}

	// pega old_path[k+1] até old_path[1500] e os adicione em ordem no vetor new_path
	for (int y = k+1; y < 1500; ++y)
	{
		new_path.push_back(old_path[x]);
	}

	// retorna vetor com caminho novo 
	return new_path;
	
}

// This is the complete 2-opt swap making use of the above mechanism:

//    repeat until no improvement is made {
//        start_again:
//        best_distance = calculateTotalDistance(existing_route)
//        for (i = 0; i < number of nodes eligible to be swapped - 1; i++) {
//            for (k = i + 1; k < number of nodes eligible to be swapped; k++) {
//                new_route = 2optSwap(existing_route, i, k)
//                new_distance = calculateTotalDistance(new_route)
//                if (new_distance < best_distance) {
//                    existing_route = new_route
//                    goto start_again
//                }
//            }
//        }
//    }

void two_opt(vector<int> old_path, int curr_cost)
{
	int best_cost = curr_cost;
	int new_cost = 0;
	vector<int> new_path(1500, 0);
	bool improved = true;

	while(improved)
	{
		calcutale_cost(old_path);
		improved = false;
		for (int i = 0; i < 1500; ++i)
		{
			for (int k = i + 1; k < 1500; ++k)
			{
				new_path = two_opt_swap(old_path, i, k);
				new_cost = calcutale_cost(new_path);

				if(new_cost < best_cost)
				{
					old_path = new_path;
					improved = true;
				}
			}
		}
	}

	// imprime o custo total
	cout<<"Custo minimio total: "<<best_cost<<"\n";

	cout<<"Caminho: ";
	// imprime o caminho
	for (int i = 0; i < path.size(); ++i)
	{
		cout<<new_path[i]<<", ";
	}
	// imprime o nó inicial novamente
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



























