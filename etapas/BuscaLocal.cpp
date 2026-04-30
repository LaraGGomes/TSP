#include "BuscaLocal.h"

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

            double delta;
            // fórmula é diferente pra vértices adjacentes
            if (j == i + 1) {
                delta = - data.d(vi_ante, vi) + data.d(vi, vj_prox) - data.d(vj, vj_prox) + data.d(vi_ante, vj);
            }
            else {
                delta = -data.d(vi_ante, vi) - data.d(vi, vi_prox) + data.d(vi_ante, vj)
                        + data.d(vj, vi_prox) - data.d(vj_ante, vj) - data.d(vj, vj_prox)
                        + data.d(vj_ante, vi) + data.d(vi, vj_prox);
            }

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

// seleciona dois vértices não adjacentes, remove as arestas,
// inverter todos os segmentos entre elas, e colocar arestas novas
bool bestImprovement2Opt(Data &data, Solucao *s) {
    double bestDelta = 0;
    int best_i, best_j;

    for (int i = 0; i < s->sequence.size() - 1; i++) {
        int vi = s->sequence[i];
        int vi_prox = s->sequence[i+1];

        // segunda condição garante que não vão haver arestas adjacentes
        for (int j = i + 2; j < s->sequence.size() - 1 && s->sequence[j+1] != s->sequence[i]; j++) {
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

        // inversão do segmento entre as arestas
        for (int i = best_i+2, j = best_j - 1; i < best_j && j > i; i++, j--) {
            swap(s->sequence[i], s->sequence[j]);
        }

        s->cost += bestDelta;

        return true;
    }

    return false;
}

// seleciona x vértices adjacentes, remove e então reensere em uma nova posição
bool bestImprovementOrOpt(Data &data, Solucao *s, int tipo) {
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 1; i <= s->sequence.size() - 1 - tipo; i++) {
        int vi = s->sequence[i];
        int vi_prox = s->sequence[i+tipo];
        int vi_ante = s->sequence[i-1];
        int vi_last = s->sequence[i+tipo-1];

        for(int j = 1; j < s->sequence.size() - 1; j++) {
            if (j - i <= tipo + 1 && j - i >= 0) continue;

            int vj = s->sequence[j];
            int vj_ante = s->sequence[j-1];

            double delta = -data.d(vi_ante, vi) + data.d(vi_ante, vi_prox) - data.d(vj_ante, vj) + data.d(vj_ante, vi) - data.d(vi_last, vi_prox) + data.d(vi_last, vj);

            if(delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestDelta < 0) {
        vector<int> segmento(s->sequence.begin() + best_i, s->sequence.begin() + best_i + tipo);

        s->sequence.erase(s->sequence.begin() + best_i, s->sequence.begin() + best_i + tipo);

        if(best_i < best_j) 
            s->sequence.insert(s->sequence.begin() + best_j - tipo, segmento.begin(), segmento.end());
        else 
            s->sequence.insert(s->sequence.begin() + best_j, segmento.begin(), segmento.end());

        s->cost += bestDelta;

        return true;
    }

    return false;  
}

void BuscaLocal(Data& data, Solucao *s) {
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false) {

        int n = rand()% NL.size();
        switch (NL[n]) {
        case 1:
            improved = bestImprovementSwap(data, s);
            break;        
        case 2:
            improved = bestImprovement2Opt(data, s);
            break;        
        case 3:
            improved = bestImprovementOrOpt(data, s, 1);
            break;        
        case 4:
            improved = bestImprovementOrOpt(data, s, 2);
            break;        
        case 5:
            improved = bestImprovementOrOpt(data, s, 3);
            break;        
        }

        if(improved) 
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}
