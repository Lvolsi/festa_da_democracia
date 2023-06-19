#include <iostream>
#include <fstream>

using namespace std;

struct Eleitores{
	int num_titulo;
	char nome[30];
};

int main() {
	setlocale(LC_ALL, "Portuguese");
	Eleitores elei;

	cout << "Cadastro de eleitores: " << endl;;
	
	std::ofstream arquivo("eleitores.txt", std::ios::app); // Abre o arquivo em modo de adição
				
	    if (arquivo.is_open()) { // Verifica se o arquivo foi aberto corretamente
		        
			cout << "Insira o nome do eleitor: " << endl;;
			cin >> elei.nome;
			arquivo <<"*-------------------------------------*" << endl;
			arquivo << "Nome do eleitor: " << elei.nome << endl; // Grava informações no arquivo
		        
		   	cout << "Digite o número do título do eleitor: " << endl;
			cin >> elei.num_titulo;
		    arquivo << "Número do título do eleitor: " << elei.num_titulo << endl;
		    arquivo <<"*-------------------------------------*" << endl;  
		    arquivo.close(); // Fecha o arquivo
		    std::cout << "Informações gravadas com sucesso!" << std::endl;
		    } else {
		        std::cout << "Não foi possível abrir o arquivo." << std::endl;
		    }


    return 0;
}

