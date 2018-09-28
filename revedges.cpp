// Copyright [2018] Gavan Adrian-George, 324CA + echipa PA (scheletul de laborator)
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;

const int kNmax = 510;

typedef std::pair<int, int> Pereche;

class Task {
 public:
	void solve() {
		read_input();
		compute();
		print_output();
	}

 private:
	int n, m, q;
  // Matricea distantelor minime.
	int d[kNmax][kNmax];
  // Vectorul perechilor pentru interogari.
  vector<Pereche> interogari;
  // Vectorul in care se retine numarul de arce ce trebuie schimbate pentru
  // fiecare interogare.
  vector<int> numar_muchii;
  // Matricea ponderilor.
	vector<int> a[kNmax];

	void read_input() {
		ifstream fin("revedges.in");
    int x, y;
    fin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
      a[i] = vector<int>(n + 1, -1);
    }

    /* Ideea algoritmului a fost descrisa in README. */
    for (int i = 1; i <= m; i++) {
      fin >> x >> y;
      // Arcele grafului dat vor avea costul 0 si noi construim si arcele
      // orientate invers, doar ca le atribuim valoarea 1.
      // Chiar daca dupa aceea primim arcul cu orientare inversa in input nu
      // este o problema pentru ca se va suprascrie valoarea 1 din matrice cu 0
      // si din cauza if-ului nu se va suprascrie o valoare de 0 deja existenta.
      a[x][y] = 0;
      if (a[y][x] == -1) {
        a[y][x] = 1;
      }
    }

    for (int i = 1; i <= q; i++) {
      fin >> x >> y;
      interogari.push_back({x,y});
    }

		fin.close();
	}

	void compute() {
    // Roy-Floyd
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j++) {
				if (a[i][j] == -1) {
          // Daca nu este arc se initializeaza cu valoare foarte mare.
					d[i][j] = 1000000;
				} else {
					d[i][j] = a[i][j];
				}
			}
		}

		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i ++) {
				for (int j = 1; j <= n; j++) {
					if (i != j) {
						d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
					}
				}
			}
		}

    // Dupa ce s-a completat matricea cu costurile minime ale drumurilor intre
    // fiecare nod, doar se extrage valoarea corespunzatoare din "d" pentru
    // fiecare interogare.
    for (int i = 0; i < q; i++) {
      numar_muchii.push_back(d[interogari[i].first][interogari[i].second]);
    }
	}

	void print_output() {
		ofstream fout("revedges.out");
		for (int i = 0; i < q; i++) {
      if (numar_muchii[i] == 1000000) {
        numar_muchii[i] = 0;
      }
			fout << numar_muchii[i];
			fout << '\n';
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
