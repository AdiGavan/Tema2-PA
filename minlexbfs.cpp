// Copyright [2018] Gavan Adrian-George, 324CA + echipa PA (scheletul de laborator)
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	int source = 1;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("minlexbfs.in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	vector<int> get_result() {
	    // Alb - 0, Gri - -1, Negru - -2;
	    vector<int> c(n + 1, 0);
	    vector<int> elemente;
	    // Se adauga un element pe pozitia 0 pentru a incepe indexarea de la 1.
	    elemente.push_back(-1);

	    /* Pentru a obtine parcurgerea minim lexicografica trebuie sa se
	       introduca vecinii nodurilor de la cel mai mic la cel mai mare in coada,
	       asa ca listele de adiacenta trebuie sortate. */
	    for (int i = 1; i <= n; i++) {
	      std::sort(adj[i].begin(), adj[i].end());
	    }

	    // BFS
	    c[1] = -1;
	    queue<int> q;
	    q.push(1);
	    while(!q.empty()) {
	      int u = q.front();
	      elemente.push_back(u);
	      for (int j = 0; j < adj[u].size(); j++) {
		// adj[u][j] este vecinul lui u.
		if (c[adj[u][j]] == 0) {
		    c[adj[u][j]] = -1;
		    q.push(adj[u][j]);
		}
	      }
	      c[u] = -2;
	      q.pop();
	    }

    	    return elemente;
	}

	void print_output(vector<int> result) {
		ofstream fout("minlexbfs.out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << ' ';
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
