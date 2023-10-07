#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <list>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

struct Tree {
	int* deg;
	int* parent;
	set<int> leafs;

	int N;
};

struct Edge {
	int src;
	int dest;
	int weight;
};

struct MinHeapNode {
	char chr;

	int freq;

	MinHeapNode* left, * right;

	MinHeapNode(char chr, int freq) {
		left = right = NULL;
		this->chr = chr;
		this->freq = freq;
	}
};


struct compare {
	bool operator()(MinHeapNode* l, MinHeapNode* r) {
		return l->freq > r->freq;
	}
};

class DSU {
private:

	int* parent;
	int* rank;
public:
	DSU(int N) {
		this->parent = new int[N];
		this->rank = new int[N];

		for (int i = 0; i < N; i++) {
			this->parent[i] = -1;
			this->rank[i] = 1;
		}
	}

	int findSet(int i) {
		if (parent[i] == -1)
			return i;

		return parent[i] = findSet(parent[i]);
	}

	void unionSet(int x, int y) {
		int s1 = findSet(x);
		int s2 = findSet(y);

		if (s1 != s2) {
			if (rank[s1] < rank[s2]) {
				parent[s1] = s2;
			}
			else if (rank[s1] > rank[s2]) {
				parent[s2] = s1;
			}
			else {
				parent[s2] = s1;
				rank[s1] += 1;
			}
		}
	}
};