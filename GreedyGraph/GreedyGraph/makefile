# цель сборки (исполняемый файл, который будет вызываться через ./<имя файла>,
# в данном случае - ./greedy_alg
all: greedy_alg

# Для greedy_alg нужны классы Графа и Вертекса, при помощи команды ниже скомпилированные
# Граф и Вертекс связываются с greedy, и на выходе получается greedy_alg
greedy_alg: greedy.o Graph.o Vertex.o
g++ greedy.o Graph.o Vertex.o -o greedy_alg

# Для того, чтобы связать greedу с остальными (команда выше), его нужно скомпилировать. 
# Компилируем.
greedy.o: greedy.cpp
g++ -c greedy.cpp -o greedy.o

# Для связки файлов между собой больше всего подходят исполняемые (.о \ .obj) файлы, для 
# этого компилируем Граф и Вертекс.
Graph.o: Graph.h Graph.cpp
g++ -c Graph.cpp -o Graph.o

Vertex.o: Vertex.h Vertex.cpp
g++ -c Vertex.cpp -o Vertex.o
