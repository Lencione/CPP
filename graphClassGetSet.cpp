#include <iostream>
using namespace std;

class ADJACENCY {
private:
    int vertex;
    int weight;
    ADJACENCY *next;

public:
    int getVertex() { return vertex; }
    void setVertex(int vertex) { this->vertex = vertex; }
    void setWeight(int weight) { this->weight = weight; }
    int getWeight() { return weight; }
    void setNext(ADJACENCY *next) { this->next = next; }
    ADJACENCY *getNext() { return next; }
};

class VERTEX {
private:
    int key;
    ADJACENCY *head;

public:
    int getKey() { return this->key; }
    void setKey(int key) { this->key = key; }
    void setHead(ADJACENCY *head) { this->head = head; }
    ADJACENCY *getHead() { return head; }
};

class GRAPH {
private:
    int vertices;
    int edges;
    VERTEX *adjacency_list;

public:
    GRAPH(){
        cout << "Need to inform the number of vertices" << endl;
        cout << "Program will be terminated" << endl << endl;
        exit(-1);
    }

    GRAPH(int v) {
        if (v <= 0) {
            cout << "Need to inform the number of vertices" << endl;
            cout << "Program will be terminated" << endl << endl;
            exit(-1);
        }
        vertices = v;
        edges = 0;
        adjacency_list = new VERTEX[v];
        for (int i = 0; i < v; i++) {
            adjacency_list[i].setHead(NULL);
        }
    }

    int getVertices() { return vertices; }
    void setVertices(int vertices) { this->vertices = vertices; }
    int getEdges() { return edges; }
    void setEdges(int edges) { this->edges = edges; }
    VERTEX *getAdjacencyList() { return adjacency_list; }
    void setAdjacencyList(VERTEX *adjacency_list) { this->adjacency_list = adjacency_list; }

    ADJACENCY *createAdjacency(int v, int weight) {
        ADJACENCY *temp = new ADJACENCY;
        temp->setVertex(v);
        temp->setWeight(weight);
        temp->setNext(NULL);
        return temp;
    }

    void findKey(int keyToFind)
    {
        bool found = false;
        for (int vertexIndex = 0; vertexIndex < vertices; vertexIndex++)
        {
            VERTEX *currentVertex = adjacency_list;
            if (currentVertex[vertexIndex].getKey() == keyToFind)
            {
                cout << "The key " << keyToFind << " is in vertex v" << vertexIndex;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "Key " << keyToFind << " not found";
    }

    bool addEdge(int start_vertex, int end_vertex, int weight, int key) {
        if (end_vertex < 0 || end_vertex >= vertices || start_vertex < 0 || start_vertex >= vertices)
            return false;
        ADJACENCY *new_edge = createAdjacency(end_vertex, weight);
        new_edge->setNext(adjacency_list[start_vertex].getHead());
        adjacency_list[start_vertex].setHead(new_edge);
        adjacency_list[start_vertex].setKey(key);
        edges++;
        return true;
    }

    void print() {
        cout << "Vertices: " << vertices << ", Edges: " << edges << endl;
        for (int i = 0; i < vertices; i++) {
            cout << "key(" << adjacency_list[i].getKey() << "), ";
            cout << "v" << i << ": ";
            ADJACENCY *adj = adjacency_list[i].getHead();
            while (adj) {
                cout << "v" << adj->getVertex() << "(" << adj->getWeight() << ") ";
                adj = adj->getNext();
            }
            cout << endl;
        }
    }
};
