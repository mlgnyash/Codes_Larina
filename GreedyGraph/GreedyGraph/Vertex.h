#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Vertex
{
private: //приватные поля класса - массив связанных с данной вершиной вершин, значение вершины, цвет вершины
	vector <int> adj_Vertices;
	int num;
	int color;
public:
//все функции расписаны в Vertex.cpp
	Vertex(int);
	int getnum();
	void setnum(int);
	int getcolor();
	void setcolor(int);
	vector<int>::iterator begin();
	vector<int>::iterator end();
	void add_adj(int);
	int adj_count() const;
	bool operator < (const Vertex&);
};

