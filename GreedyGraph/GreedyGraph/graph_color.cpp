#include "Graph.h"

int main() {
// мейн для проверки связности заданных вершин в графе
	Graph G(4);
	G.add_edge(0, 1);
	G.add_edge(1, 2);
	G.add_edge(2, 3);
	G.add_edge(3, 1);
	cout << G.are_connected(0, 1) << " " << G.are_connected(0, 2) << endl;

	G.add_edge(0, 2);
	G.add_edge(0, 3);
	cout << G.are_connected(0, 2) << " " << G.are_connected(0, 3);
	return 0;
}