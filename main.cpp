#include "leitor-instancias/src/Data.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);

    data.read();

    double cost = data.getDistance(1, 2); 
    
    cout << "Matriz carregada! Custo entre cidade 1 e 2: " << cost << std::endl;

    cout << "Dimensao: " << data.getDimension();    // dimensao retorna quantidade de cidades

    return 0;
}
