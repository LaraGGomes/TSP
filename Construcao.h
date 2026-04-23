#include "Solucao.h"
#include <cstdlib>  // rand

using namespace std;

typedef struct InsertionInfo {
    int noInserido;
    int arestaRemovida;
    double custo;
}InsertionInfo;

// protótipo das funções necessárias
vector<InsertionInfo> calcularCustoInsercao(Data& data, Solucao& s, vector<int>& CL);
vector<int> escolher3NosAleatorios(Data& data);
vector<int> nosRestantes(Data& data, vector<int> sequencia);
void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao);
void inserirNaSolucao(Solucao& s, InsertionInfo selecionado);

// vai receber um subtour aleatório, e CL são os vértices restantes não inclusos no subtour
vector<InsertionInfo> calcularCustoInsercao(Data& data, Solucao& s, vector<int>& CL) {

    vector<InsertionInfo> custoInsercao((s.sequence.size() - 1) * CL.size());   // delimitando tamanho do vetor
    int l = 0;

    for (int a = 0; a < s.sequence.size(); a++) {
        int i = s.sequence[a];
        int j = s.sequence[a+1];

        // para cada nó restante, vamos registrar as informações de inserção em uma posição do vetor 
        for (auto k : CL) {
            // novo custo é calculado adicionando as distância entre a nova aresta e os vértices e removendo a distância entre os dois vértices
            custoInsercao[l].custo = data.d(i, k) + data.d(j, k) - data.d(i, j);
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;

            l++;
        }
    }
    return custoInsercao;   
}

vector<int> escolher3NosAleatorios(Data& data) {
    vector<int> s;

    s.push_back(1);

    for(int i = 0; i < 3; i++) {
        int no;
        bool rep = true;    // checagem de repetição de vértice

        while(rep) {
            no = rand() % data.getDimension() + 1; 

            // vai procurar o no aleatorizado no vetor, se não encontra retorna s.end() 
            if (find(s.begin(), s.end(), no) == s.end()) {
                rep = false;
            }
        }
        s.push_back(no);
    }

    s.push_back(1);
    return s;
}

vector<int> nosRestantes(Data& data, vector<int> sequencia) {
    vector<int> CL;

    // aqui o intuito é inserir cada vértice no vetor, caso ele não seja encontrado na sequência
    for (int i = 1; i <= data.getDimension(); i++) {
        if (find(sequencia.begin(), sequencia.end(), i) == sequencia.end()) {
            CL.push_back(i);
        }
    }

    return CL;
}

void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao) {

    for (int i = 0; i < custoInsercao.size(); i++) {

        for (int j = i+1; j < custoInsercao.size(); j++) {

            if (custoInsercao[i].custo > custoInsercao[j].custo) {
                InsertionInfo aux = custoInsercao[i];
                custoInsercao[i] = custoInsercao[j];
                custoInsercao[j] = aux;
            }

        }
    }
}

// aqui eu to recebendo como parâmetro o insertionInfo completo do nó selecionado porque eu vou precisar saber
// em qual posição eu insiro o nó na solução
void inserirNaSolucao(Solucao& s, InsertionInfo selecionado) {
    // vertice inicial onde será posicionado o novo nó 
    int vertice = selecionado.arestaRemovida;

    // posição do vértice
    auto pos = find(s.sequence.begin(), s.sequence.end(), vertice);

    // inserção do nó
    s.sequence.insert(pos+1, selecionado.noInserido);
}

Solucao Construcao(Data& data) {
    // vamos criar uma solução parcial com 3 nós aleatórios e guardar os nós restantes em CL
    Solucao s;

    s.sequence = escolher3NosAleatorios(data);
    vector<int> CL = nosRestantes(data, s.sequence);

    // enquanto houverem nós restantes, vamos randomizar qual nó será inserido na solução um por um
    while(!CL.empty()) {
        vector<InsertionInfo> custoInsercao = calcularCustoInsercao(data, s, CL);

        ordenarEmOrdemCrescente(custoInsercao);

        double alpha = (double)rand()/RAND_MAX;
        int selecionado = rand()%((int)ceil(alpha * custoInsercao.size()));

        inserirNaSolucao(s, custoInsercao[selecionado]);

        CL.erase(CL.begin() + selecionado); // removendo o nó selecionado do CL
    }

    return s;
}