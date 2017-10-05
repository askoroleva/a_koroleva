#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

class Graph
{
public:
	vector <int> H, L, IJ, draw;
	int n; 
	int m; 
	Graph(int _n, vector<int> _I, vector<int> _J): n(_n), m(_I.size()*2) {
		IJ.resize(m);
		for (int k(0); k < m/2; k++) {
			IJ[k] = _I[k];
			int index = m - k - 1;
			IJ[index] = _J[k];
		}
		make_H_L();
	}

	void make_H_L() { 
		H.assign(n, -1);
		L.resize(m);
		for (int k(0); k < m; k++) {
			int i = IJ[k];
			L[k] = H[i];
			H[i] = k;
		}
	}

	void Add(int i, int j){ 
		IJ.insert(IJ.begin() + m / 2, i);
		IJ.insert(IJ.begin() + m / 2 + 1, j);
		m = m + 2;
		make_H_L();
	}

	void print() {
		cout << "graph tree {" << endl;
		for (int i(0); i < m/2; i++) {
			cout << IJ[i]+1 << " -- " << IJ[m-i-1]+1 << ";";
			cout << endl;
		}
		cout << "}";
	}

	void DFS(int v, int color) {
		draw[v] = color;
		for (int i(H[v]); i != -1; i = L[i]) {
			if (draw[IJ[m - i - 1]] == -1) {
				DFS(draw[IJ[m - i - 1]], color);
			}
		}
	}

	void find() {
		int color(1);
		for (int i(0); i < n; i++) {
			if (draw[i] == -1) {
				DFS(i, color);
				color++;
			}
		}
	}
};

int main()
{
	freopen("tree.gv", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector <int> I, J;
	int a, b;
	for (int i(0); i < m; i++) {
		cin >> a >> b;
		I.push_back(a-1);
		J.push_back(b-1);
	}
	Graph Gr(n, I, J);
	Gr.print();
	Gr.find();
	system("pause");
	return 0;
}

