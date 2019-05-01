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

// calcula custo dado a matriz de adjacencia e um caminho
int calculate_cost(int **adj_matrix, vector<int> route) 
{
    int cost = 0;

    for(int i = 0; i < route.size() - 1; i++) 
    {
    	// acumula custo da adj_matrix com os indices da rota [i][i+1]
        cost += adj_matrix[route[i]][route[i + 1]];
    }

    // retorna o custo
    return cost;
}

// inverte o miolo entre "inicio e final" no 2-opt
vector<int> invert(vector<int> to_invert, int inicio, int final)
{
	// EXEMPLO:
	//
	// to_invert = 	|0|3|2|4|1|5|
	// temp =		|0|3|2|4|1|5|
	// indices (inicio = 1; final = 4)
	//
	// i = 1; j = 4
	// to_invert = 	|0|1|2|4|1|5|
	// temp =		|0|3|2|4|1|5|

	// i = 2; j = 3
	// to_invert = 	|0|1|4|4|1|5|
	// temp =		|0|3|2|4|1|5|
	
	// i = 3; j = 2
	// to_invert = 	|0|1|4|2|1|5|
	// temp =		|0|3|2|4|1|5|

	// i = 4; j = 1.   .     .
	// to_invert = 	|0|1|4|2|3|5| (miolo invertido)
	// temp =		|0|3|2|4|1|5|

	vector<int> temp;
	temp = to_invert;

	for(int i = inicio, j = final; i <= final; i++, j--){
		to_invert[i] = temp[j];
	}

	return to_invert;
}

// heuristica de construcao do vizinho mais proximo 
vector<int> nearest_neighbour(int **adj_matrix)
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
	vector<int> route;
	route.push_back(curr_node);

	// enquanto o tamanho do vetor route for menor que 1500
	while(route.size() < 1500)
	{
		// min = maior valor possivel 
		int min = __INT_MAX__;
		for(int i = 0; i < 1500; ++i)
		{
			// se nó i nao tiver sido visitado, e o nó atual for menor que o minimo
			if((!visited_node[i]) && (adj_matrix[curr_node][i] < min))
			{
				// minimo recebe o no atual
				min = adj_matrix[curr_node][i];
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
		route.push_back(past_visited);
	}

	cout<<"Heuristica do vizinho mais proximo:\n";
	// imprime o custo total
	cout<<"Custo minimio total: "<<cost<<"\n";

	cout<<"Caminho: ";
	// imprime o caminho
	for (int i = 0; i < route.size(); ++i)
	{
		cout<<route[i]<<", ";
	}
	// imprime o nó inicial novamente
	cout<<"0\n\n";

	return route;
}

// movimento de vizinhanca swap
vector<int> swap(int **adj_matrix, vector<int> route)
{
	// vetor temp faz copia da rota original
	vector<int> temp;
	temp = route;
	
	// custo inicial é o custo da rota original
	int init_cost = calculate_cost(adj_matrix, route);
	// custo temporario
	int temp_cost;

	for(int i = 1; i < 1500; i++){

		// reseta rota temporaria
		temp = route;

		for(int j = i + 1; j < 1500; j++){
			int aux = temp[i];  // guarda valor de temp[i] em aux
			temp[i] = temp[j];  // temp[i] recebe temp[j]
			temp[j] = aux;		// temp[j] recebe aux que guarda temp[i]

			// calcula custo pra rota temporaria com swap feito
			temp_cost = calculate_cost(adj_matrix, temp);

			// se custo da rota temporaria for menor que da original
			if(temp_cost < init_cost){
				// custo da rota original recebe custo temporario
				init_cost = temp_cost;
				// rota original recebe rota temporaria
				route = temp;
			}
		}
	}

	cout<<"Movimento de vizinhanca swap:\n";
	// imprime o custo total
	cout<<"Custo minimio total: "<<init_cost<<"\n";

	cout<<"Caminho: ";
	// imprime o caminho
	for (int i = 0; i < 1500; ++i)
	{
		cout<<route[i]<<", ";
	}
	// imprime o nó inicial novamente
	cout<<"0\n\n";

	return route;	
}

// movimento de vizinhanca 2-opt
vector <int> two_opt(int **adj_matrix, vector <int> route)
{
	vector <int> temp = route;
	vector <int> init = route;
	int temp_cost;
	int init_cost = calculate_cost(adj_matrix, route);

	for(int i = 1; i < 1500; i++)
	{
		for(int j = i + 1; j < 1500; j++)
		{
			// inverte o miolo delimitado por i = 1 ; j = 2,3,4,...,1499
			// inverte o miolo delimitado por i = 2 ; j = 3,2,5,...,1499
			// inverte o miolo delimitado por i = 3 ; j = 4,5,6,...,1499
			// ...
			temp = invert(temp, i, j);

			// calcula custo da rota temporaria 
			temp_cost = calculate_cost(adj_matrix, temp);
			// se custo da rota temporaria for menor que custo da rota inicial
			// custo inicial recebe custo temporario e rota inicial recebe rota temporaria
			if(temp_cost < init_cost){
				init_cost = temp_cost;
				route = temp;
			}
			// reseta rota temporaria
			temp = init;
		}
	}
	cout<<"Movimento de vizinhanca 2-opt:\n";
	// imprime o custo total
	cout<<"Custo minimio total: "<<init_cost<<"\n";

	cout<<"Caminho: ";
	// imprime o caminho
	for (int i = 0; i < route.size(); ++i)
	{
		cout<<route[i]<<", ";
	}
	// imprime o nó inicial novamente
	cout<<"0\n\n";

	return route;
}



int main(int argc, char *argv[])
{
	// array pra posicoes x e y
	double pos_x[1500];
	double pos_y[1500];
	// contador
	int count = 0;
	
	// alocacao dinamica matriz[1500][1500]
	int **adj_matrix = new int*[1500];
	for(int i = 0; i < 1500; i++)
		adj_matrix[i] = new int[1500];
	for(int i = 0; i < 1500; i++)
		for(int j = 0; j < 1500; j++)
			adj_matrix[i][j] = 0;

	// abre o arquivo com os pontos x e y
	ifstream in("tsp3.txt");
	
	// pega os 1500 valores
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
			// adj_matrix[i][j] é populada com a distancia euclidiana
			adj_matrix[i][j] = euclidian_distance(pos_x[i], pos_y[i], pos_x[j], pos_y[j]);
		}
	}

	// chama heuristica de construcao do vizinho mais proximo passando a matriz de adjacencia
	vector<int> route = nearest_neighbour(adj_matrix);

	// movimento de vizinhanca swap
	swap(adj_matrix, route);

	// movimento de vizinhanca 2-opt
	two_opt(adj_matrix, route);

	// deleta a matriz alocada
	delete[] adj_matrix;
	return 0;
}



























