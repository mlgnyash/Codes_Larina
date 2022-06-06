#include "Vertex.h"

Vertex::Vertex(int i) { // создание вершины с заданным значением и несуществующим цветом
	num = i;
	color = -1;
}

int Vertex::getnum() { //возврат значения
	return num;
}

void Vertex::setnum(int n) { //смена значения
	num = n;
}

int Vertex::getcolor() { //возврат цвета
	return color;
}
void Vertex::setcolor(int c) { //смена цвета
	color = c;
}

vector<int>::iterator Vertex::begin() { //функция, которая возвращает начало массива связанных с данной вершиной других вершин
	return adj_Vertices.begin();
}
vector<int>::iterator Vertex::end() { //то же самое что исверху, но возвращает конец
	return adj_Vertices.end();
}

void Vertex::add_adj(int i) { //добавляет в список связанных вершин новую
	adj_Vertices.push_back(i);
}

int Vertex::adj_count() const { //возвращает кол-во связанных с данной вершиной других вершин
	return (adj_Vertices.size());
}

bool Vertex::operator<(const Vertex & V2) { //оператор сравнения двух вершин по количеству связанных с ними других вершин
	return (this->adj_count() > V2.adj_count());
}