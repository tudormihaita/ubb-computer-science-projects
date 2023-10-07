#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <string>

#define INF 999999

using namespace std;

struct edge {
	int src, dest, weight;
};

class Graph {
	string input_file, output_file;
	int V, E;
	vector<edge> edges;
	vector<pair<int, int>>* adj;

public:
	Graph(string input, string output);
	vector<int> BellmanFord(int V, vector<edge> edges, int src);
	vector<int> Dijkstra(int V, vector<pair<int, int>>* adj, int src);
	bool Johnson();
	~Graph();

};


Graph::Graph(string in, string out) {
	this->input_file = in;
	this->output_file = out;

	ifstream fin(this->input_file);

	int vertices, edges;
	fin >> vertices >> edges;
	this->V = vertices;
	this->E = edges;

	this->adj = new vector<pair<int, int>>[this->V+1];

	int u, v, w;
	while (fin >> u >> v >> w) {
		this->adj[u].push_back({ v, w });
		edge new_edge;
		new_edge.src = u;
		new_edge.dest = v;
		new_edge.weight = w;
		this->edges.push_back(new_edge);
	}

	fin.close();
}

Graph::~Graph() {
	delete[] this->adj;
}

vector<int> Graph::BellmanFord(int V, vector<edge> edges, int src) {
	//INITIALIZARE
	vector<int> dist(V, INF);
	dist[src] = 0;

	//RELAX
	for (int i = 0; i < V - 1; i++) {
		for (auto& j : edges) {
			if (dist[j.dest] > dist[j.src] + j.weight) {
				dist[j.dest] = dist[j.src] + j.weight;
			}
		}
	}

	//VERIFICARE CICLU NEGATIV INFINIT
	for (auto& j : edges) {
		if (dist[j.src] != INF && dist[j.dest] > dist[j.src] + j.weight) {
			return {};
		}
	}


	return dist;
}


vector<int> Graph::Dijkstra(int V, vector<pair<int, int>>* adj, int src) {
	//INITIALIZARE
	vector<int> dist(V, INF);
	dist[src] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> coada;
	coada.push({ 0, src });

	
	while (!coada.empty()) {
		int u = coada.top().second;
		coada.pop();

		for (auto& i : adj[u]) {
			int v = i.first;
			int w = i.second;

			//RELAX
			if (dist[u] != INF && dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				coada.push({ dist[v], v });
			}
		}
	}

	return dist;
}

bool Graph::Johnson() {
	vector<edge> new_edges = this->edges;

	//ADAUGARE MUCHII CU PONDERE 0 DE LA NOD SUPLIMENTAR
	for (int i = 0; i < this->V; i++) {
		edge new_edge;
		new_edge.src = V;
		new_edge.dest = i;
		new_edge.weight = 0;
		new_edges.push_back(new_edge);
	}

	//CALCUL DISTANTE MINIME NOI BELLMAN FORD CU NOD SUPLIMENTAR
	vector<int> new_weights = BellmanFord(this->V + 1, new_edges, this->V);

	//VERIFICARE CICLU NEGATIV INFINIT
	if (new_weights.size() == 0) {
		ofstream fout(this->output_file);
		fout << "-1\n";
		fout.close();
		return false;
	}

	ofstream fout(this->output_file);


	//for (int i = 0; i < this->V; i++) {
	//	for (auto& j : adj[i]) {
	//		//j.second = j.second + new_weights[i] - new_weights[j.first];
	//		cout << i << " " << j.first << " " << j.second << "\n";
	//	}
	//}

	//cout << "\n";

	//CALCUL SI AFISARE MUCHII REPONDERATE
	for (int i = 0; i < this->V; i++) {
		for (auto& j : adj[i]) {
			j.second = j.second + new_weights[i] - new_weights[j.first];
			fout << i << " " << j.first << " " << j.second << "\n";
		}
	}

	//for (int i = 0; i < this->V; i++) {
	//	for (auto& j : adj[i]) {
	//		//j.second = j.second + new_weights[i] - new_weights[j.first];
	//		cout << i << " " << j.first << " " << j.second << "\n";
	//	}
	//}


	//APLICARE DIJKSTRA PENTRU FIECARE NOD CU MUCHII REPONDERATE POZITIVE
	for (int i = 0; i < this->V; i++) {
		vector<int> dist = Dijkstra(V, adj, i);
		for (int j = 0; j < this->V; j++) {
			//AFISARE COSTURI MINIME CU PONDERI ORIGINALE MUCHII
			if (dist[j] == INF)
				fout << "INF" << " ";
			else {
				dist[j] = dist[j] - new_weights[i] + new_weights[j];
				fout << dist[j] << " ";
			}
		}
		fout << "\n";
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Numar invalid de argumente!\n";
		return -1;
	}

	Graph G(argv[1], argv[2]);
	G.Johnson();

	return 0;
}