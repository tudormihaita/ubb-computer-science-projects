#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


using namespace std;
#define INF 999999
#define NIL NULL
#define LMAX 101

ifstream fin("graf.txt");
ifstream in("labirint1.txt");
ofstream out("labirint1sol.txt");


void moore() {
	//revenirea la inceputul fisierului pentru a evita crash-urile la redeschiderea path-ului in rularea urmatoarei comenzi
	fin.clear();
	fin.seekg(0);

	int n;
	fin >> n;

	vector<int> vecini[LMAX];

	int* dist = new int[n + 1];
	int* parinte = new int[n + 1];


	int x, y;
	while (fin >> x >> y) {
		vecini[x].push_back(y);
	}

	int nod_sursa;
	cout << "Introduceti nodul sursa: "; cin >> nod_sursa;

	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
		parinte[i] = NIL;
	}

	dist[nod_sursa] = 0;
	parinte[nod_sursa] = -1;

	queue<int> coada;
	coada.push(nod_sursa);

	while (!coada.empty()) {
		int nod_curent = coada.front();
		coada.pop();
		for (auto i : vecini[nod_curent]) {
			if (dist[i] == INF) {
				dist[i] = dist[nod_curent] + 1;
				parinte[i] = nod_curent;
				coada.push(i);
			}
		}
	}

	int nod_destinatie;
	cout << "Introduceti nodul destinatie: "; cin >> nod_destinatie;
	if (dist[nod_destinatie] == INF) {
		cout << "Nu exista drum pana la nodul dat!\n";
	}
	else {
		int* drum = new int[dist[nod_destinatie]+1];
		int poz = dist[nod_destinatie];
		drum[poz] = nod_destinatie;
		while (poz) {
			drum[poz - 1] = parinte[drum[poz]];
			--poz;
		}
		cout << "Drumul de lungime minima de la nodul sursa " << nod_sursa << " la nodul destinatie " << nod_destinatie << " este:\n";
		for (int i = 0; i <= dist[nod_destinatie]; i++) {
			cout << drum[i] << " ";
		}
		cout << "\n";
	}

	delete[] dist;
	delete[] parinte;
}



void inchidere_tranzitiva() {
	fin.clear();
	fin.seekg(0);

	int n;
	fin >> n;
	
	int** inchidere = new int* [n + 1];
	for (int i = 1; i <= n; i++)
		inchidere[i] = new int[n + 1];

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			inchidere[i][j] = 0;


	int x, y;
	while (fin >> x >> y) {
		inchidere[x][y] = 1;
	}

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (inchidere[i][j] == 0)
					inchidere[i][j] = (inchidere[i][k] == 1 && inchidere[k][j] == 1);

	cout << "Matricea inchiderii tranzitive pentru graful de sus este:\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cout << inchidere[i][j] << " ";
		delete[]  inchidere[i];
		cout << "\n";
	}

	delete[] inchidere;

}


int inmat(int i, int j, int n, int m) {
	return(i >= 0 && i < n && j >= 0 && j < m);
}


void reconstituire_traseu_labirint(int** mat, int i, int j, int n, int m, int dx[], int dy[]) {
	if (mat[i][j] == 1) {
		mat[i][j] = 'x';
	}
	else {
		int p = -1;
		for (int k = 0; k < 4 && p == -1; k++) {
			int inou = i + dx[k];
			int jnou = j + dy[k];
			if (inmat(inou, jnou, n, m) && mat[i][j] == mat[inou][jnou] + 1 && mat[inou][jnou] != -1)
				p = k;
		}
		reconstituire_traseu_labirint(mat, i + dx[p], j + dy[p], n, m, dx, dy);
		mat[i][j] = 'x';
	}
}

void labirint1() {
	in.clear();
	in.seekg(0);

	int dy[] = { 0, 1, 0, -1 };
	int dx[] = { -1, 0, 1, 0 };

	char* string = new char[LMAX];
	int** mat = new int* [LMAX];

	pair<int, int> nod_start;
	pair<int, int> nod_final;

	int n = 0, m = 0;
	while (in.getline(string, LMAX)) {
		n++;
		m = strlen(string);
		mat[n-1] = new int[LMAX];
		for (int i = 0; i < strlen(string); i++) {
			if (string[i] == '1') {
				mat[n - 1][i] = -1;
			}
			else if (string[i] == ' ') {
				mat[n - 1][i] = 0;
			}
			else if (string[i] == 'S') {
				mat[n - 1][i] = 1;
				nod_start = { n - 1, i };
			}
			else if (string[i] == 'F') {
				mat[n - 1][i] = 0;
				nod_final = { n - 1, i };
			}
		}


	}

	queue<pair<int, int>> coada;
	coada.push(nod_start);

	mat[nod_start.first][nod_start.second] = 1;
	while (!coada.empty()) {
		int i = coada.front().first;
		int j = coada.front().second;

		for (int k = 0; k < 4; k++) {
			int iv = i + dx[k];
			int jv = j + dy[k];
			if (inmat(iv, jv, n, m) && mat[iv][jv] == 0) {
				mat[iv][jv] = mat[i][j] + 1;
				coada.push(make_pair(iv, jv));
			}
		}
		coada.pop();
	}

	reconstituire_traseu_labirint(mat, nod_final.first, nod_final.second, n, m, dx, dy);

	int dist = 0;
	cout << "Solutia labirintului dat a fost generata!\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (mat[i][j] == 'x') {
				dist++;
				out << 'x';
			}
			else if (mat[i][j] != -1)
				out << ' ';
			else if (mat[i][j] == -1)
				out << '1';
		out << "\n";
	}
	
	cout << "Distanta: " << dist << "\n";
}





void bfs() {
	fin.clear();
	fin.seekg(0);

	int n;
	fin >> n;

	vector<int> vecini[LMAX];
	vector<bool> viz(n + 1, false);
	vector<int> dist(n + 1, INF);
	
	int x, y;
	while (fin >> x >> y) {
		vecini[x].push_back(y);
	}

	int nod_sursa;
	cout << "Introduceti nodul sursa: "; cin >> nod_sursa;

	queue<int> coada;
	viz[nod_sursa] = true;
	dist[nod_sursa] = 0;

	coada.push(nod_sursa);

	cout << "Nodurile descoperite de algoritmul BFS plecand de la nodul sursa  " << nod_sursa << " si distanta pana la fiecare nod:\n";
	while (!coada.empty()) {
		int nod_curent = coada.front();
		cout << nod_curent << " - " << dist[nod_curent] << "; ";
		coada.pop();
		for (auto i : vecini[nod_curent]) {
			if (!viz[i]) {
				viz[i] = true;
				dist[i] = dist[nod_curent] + 1;
				coada.push(i);
			}
		}
	}
	cout << "\n";

}


void dfs_visit(vector<bool>& viz, vector<int> vecini[], int nod) {
	viz[nod] = true;
	for (auto i : vecini[nod]) {
		if (!viz[i]) {
			cout << i << " ";
			viz[i] = true;
			dfs_visit(viz, vecini, i);
		}
	}
}



void dfs() {
	fin.clear();
	fin.seekg(0);

	int n;
	fin >> n;

	vector<int> vecini[LMAX];
	vector<bool> viz(n + 1, false);

	int x, y;
	while (fin >> x >> y) {
		vecini[x].push_back(y);
	}

	int nod_sursa;
	cout << "Introduceti nodul sursa: "; cin >> nod_sursa;

	cout << "Varfurile descoperite de algoritmul DFS plecand de la nodul sursa " << nod_sursa << ":\n";
	cout << nod_sursa << " ";

	dfs_visit(viz, vecini, nod_sursa);

	cout << "\n";
}


int main(int argc, char** argv) {
	cout << "1 - Alogritmul lui Moore\n";
	cout << "2 - Inchiderea tranzitiva\n";
	cout << "3 - Solutie labirint1 prin Algoritmul lui Lee\n";
	cout << "4 - Algoritmul BFS\n";
	cout << "5 - Algoritmul DFS\n";

	int cmd = 0;
	while (1) {
		cin >> cmd;
		if (cmd == 1) {
			moore();
		}
		else if (cmd == 2) {
			inchidere_tranzitiva();
		}
		else if (cmd == 3) {
			labirint1();
		}
		else if (cmd == 4) {
			bfs();
		}
		else if (cmd == 5) {
			dfs();
		}
		else if (cmd == 0) {
			cout << "Goodbye!\n";
			return 0;
		}
		else {
			cout << "Comanda invalida!\n";
		}
	}
	return 0;
}