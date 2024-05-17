#include <iostream>
using namespace std;
typedef int TIPOPESO;

class ADJACENCIA
{
private:
    int vertice;
    TIPOPESO peso;
    ADJACENCIA *prox;

public:
    int getVertice() { return vertice; }
    void setVertice(int vertice) { this->vertice = vertice; }
    void setPeso(TIPOPESO peso) { this->peso = peso; }
    TIPOPESO getPeso() { return peso; }
    void setProx(ADJACENCIA *prox) { this->prox = prox; }
    ADJACENCIA *getProx() { return prox; }
};

class VERTICE
{
private:
    // outros dados
    ADJACENCIA *cab;

public:
    void setCab(ADJACENCIA *cab) { this->cab = cab; }
    ADJACENCIA *getCab() { return cab; }
};

class GRAFO
{
private: // no BFS ou DFS mudar para public ou implementar getter and setter
    int vertices;
    int arestas;
    VERTICE *adj;

public:
    GRAFO()
    {
        cout << "Necessario informar o numero de vertices" << endl;
        cout << "Programa sera encerrado" << endl
             << endl;
        exit(-1);
    }
    GRAFO(int v)
    {
        int i;
        vertices = v;
        arestas = 0;
        adj = new VERTICE[v];
        for (i = 0; i < v; i++)
        {
            adj[i].setCab(NULL);
        }
    }

    int getVertices() { return vertices; }
    void setVertices(int vertices) { this->vertices = vertices; }
    int getArestas() { return arestas; }
    void setArestas(int arestas) { this->arestas = arestas; }
    VERTICE *getAdj() { return adj; }
    void setAdj(VERTICE *adj) { this->adj = adj; }

    ADJACENCIA *criaAdj(int v, int peso)
    {
        ADJACENCIA *temp = new ADJACENCIA;
        temp->setVertice(v);
        temp->setPeso(peso);
        temp->setProx(NULL);
        return (temp);
    }

    bool criaAresta(int vi, int vf, TIPOPESO p)
    {
        /*if (!gr)
          return false;*/
        if ((vf < 0) || (vf >= vertices))
            return false;
        if ((vi < 0) || (vi >= vertices))
            return false;
        ADJACENCIA *novo = criaAdj(vf, p);
        novo->setProx(adj[vi].getCab());
        adj[vi].setCab(novo);
        arestas++;
        return true;
    }

    void imprime()
    {
        int i;
        cout << "Vertices: " << vertices << ", Aresta: " << arestas << endl;
        for (i = 0; i < vertices; i++)
        {
            cout << "v" << i << ": ";
            ADJACENCIA *ad = adj[i].getCab();
            while (ad)
            {
                cout << "v" << ad->getVertice() << "(" << ad->getPeso() << ") ";
                ad = ad->getProx();
            }
            cout << endl;
        }
    }
};