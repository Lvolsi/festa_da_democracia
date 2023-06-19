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
	
	std::ofstream arquivo("eleitores.txt", std::ios::app); // Abre o arquivo em modo de adi��o
				
	    if (arquivo.is_open()) { // Verifica se o arquivo foi aberto corretamente
		        
			cout << "Insira o nome do eleitor: " << endl;;
			cin >> elei.nome;
			arquivo <<"*-------------------------------------*" << endl;
			arquivo << "Nome do eleitor: " << elei.nome << endl; // Grava informa��es no arquivo
		        
		   	cout << "Digite o n�mero do t�tulo do eleitor: " << endl;
			cin >> elei.num_titulo;
		    arquivo << "N�mero do t�tulo do eleitor: " << elei.num_titulo << endl;
		    arquivo <<"*-------------------------------------*" << endl;  
		    arquivo.close(); // Fecha o arquivo
		    std::cout << "Informa��es gravadas com sucesso!" << std::endl;
		    } else {
		        std::cout << "N�o foi poss�vel abrir o arquivo." << std::endl;
		    }


    return 0;
}

