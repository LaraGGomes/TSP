#include <iostream>     // cout
#include <vector>       // vetor 
#include <algorithm>    // sort
#include "leitor-instancias/src/Data.h"

using namespace std;
/*uso ou não?? não afeta performance, afeta miiiiinimamente tempo de execução, 
mas a pira mesmo seria eu considerar o que ficaria mais bonitinho
*/

#define d(x, y) getDistance(x, y);
// pra simplificar o getDistance, que calcula o custo entre dois vértices

typedef struct Solucao {
    vector<int> sequence;
    double cost;
} Solucao;

// protótipos das funções de solução
void exibirSolucao(Solucao *s);
void calcularCusto(Data *data, Solucao *s);

void exibirSolucao(Solucao *s) {
    for (int i = 0; i < s->sequence.size() - 1; i++) 
        cout << s->sequence[i] << " -> ";

    cout << s->sequence.back() << endl;
}

void calcularCusto(Data *data, Solucao *s) {
    s->cost = 0;
    for (int i = 0; i < s->sequence.size() - 1; i++)
        s->cost += data->getDistance(s->sequence[i], s->sequence[i+1]);
        // o getDistance(x, y) é o matrizAdj[x][y]
}