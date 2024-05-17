#include "grafosClassGetSet.cpp"
#include <iostream>
#include <limits.h>

// https://github.com/Lencione/CPP/tree/main/Grafos-Dijkstra

using namespace std;
typedef int TIPOPESO;

class Dijkstra {
public:
  void inicializaD(GRAFO *g, int *d, int *p, int s) {
    int v;
    for (v = 0; v < g->getVertices(); v++) {
      d[v] = INT_MAX / 2;
      p[v] = -1;
    }
    d[s] = 0;
  }

  void relaxa(GRAFO *g, int *d, int *p, int u, int v) {
    VERTICE *temp = g->getAdj();
    ADJACENCIA *ad = temp[u].getCab();
    while ((ad) && (ad->getVertice() != v))
      ad = ad->getProx();
    if (ad) {
      if (d[v] > d[u] + ad->getPeso()) {
        d[v] = d[u] + ad->getPeso();
        p[v] = u;
      }
    }
  }

  bool existeAberto(GRAFO *g, int *aberto) {
    int i;
    for (i = 0; i < g->getVertices(); i++)
      if (aberto[i])
        return true;
    return false;
  }

  int menorDist(GRAFO *g, int *aberto, int *d) {
    int i;
    for (i = 0; i < g->getVertices(); i++)
      if (aberto[i])
        break;
    if (i == g->getVertices())
      return -1;
    int menor = i;
    for (i = menor + 1; i < g->getVertices(); i++)
      if (aberto[i] && (d[menor] > d[i]))
        menor = i;
    return menor;
  }

  /**
   * Alterei a funcao dijkstra para receber mais dois vetores sendo eles
   * distancias e predecessores
   * e tambem, agora a funcao nao retorna mais nada, ao inves disso
   * Atualiza ambos os vetores durante a execucao
   * */
  void dijkstra(GRAFO *g, int s, int *distancias, int *predecessores) {
    int aberto[g->getVertices()];
    inicializaD(g, distancias, predecessores, s);
    int i;
    for (i = 0; i < g->getVertices(); i++)
      aberto[i] = true;

    while (existeAberto(g, aberto)) {
      int u = menorDist(g, aberto, distancias);
      aberto[u] = false;
      VERTICE *temp = g->getAdj();
      ADJACENCIA *ad = temp[u].getCab();
      while (ad) {
        relaxa(g, distancias, predecessores, u, ad->getVertice());
        ad = ad->getProx();
      }
    }
  }

  /**
   * Adicionei uma funcao recursiva imprimeCaminho 
   * Que tem a responsabilidade de imprimir o caminho do vertice inicial ate o vertice indicado
  */
  void imprimeCaminho(int *predecessores, int vertice)
  {
    if (predecessores[vertice] == -1)
    {
      cout << vertice;
      return;
    }
    imprimeCaminho(predecessores, predecessores[vertice]);
    cout << "->" << vertice;
  }
};

/**
 * Inicializo os vetores de distancia e predecessores
 * E agora chamo a funcao dijkstra passando os dois novos parametros
 * Pra cada vertice, exibo a distancia e o caminho completo usando a funcao recursiva imprimeCaminho
 */
int main() {
  GRAFO *gr = new GRAFO(6);
  gr->criaAresta(0, 1, 10);
  gr->criaAresta(0, 2, 5);
  gr->criaAresta(2, 1, 3);
  gr->criaAresta(1, 3, 1);
  gr->criaAresta(2, 3, 8);
  gr->criaAresta(2, 4, 2);
  gr->criaAresta(4, 5, 6);
  gr->criaAresta(3, 5, 4);
  gr->criaAresta(3, 4, 4);
  gr->imprime();

  Dijkstra dj;
  int distancias[6];
  int predecessores[6];
  dj.dijkstra(gr, 0,distancias,predecessores);
  
  cout << "Menor distância entre V0 e V5 = " << distancias[5] << endl;

  for (int i = 0; i < gr->getVertices(); i++){
    cout << "Distancia (V0 -> V" << i << ") = " << distancias[i] << " => Caminho ";
    dj.imprimeCaminho(predecessores, i);
    cout << endl;
  }

  return 0;
}
