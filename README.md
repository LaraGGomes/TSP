# TSP
Resolução do Problema do Caixeiro Viajante (Traveling Salesman Problem) pela abordagem meta-heurística.

---

## Planejamento:
O objetivo é resolver o Problema do Caixeiro Viajante (Traveling Salesman Problem) pela abordagem 
meta-heurística, que visa buscar soluções boas em um tempo razoável, utilizando como base o 
Framework ILS - Iterated Local Search.

A ideia geral do método é encontrar soluções aleatórias, realizar sucessivas operações visando 
o refinamento da solução (ou seja, uma diminuição do custo) até chegar em um "ótimo local", modificar
levemente a solução encontrada, para então repetir o processo iterativo.

Os passos são:
* Construção
* Busca Local
* Pertubação

Vou implementar as funções de cada etapa em um .h separadamente, para então junta-los em uma
biblioteca conjunta com quaisquer outras funções necessárias.

Na main vão ter o maxIter e maxIterIls, que serão parâmetros na chamada da função SolutionILS().

## Rodar o código com uma instância

Compilar o programa: 

    g++ -O3 -std=c++17 *.cpp etapas/*.cpp leitor-instancias/src/Data.cpp -o programa.exe

Rodar uma instância:

    ./programa.exe leitor-instancias/instances/nomedainstancia.tsp