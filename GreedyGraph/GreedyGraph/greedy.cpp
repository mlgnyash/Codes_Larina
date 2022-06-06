#include "Graph.h"
#include <fstream>

void print(vector<Vertex> vec) { //дубликат вывода содержания вектора вершин
	auto it = vec.begin();
	while (it != vec.end()) {
		cout << (*it).getnum() << " ";
		it++;
	}
	cout << endl;
}

int main() {
//открытие и чтение файла с заданным в консоли именем
	string file_name;
	cin >> file_name;
	file_name = "C:\\data\\gc_" + file_name;

// при помощи ифстрима открываем файл (если можем), после записываем данные оттуда в хар-ки графа
	ifstream data_file;
	data_file.open(file_name);
	if(!data_file) {
		cout << "Can not open file  " << file_name << endl;
		return 0;
	}

// создание графа с заданными в консоли N вершинами и М связями
	int N, M;
	data_file >> N >> M;
	Graph G(N);

	int V1, V2;
	for (int i = 0; i < M; i++) {
		data_file >> V1 >> V2;
		G.add_edge(V1, V2);
	}

	//cout << "Graph looks like that:" << endl;
	//G.print();
	//cout << endl << "Vector of vertices before sorting: ";
	//G.print_adj();
	//cout << "Vector of vertices after sorting: ";
	G.adj_sort(); // Сортировка от большего числа вершин к меньшему
	//G.print_adj();
	//cout << endl;

	int colored = 0, curcolor = 1; // Вводим число покрашенных вершин и "нынешний цвет"
	vector<Vertex> curadj; // Вводим вектор "сейчасных соседей" - будем по нему проверять смежность вершин с нынешним цветом
	while (colored != N) { // Сначала просто бежим слева направо, и ищем первую непокрашенную в curcolor вершину
		vector<Vertex>::iterator it = G.begin();
		bool new_vertex_found = 0;
		while (it != G.end() && new_vertex_found == 0) { // Находим эту непокрашенную - с неё начнётся покрашивание всех несмежных ей в цвет curcolor
			if ((*it).getcolor() == -1) {
				(*it).setcolor(curcolor);
				colored++;
				curadj.push_back((*it));
				new_vertex_found = 1;
				//cout << "Found an uncolored vertex " << (*it).getnum() << endl;
			}
			it++;
		}

		it = G.begin(); // Возвращаем итератор на начало, и снова бежим слева направо, крася все несмежные в curcolor
		while (it != G.end()) {
			if ((*it).getcolor() == -1) { // Если нашли непокрашенную
				//cout << "-subfound an uncolored vertex " << (*it).getnum() << endl;
				vector<Vertex>::iterator sub_it = curadj.begin(); // Ставим итератор на начало списка смежных вершин этого цвета
				int do_not_use = 0; // Если эта штука станет не равна нулю, не будем использовать эту вершину

				while (sub_it != curadj.end() && do_not_use==0) {
					//cout << "--checking it for being adjacent to " << (*sub_it).getnum() << "..." << endl;
					//cout << "--check result is " << G.are_connected((*it), (*sub_it)) << endl;
					do_not_use += G.are_connected((*it), *sub_it);
					sub_it++;
				}

				if (do_not_use == 0) { // Если же та штука осталась нулевой, значит, наша вершина никому не смежна
					//cout << "--this vertex is not adjacent to anything" << endl;
					(*it).setcolor(curcolor); // Красим её
					//cout << "---colored it in color " << curcolor << endl;
					colored++; // Увеличиваем количество покрашенных на 1
					//cout << "---there are now " << colored << " colored vertices" << endl;
					curadj.push_back((*it).getnum()); // Добавляем её в список смежности по этому цвету
					//cout << "---added it to the list of this color's adjacents: ";
					//print(curadj);
				}
			}
			it++; // Шагаем вперёд
		} // Этот цикл закончился => мы с цветом curcolor прошли до конца
		curcolor++; // Пойдём по следующему цвету
		curadj.clear(); // Очищаем вектор смежности - с новым цветом начнётся новая жизнь
		//cout << endl;
	}

	cout << endl << "The graph is colored in " << curcolor-1 << " colors" << endl;
	//G.print_colors();

	return 0;
}