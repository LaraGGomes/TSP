#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <iostream>
#include <vector>
#include "leitor-instancias/src/Data.h"

using namespace std;

typedef struct Solucao {
    vector<int> sequence;
    double cost;
} Solucao;

void exibirSolucao(Solucao *s);
void calcularCusto(Data& data, Solucao *s);

#define d(x, y) getDistance(x, y)
// pra simplificar o getDistance, que calcula o custo entre dois vértices

#endif