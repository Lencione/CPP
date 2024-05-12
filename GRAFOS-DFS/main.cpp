#include "graphClassGetSet.cpp"
#include <iostream>
using namespace std;


int main() {
    GRAPH *graph = new GRAPH(5);
    graph->addEdge(0, 1, 2, -1);
    graph->addEdge(1, 2, 4, 2);
    graph->addEdge(2, 0, 12, 4);
    graph->addEdge(2, 4, 40, 4);
    graph->addEdge(3, 1, 3, 5);
    graph->addEdge(4, 3, 8, 6);
    graph->print();
    graph->findKey(5);

    return 0;
}
