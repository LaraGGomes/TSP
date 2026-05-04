#include "Framework.h"
#include "leitor-instancias/src/Data.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);

    data.read();

    int maxIterILS;
    int V = data.getDimension();
    
    srand(time(NULL));

    if (V >= 150)
        maxIterILS = V/2;
    else 
        maxIterILS = V;

    Solucao melhorSolucao = ILS(data, 50, maxIterILS);

    cout << "\nCusto da melhor solucao encontrada: " << melhorSolucao.cost << endl;

    return 0;
}
