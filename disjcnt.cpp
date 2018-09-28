// Copyright [2018] Gavan Adrian-George, 324CA + echipa PA (scheletul de laborator)
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <map>
using namespace std;

const int kNmax = 200000;

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
	// Map care are ca si key o pereche de 2 noduri (o muchie) si se retine
	// daca muchia este duplicat sau nu.
	map<pair<int, int>, int> frecvente;

	int timp = 0;
	int root;
  	long numar_perechi = 0;
  	long contor_nod = 0;

	struct Edge {
		int x;
		int y;
	};

  	/* Ideea algoritmului a fost descrisa in README */
	void read_input() {
		ifstream fin("disjcnt.in");
		fin >> n >> m;
		// Contor folosit pentru a stii ce valoare trebuie data noilor noduri.
		contor_nod = n + 1;

		int aux = 0;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;

			adj[x].push_back(y);
			adj[y].push_back(x);

			// Se verifica daca muchia este duplicat sau nu.
			// Daca muchia este duplicat, se vor creea alte 2 noduri care se vor
			// conecta la nodurile muchiei duplicat pentru a "simula" o alta muchie.
			auto it = frecvente.find(make_pair(x, y));
			if (it != frecvente.end()) {
				// Se leaga nod1 intermediar la nod1 muchie.
				adj[contor_nod].push_back(x);
				adj[x].push_back(contor_nod);

				aux = contor_nod;
				contor_nod++;

				// Se leaga nod2 intermediar la nod2 muchie.
				adj[contor_nod].push_back(y);
				adj[y].push_back(contor_nod);

				// Se leaga cele 2 noduri intermediare.
				adj[contor_nod].push_back(aux);
				adj[aux].push_back(contor_nod);

				contor_nod++;
			}

			// Daca muchia nu a mai fost adaugata, se adauga in map.
			if (it == frecvente.end()) {
				pair<int, int> aux2 = make_pair(x,y);
				pair<int, int> aux3 = make_pair(y,x);
				frecvente[aux2] = 1;
				frecvente[aux3] = 1;
			}

		}
		fin.close();
	}

    // Functie pentru algoritmul Tarjan (pentru muchii critice).
    void tarjanCritice(int v, vector<int> &idx,
                        vector<int> &low, vector<Edge> &sol) {
      idx[v] = low[v] = timp;
      timp++;

      for (auto u : adj[v]) {
        if (root != u) {
          if (idx[u] == -1) {
            int temp = root;
            root = v;
            tarjanCritice(u, idx, low, sol);
            root = temp;
            low[v] = min(low[v], low[u]);
            if (low[u] > idx[v]) {
              Edge aux;
              aux.x = v;
              aux.y = u;
              sol.push_back(aux);
            }
          } else {
            low[v] = min(low[v], idx[u]);
          }
        }
      }
    }

	void get_result() {
		vector<Edge> sol;
	    vector<int> idx(contor_nod, -1);
	    vector<int> low(contor_nod, -1);

	    // Se aplica Tarjan pentru a se afla muchiile critice.
	    for (int i = 1; i <= contor_nod - 1; i++){
	      if(idx[i] == -1) {
		root = 0;
		tarjanCritice(i, idx, low, sol);
	      }
	    }

	    // Dupa ce s-au aflat muchiile critice, acestea sunt eliminate din graf.
	    for (int i = 0; i < sol.size(); i++) {
	      adj[sol[i].x].erase(std::remove(adj[sol[i].x].begin(),
				  adj[sol[i].x].end(), sol[i].y), adj[sol[i].x].end());
	      adj[sol[i].y].erase(std::remove(adj[sol[i].y].begin(),
				  adj[sol[i].y].end(), sol[i].x), adj[sol[i].y].end());
	    }

	    // Se elimina muchiile din nodurile grafului catre nodurile suplimentare.
	    // Nu se sterg si muchiile din nodurile suplimentare catre nodurile
	    // grafului initial pentru ca in parcurgerea BFS (care urmeaza) se vor
	    // utiliza doar nodurile initiale, iar aceste muchii nu afecteaza.
	    for (int i = n + 1; i <= contor_nod - 1; i++) {
	      for (auto node : adj[i]) {
		adj[node].erase(std::remove(adj[node].begin(),
				adj[node].end(), i), adj[node].end());
	      }
	    }

	    // Se va aplica BFS in fiecare nod nevizitat pentru a determina componentele
	    // conexe rezultate in urma eliminarii muchiilor critice.
	    // Se va aplica BFS doar pentru nodurile din graful original, pentru ca
	    // nu ne intereseaza nodurile suplimentare.

	    // Alb - 0, Gri - -1, Negru - -2;
	    vector<int> c(n + 1, 0);

	    for (int i = 1; i <= n; i++) {
	      if (c[i] != 0) {
		continue;
	      }
      
	      vector<int> elemente;

	      c[i] = -1;
	      queue<int> q;
	      q.push(i);
	      while(!q.empty()) {
		int u = q.front();
		elemente.push_back(u);
		for (int j = 0; j < adj[u].size(); j++) {
		  if (c[adj[u][j]] == 0) {
		      c[adj[u][j]] = -1;
		      q.push(adj[u][j]);
		  }
		}
		c[u] = -2;
		q.pop();
	      }

	      // Toate nodurile dintr-o componenta conexa formeaza perechi
	      // corespunzatoare.
	      long nr_elem = elemente.size();
	      numar_perechi += nr_elem * (nr_elem - 1) / 2;
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
