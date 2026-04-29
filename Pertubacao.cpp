#include "Pertubacao.h"

Solucao Pertubacao(Data& data, Solucao s) {
    Solucao novaS;
    bool conflito = true;
    int i1, i2;         // intervalos dos segmentos
    int pos1, pos2;     // posição inicial de cada intervalo
    int max = ceil((s.sequence.size() - 1) / 10.0);   // perguntar pra Marcelo se é módulo de 10 ou to interpretando errado

    novaS.sequence = s.sequence;

    srand(time(NULL));

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

        if (pos1 < pos2 && pos1 + i1 <= pos2 || pos1 > pos2 && pos1 >= pos2 + i2) {
            conflito = false;
        }
        // ou coloco pos1 < pos2 && pos1 + i1 <= pos2, limitando que s1 seja antes de s2
    }

    vector<int> s1(novaS.sequence.begin() + pos1, novaS.sequence.begin() + pos1 + i1); // sequencia 1
    vector<int> s2(novaS.sequence.begin() + pos2, novaS.sequence.begin() + pos2 + i2); // sequencia 2

    int s1_ante = novaS.sequence[pos1-1];

    // inserindo s1
    for(int i = s1.size() - 1; i >= 0; i--) {
        novaS.sequence.insert(novaS.sequence.begin() + pos2, s1[i]);
    }

    auto pos_ante = find(novaS.sequence.begin(), novaS.sequence.end(), s1_ante);

    // o mais a direita deve ser removido primeiro
    if (pos1 > pos2) {
        // remove s1 antigo
        for (int _ : s1) {
            novaS.sequence.erase(pos_ante + 1);
        }

        // remove s2
        for (int _ : s2) {
            novaS.sequence.erase(novaS.sequence.begin() + pos2 + s1.size());
        }
    }

    else {
        // remove s2
        for (int _ : s2) {
            novaS.sequence.erase(novaS.sequence.begin() + pos2 + s1.size());
        }

        // remove s1 antigo
        for (int _ : s1) {
            novaS.sequence.erase(pos_ante + 1);
        }

    }

    // insere s2
    if (pos1 < pos2) {
        for(int i = s2.size() - 1; i >= 0; i--)
            novaS.sequence.insert(novaS.sequence.begin() + pos1, s2[i]);
    }
    else {
        for(int i = s2.size() - 1; i >= 0; i--)
            novaS.sequence.insert(novaS.sequence.begin() + pos1 - s2.size() + s1.size(), s2[i]);
    }

    calcularCusto(data, &novaS);

    return novaS;
}