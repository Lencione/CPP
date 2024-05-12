#include <iostream>
using namespace std;

struct ADJACENCY {
    int vertex;
    ADJACENCY* next;
};

struct VERTEX {
    ADJACENCY* head;
};

struct GRAPH {
    int vertices;
    VERTEX* adjacency_list;
};

GRAPH* createGraph(int v) {
    GRAPH* g = new GRAPH;
    g->vertices = v;
    g->adjacency_list = new VERTEX[v];
    for (int i = 0; i < v; i++)
        g->adjacency_list[i].head = nullptr;
    return g;
}

ADJACENCY* createAdjacency(int v) {
    ADJACENCY* temp = new ADJACENCY;
    temp->vertex = v;
    temp->next = nullptr;
    return temp;
}

bool addEdge(GRAPH* gr, int vi, int vf) {
    if (!gr)
        return false;
    if ((vf < 0) || (vf >= gr->vertices))
        return false;
    if ((vi < 0) || (vi >= gr->vertices))
        return false;
    ADJACENCY* newEdge = createAdjacency(vf);
    newEdge->next = gr->adjacency_list[vi].head;
    gr->adjacency_list[vi].head = newEdge;
    return true;
}

bool bfsSearch(GRAPH* gr, int key) {
    if (!gr)
        return false;

    // Cria um array pra armazenar se cada vertice foi visitado e em seguida
    // Inicializa setando todos como false (nao visitado)
    bool* visited = new bool[gr->vertices];
    for (int i = 0; i < gr->vertices; i++)
        visited[i] = false;

    // Agora cria-se um array pra simular uma fila e o indice pra controlar
    int* queue = new int[gr->vertices];
    int front = 0;
    int rear = -1;

    // Loop pra percorrer todos os vertices
    for (int i = 0; i < gr->vertices; i++) {
        // Primeiro verifico se o vertice ja foi visitado
        // Caso nao, coloco o vertice na fila e seto ele como visitado
        if (!visited[i]) {
            queue[++rear] = i;
            visited[i] = true;

            // Enquanto a fila nao estiver vazia, continue a busca
            while (front <= rear) {
                // Remove o vertice da frente da fila
                int u = queue[front++];

                // Agora faco uma iteracao a partir da cabeca do vertice
                ADJACENCY* adj = gr->adjacency_list[u].head;
                while (adj) {
                    int v = adj->vertex;
                    // Verifico se ele ja foi visitado
                    if (!visited[v]) {
                        // Verifico se o vertice foi encontrado
                        // Caso sim, deleto os arrays pra liberar memoria e retorno true
                        if (v == key) {
                            delete[] visited;
                            delete[] queue;
                            return true;
                        }
                        // Caso nao tenha encontrado, adiciono o proximo vertice na fila
                        // E marco esse vertice como visitado
                        queue[++rear] = v;
                        visited[v] = true;
                    }
                    // Caso ja tenha sido visitado ou nao tenha sido encontrado
                    // Vou para o proximo vertice adjacente
                    adj = adj->next;
                }
            }
        }
    }
    // Caso tenha terminado a fila, sem encontrado o resultado
    // Libero a memoria e retorno false
    delete[] visited;
    delete[] queue;
    return false;
}

int main() {
    GRAPH* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    int searchKey = 2;
    if (bfsSearch(graph, searchKey))
        cout << "The key " << searchKey << " was found in the graph." << endl;
    else
        cout << "The key " << searchKey << " was not found in the graph." << endl;

    return 0;
}
