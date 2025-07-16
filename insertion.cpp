#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

void insertion(vector<long long>&vetor){
	for (int i = 1; i < vetor.size(); i++){
		int num_compara = vetor[i]; //numero de comparacao para ser movido
		int j = i - 1;// elemento anterior ao numero

		while (j >= 0 && vetor[j] > num_compara){
			vetor[j + 1] = vetor[j]; // se o elemento anterior for maior, ele sera movido
			j--;// confere a posicao anterior
		}

		vetor[j + 1] = num_compara; // insercao do elemento
	}
}

void selection(vector<long long>& vetor) {
    int tamanho = vetor.size();
    for (int i = 0; i < tamanho - 1; i++) {
        int minimo_idx = i; // considera o primeiro indice como valor minimo
        for (int j = i + 1; j < tamanho; j++) {
            if (vetor[j] < vetor[minimo_idx]) { // se o valor encontrado for menor que o minimo
                minimo_idx = j;//
            }
        }
        if (minimo_idx != i) {
            long long temp = vetor[i];
            vetor[i] = vetor[minimo_idx];
            vetor[minimo_idx] = temp;
        }
    }
}

//guardar as listas ordenadas em arquivos
void salvarVetor(const vector<long long>& vetor, const string& nomearquivo) {
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
	//Mudar o arquivo de teste aqui
	ifstream arq("dados/num.100000.1.in");
	vector <long long> vecisrt;
	vector <long long> vecselect;
	long long numero;

	if (!arq){
		cerr << "Erro ao abrir o arquivo" << endl;
	}

	//valores do arquivo dentro dos vetore
	while (arq >> numero){
		vecisrt.push_back(numero);
		vecselect.push_back(numero);
	}

	arq.close();

	auto inicioselect = high_resolution_clock::now();//marcando o tempo
    selection(vecselect);
    auto fimselect = high_resolution_clock::now();

    auto duracaoselect = duration_cast<nanoseconds>(fimselect - inicioselect);


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

