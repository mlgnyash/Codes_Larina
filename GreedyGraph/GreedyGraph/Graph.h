#pragma once
#include "Vertex.h" //импорт класса Вертекс

class Graph
{
private: //приватные поля класса - массив вершин графа и массив отсортированных вершин графа
	vector<Vertex> Vertices;
	vector<Vertex> Sorted_Vertices;
public:
// декларация публичных функций 
	Graph(int); //конструктор
	bool are_connected(Vertex V1, Vertex V2); //проверка связности 2 вершин графа
	void add_edge(int V1, int V2); //добавление связи между вершинами
	void print(); //выдача вершин графа
	vector<Vertex> get_vertices(); //остальные функции описаны в Graph.cpp
	Vertex vertex(int);
	vector<Vertex>::iterator begin();
	vector<Vertex>::iterator end();
	vector<Vertex>::iterator sorted_begin();
	vector<Vertex>::iterator sorted_end();
	void adj_sort();
	void print_adj();
	void print_colors();
};

