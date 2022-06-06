#include "Graph.h"

Graph::Graph(int N) { // конструктор (функция создания) графа с заданным кол-вом вершин
	for (int i = 0; i < N; i++) {
		Vertices.push_back(Vertex(i));
	}
	Sorted_Vertices = Vertices;
}

bool Graph::are_connected(Vertex V1, Vertex V2) { 
//функция проверки связности двух данных вершин графа. Для 
// этого мы создаем итератор (по факту аналог цикла) и 
// проходимся по всем исходящим связям первой вершины.
// Если нашли - выдаем 1 (true), не нашли - выдаем 0 (false).
	vector<int>::iterator it = V1.begin();
	while (it != V1.end()) {
		if ((*it) == V2.getnum()) {
			return 1;
		}
		it++;
	}
	return 0;
}

void Graph::add_edge(int V1, int V2) {
// функция добавления связи между двумя разными вершинами.
// для этого в массив связей каждой вершины добавляем другую вершину.
	if (V1 != V2) {
		Vertices[V1].add_adj(V2);
		Vertices[V2].add_adj(V1);
	}
}

void Graph::print() {
	vector<Vertex>::iterator it = Vertices.begin();
	while (it != Vertices.end()) {
		cout << "Adjacent vertices to vertex " << (*it).getnum() << " are: ";
		vector<int>::iterator sub_it = (*it).begin();
		while (sub_it != (*it).end()) {
			cout << (*sub_it) << " ";
			sub_it++;
		}
		cout << endl;
		it++;
	}
}

vector<Vertex> Graph::get_vertices() { // функция возвращения вершин графа
	return Vertices;
}

Vertex Graph::vertex(int i) { //функция возвращения вершины с заданным индексом
	return Vertices[i];
}

vector<Vertex>::iterator Graph::begin() { //функция для возвращения начала массива вершин
	return Vertices.begin();
}

vector<Vertex>::iterator Graph::end() { // функция для возвращения конца массива вершин
	return Vertices.end();
}

vector<Vertex>::iterator Graph::sorted_begin() { // функция для возвращения начала массива отсортированных (по значению) вершин
	return Sorted_Vertices.begin();
}

vector<Vertex>::iterator Graph::sorted_end() { // возвращает конец отсортированного массива
	return Sorted_Vertices.end();
}

void Graph::adj_sort() { //функция сортировки массива вершин
	sort(Vertices.begin(), Vertices.end());
}

void Graph::print_adj() { //функция для выдачи в консоль значений каждой вершины
	vector<Vertex>::iterator it = Vertices.begin();
	while (it != Vertices.end()) {
		cout << (*it).getnum() << " ";
		it++;
	}
	cout << endl;
}

void Graph::print_colors() { // функция для выдачи в консоль раскраски (цвета) каждой вершины
	vector<Vertex>::iterator it = Vertices.begin();
	while (it != Vertices.end()) {
		cout << (*it).getnum() << " is colored in color " << (*it).getcolor() << endl;
		it++;
	}
}