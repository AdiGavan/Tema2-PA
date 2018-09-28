// Copyright [2018] Gavan Adrian-George, 324CA + echipa PA (scheletul de laborator)
#include <bits/stdc++.h>
using namespace std;

const int kNmax = 201000;

class Task {
 public:
	void solve() {
		read_input();
    		get_result();
		print_output();
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];
	map<pair<int, int>, int> frecvente;
	int x[kNmax], y[kNmax], idx[kNmax], low[kNmax], dim_cmp_conexa[kNmax];
	bool crit_edge[kNmax], visited[kNmax], visited2[kNmax];
	int nr_comp_conexe;
	long long numar_perechi = 0;

	void read_input() {
		ifstream fin("disjcnt.in");
		fin >> n >> m;

		for (int i = 1; i <= m; i++) {
			fin >> x[i] >> y[i];
			adj[x[i]].push_back(i);
			adj[y[i]].push_back(i);
			frecvente[make_pair(x[i], y[i])]++;
		}

		fin.close();
	}

	  // Functie muchii critice
	void tarjanCritice(int node, int father) {
		idx[node] = idx[father] + 1;
		low[node] = idx[node];
		visited[node] = true;

		for (int edge : adj[node]) {
			int v = x[edge] + y[edge] - node;
			if (v == father) continue;
			if (!visited[v]) {
				tarjanCritice(v, node);

				low[node] = min(low[node], low[v]);
				if (low[v] > idx[node] && (frecvente[make_pair(node, v)] +
						frecvente[make_pair(node, v)] <= 2)) {
					crit_edge[edge] = true;
				}
			} else {
				low[node] = min(low[node], idx[v]);
			}
		}
	  }

	  // Functie pentru componente conexe
	  void componente_conexe(int node) {
		visited2[node] = true;
		dim_cmp_conexa[nr_comp_conexe]++;

		for (int edge : adj[node]) {
			int v = x[edge] + y[edge] - node;
			if (!visited2[v] && !crit_edge[edge]) {
				componente_conexe(v);
			}
		}
	  }

	  void get_result() {
		tarjanCritice(1, 0);

		for (int i = 1; i <= n; i++) {
			if (!visited2[i]) {
				nr_comp_conexe++;
				componente_conexe(i);
			}
		}

		for (int i = 1; i <= nr_comp_conexe; i++) {
		   numar_perechi += (1LL * dim_cmp_conexa[i] * (dim_cmp_conexa[i] - 1)) / 2;
		}
	   }

	   void print_output() {
		ofstream fout("disjcnt.out");
		fout << numar_perechi << '\n';
		fout.close();
	   }
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
