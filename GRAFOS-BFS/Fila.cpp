#include <iostream>
using namespace std;
typedef int TIPOCHAVE;

struct REGISTRO {
  TIPOCHAVE chave;
  // outros campos ...
};

struct ELEMENTO {
  REGISTRO reg;
  ELEMENTO *prox;
};

typedef ELEMENTO *PONT;

struct FILA {
  PONT inicio;
  PONT fim;
};

void inicializarFila(FILA *f) {
  f->inicio = NULL;
  f->fim = NULL;
}

bool inserirNaFila(FILA *f, REGISTRO reg) {
  PONT novo = new ELEMENTO;
  novo->reg = reg;
  novo->prox = NULL;
  if (f->inicio == NULL)
    f->inicio = novo;
  else
    f->fim->prox = novo;
  f->fim = novo;
  return true;
}

bool excluirDaFila(FILA *f, REGISTRO *reg) {
  if (f->inicio == NULL)
    return false;
  *reg = f->inicio->reg;
  PONT apagar = f->inicio;
  f->inicio = f->inicio->prox;
  free(apagar);
  if (f->inicio == NULL)
    f->fim = NULL;
  return true;
}
