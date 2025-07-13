#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

void insertion(vector<int>&vetor){
	for (int i = 1; i < vetor.size(); i++){
		int num_compara = vetor[i];
		int j = i - 1;

		while (j >= 0 && vetor[j] > num_compara){
			vetor[j + 1] = vetor[j];
			j--;
		}

		vetor[j + 1] = num_compara;
	}
}

void selection(vector<int>& vetor) {
    int tamanho = vetor.size();
    for (int i = 0; i < tamanho - 1; i++) {
        int minimo_idx = i;
        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[minimo_idx]) {
                minimo_idx = j;
            }
        }
        // Troca vetor[i] com vetor[minimp_idx]
        swap(vetor[i], vetor[minimo_idx]);
    }
}

void salvarVetor(const vector<int>& vetor, const string& nomearquivo) {
    ofstream arquivo(nomearquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomearquivo << endl;
        return;
    }

    for (int num : vetor) {
        arquivo << num << " ";
    }
    arquivo << endl;

    arquivo.close();
}

int main(){
	//Mudar o arquivo desejado aqui
	ifstream arq("dados/num.100000.1.in");
	vector <int> vecisrt;
	vector <int> vecselect;
	int numero;

	if (!arq){
		cerr << "Erro ao abrir o arquivo" << endl;
	}

	//Colocando os valores do arquivo dentro do vetor
	while (arq >> numero){
		vecisrt.push_back(numero);
		vecselect.push_back(numero);
	}

	arq.close();

	auto inicioselect = high_resolution_clock::now();
        selection(vecselect);
        auto fimselect = high_resolution_clock::now();

        auto duracaoselect = duration_cast<nanoseconds>(fimselect - inicioselect);


	//Iniciando a contagem exatamente antes de chamar o insertion
	auto inicioisrt = high_resolution_clock::now();
	insertion(vecisrt);
	auto fimisrt = high_resolution_clock::now();
	//Finalizando a contagem logo após o insertion 

	auto duracaoisrt = duration_cast<nanoseconds>(fimisrt - inicioisrt);

	salvarVetor(vecisrt, "output/outputinsert.txt");
        salvarVetor(vecselect, "output/outputselect.txt");
	 
	cout << "Tempo de execução (insertion sort): " << duracaoisrt.count() << " ns" << endl;
	cout << "Tempo de execução (selection sort): " << duracaoselect.count() << " ns" << endl;

	return 0;
}

