#include "Solucao.h"
#include <cstdlib>

bool bestImprovementSwap(Data& data, Solucao *s);
bool bestImprovement2Opt(Data &data, Solucao *s);
bool bestImprovementOrOpt(Data &data, Solucao *s, char tipo);   // coloquei o tipo como char pra ocupar menos
void BuscaLocal(Data& data, Solucao *s);

bool bestImprovementSwap(Data& data, Solucao *s) {
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 1; i < s->sequence.size() - 1; i++) {
        int vi = s->sequence[i];
        int vi_prox = s->sequence[i+1];
        int vi_ante = s->sequence[i-1];

        for(int j = i + 1; j < s->sequence.size() - 1; j++) {
            int vj = s->sequence[j];
            int vj_prox = s->sequence[j+1];
            int vj_ante = s->sequence[j-1];

            double delta = -data.d(vi_ante, vi) - data.d(vi, vi_prox) + data.d(vi_ante, vj)
                            + data.d(vj, vi_prox) - data.d(vj_ante, vj) - data.d(vj, vj_prox)
                            + data.d(vj_ante, vi) + data.d(vi, vj_prox);

            if(delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0) {
        swap(s->sequence[best_i], s->sequence[best_j]);
        s->cost = s->cost + bestDelta;
        return true;
    }

    return false;
}

// ex 1 2 3 4 5 6 1
// 1-2: 3-4, 4-5, 5-6
// 2-3: 4-5, 5-6, 6-1
// 3-4: 5-6, 6-1, 
// 4-5: 6-1
// 5-6

// 1-2, 4-5
// - d(1,2) + d(1,4) - d(4,5) + d(2,5)
// 1 4 3 2 5 6 1

// seleciona dois vértices não adjacentes, remove a prox aresta do primeiro e a anterior do segundo,
// inverter todos os segmentos entre elas, e colocar arestas novas
bool bestImprovement2Opt(Data &data, Solucao *s) {
    double bestDelta = 0;
    int best_i, best_j;

    for (int i = 0; i < s->sequence.size() - 1; i++) {
        int vi = s->sequence[i];
        int vi_prox = s->sequence[i+1];

        // segunda condição garante que não vão haver arestas adjacentes
        for (int j = i + 2; j < s->sequence.size() && s->sequence[j+1] != s->sequence[i]; j++) {
            int vj = s->sequence[j];
            int vj_prox = s->sequence[j+1];

            double delta = - data.d(vi, vi_prox) + data.d(vi, vj) - data.d(vj, vj_prox) + data.d(vi_prox, vj_prox);

            if(delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestDelta < 0) {
        swap(s->sequence[best_i+1], s->sequence[best_j]);

        // tentativa de inversão
        for (int i = best_i+2; i < best_j; i++) {
            for (int j = best_j - 1; j > i; j--) {
                swap(s->sequence[i], s->sequence[j]);
            }
        }

        s->cost += bestDelta;

        return true;
    }

    return false;
}

void BuscaLocal(Data& data, Solucao *s) {
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false) {
        // aleatorizar a operação a ser feita
        int n = rand()% NL.size();
        switch (NL[n]) {
        case 1:
            improved = bestImprovementSwap(data, s);
            break;        
        case 2:
            improved = bestImprovement2Opt(data, s);
            break;        
        case 3:
            improved = bestImprovementOrOpt(data, s, '1');
            break;        
        case 4:
            improved = bestImprovementOrOpt(data, s, '2');
            break;        
        case 5:
            improved = bestImprovementOrOpt(data, s, '3');
            break;        
        }

        if(improved) 
            NL = {1, 2, 3, 4, 5};
        else    // vai realizar novas operações enquanto não houver melhora
            NL.erase(NL.begin() + n);
    }
}
