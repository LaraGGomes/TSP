#include "Pertubacao.h"

Solucao Pertubacao(Data& data, Solucao& s) {
    Solucao novaS;
    bool conflito = true;
    int i1, i2;         // intervalos dos segmentos
    int pos1, pos2;     // posição inicial de cada intervalo
    int max = ceil((s.sequence.size() - 1) / 10.0);

    if (max <= 2)
        i1 = i2 = 2;
    else {
        i1 = 2 + rand() % (max - 1);
        i2 = 2 + rand() % (max - 1);
    }

    // garantir que os dois segmentos não se sobreponham
    while (conflito) {
        int limite = s.sequence.size() - 1;
        pos1 = 1 + rand() % (limite - i1);
        pos2 = 1 + rand() % (limite - i2);

        // duas condições de não ter conflito
        if (pos1 < pos2 && pos1 + i1 <= pos2) {
            conflito = false;
        }
        // nesse caso, troco as variáveis pra pos1 ser sempre antes
        else if (pos1 > pos2 && pos1 >= pos2 + i2) {
            swap(pos1,pos2);
            swap(i1,i2);

            conflito = false;
        }
    }

    // cálculo do custo da nova solução
    double delta;
    int v1 = s.sequence[pos1], v1_ante = s.sequence[pos1-1], v1_last = s.sequence[pos1+i1-1];
    int v2 = s.sequence[pos2], v2_prox = s.sequence[pos2+i2], v2_last = s.sequence[pos2+i2-1];

    if(pos2 == pos1 + i1) // caso forem adjacentes
        delta = -data.d(v1_ante, v1) + data.d(v1_ante, v2) - data.d(v2_last, v2_prox) + data.d(v2_last, v1) - data.d(v1_last, v2) + data.d(v1_last, v2_prox);

    else {
        int v1_prox = s.sequence[pos1+i1], v2_ante = s.sequence[pos2-1];

        delta = -data.d(v1_ante, v1) + data.d(v1_ante, v2) - data.d(v2_last, v2_prox) + data.d(v2_last, v1_prox) - data.d(v2_ante, v2) + data.d(v2_ante, v1) - data.d(v1_last, v1_prox) + data.d(v1_last, v2_prox);
    }

    novaS.cost = s.cost + delta;

    // alocação da nova solução
    vector<int> s1(s.sequence.begin() + pos1, s.sequence.begin() + pos1 + i1); // sequencia 1
    vector<int> s2(s.sequence.begin() + pos2, s.sequence.begin() + pos2 + i2); // sequencia 2
    novaS.sequence.reserve(s.sequence.size());  // definindo tamanho

    novaS.sequence.insert(novaS.sequence.end(), s.sequence.begin(), s.sequence.begin() + pos1);

    novaS.sequence.insert(novaS.sequence.end(), s2.begin(), s2.end());

    novaS.sequence.insert(novaS.sequence.end(), s.sequence.begin() + pos1 + i1, s.sequence.begin() + pos2);

    novaS.sequence.insert(novaS.sequence.end(), s1.begin(), s1.end());

    novaS.sequence.insert(novaS.sequence.end(), s.sequence.begin() + pos2 + i2, s.sequence.end());

    return novaS;
}