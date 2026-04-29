#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "Solucao.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef struct InsertionInfo {
    int noInserido;
    int arestaRemovida;
    double custo;
}InsertionInfo;

Solucao Construcao(Data& data);
vector<InsertionInfo> calcularCustoInsercao(Data& data, Solucao& s, vector<int>& CL);
vector<int> escolher3NosAleatorios(Data& data);
vector<int> nosRestantes(Data& data, vector<int> sequencia);
void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao);
void inserirNaSolucao(Solucao& s, InsertionInfo selecionado);

#endif