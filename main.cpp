#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // para atoi

using namespace std;

struct Candidato {
    string nome;
    int numero;
    int votos;
    Candidato* prox;
};

struct Eleitor {
    string nome;
    int titulo;
    Eleitor* prox;
};

Candidato* candidatos = NULL;
Eleitor* eleitores = NULL;

void inserirCandidato(string nome, int numero) {
    Candidato* novoCandidato = new Candidato;
    novoCandidato->nome = nome;
    novoCandidato->numero = numero;
    novoCandidato->votos = 0;
    novoCandidato->prox = NULL;

    if (candidatos == NULL) {
        candidatos = novoCandidato;
    } else {
        Candidato* atual = candidatos;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoCandidato;
    }

    cout << "Candidato cadastrado com sucesso!" << endl;
}

void inserirEleitor(string nome, int titulo) {
    Eleitor* novoEleitor = new Eleitor;
    novoEleitor->nome = nome;
    novoEleitor->titulo = titulo;
    novoEleitor->prox = NULL;

    if (eleitores == NULL) {
        eleitores = novoEleitor;
    } else {
        Eleitor* atual = eleitores;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoEleitor;
    }

    cout << "Eleitor cadastrado com sucesso!" << endl;
}

void liberarCandidatos() {
    Candidato* atual = candidatos;
    while (atual != NULL) {
        Candidato* prox = atual->prox;
        delete atual;
        atual = prox;
    }
    candidatos = NULL;
}

void liberarEleitores() {
    Eleitor* atual = eleitores;
    while (atual != NULL) {
        Eleitor* prox = atual->prox;
        delete atual;
        atual = prox;
    }
    eleitores = NULL;
}

void listarCandidatos() {
    Candidato* atual = candidatos;
    if (atual == NULL) {
        cout << "Nenhum candidato cadastrado." << endl;
    } else {
        cout << "Lista de candidatos:" << endl;
        while (atual != NULL) {
            cout << "Nome: " << atual->nome << ", Numero: " << atual->numero << ", Votos: " << atual->votos << endl;
            atual = atual->prox;
        }
    }
}

void listarEleitores() {
    Eleitor* atual = eleitores;
    if (atual == NULL) {
        cout << "Nenhum eleitor cadastrado." << endl;
    } else {
        cout << "Lista de eleitores:" << endl;
        while (atual != NULL) {
            cout << "Nome: " << atual->nome << ", Titulo: " << atual->titulo << endl;
            atual = atual->prox;
        }
    }
}

void salvarCandidatos() {
    ofstream arquivo("candidatos.txt");
    if (arquivo.is_open()) {
        Candidato* atual = candidatos;
        while (atual != NULL) {
            arquivo << atual->nome << " " << atual->numero << " " << atual->votos << endl;
            atual = atual->prox;
        }
        arquivo.close();
        cout << "Dados dos candidatos salvos com sucesso." << endl;
    } else {
        cout << "Nao foi possivel abrir o arquivo de candidatos." << endl;
    }
}

void salvarEleitores() {
    ofstream arquivo("eleitores.txt");
    if (arquivo.is_open()) {
        Eleitor* atual = eleitores;
        while (atual != NULL) {
            arquivo << atual->nome << " " << atual->titulo << endl;
            atual = atual->prox;
        }
        arquivo.close();
        cout << "Dados dos eleitores salvos com sucesso." << endl;
    } else {
        cout << "Nao foi possivel abrir o arquivo de eleitores." << endl;
    }
}

void carregarCandidatos() {
    ifstream arquivo("candidatos.txt");
    if (arquivo.is_open()) {
        liberarCandidatos();
        string linha;
        while (getline(arquivo, linha)) {
            string nome;
            int numero;
            int votos;
            sscanf(linha.c_str(), "%s %d %d", &nome[0], &numero, &votos);
            inserirCandidato(nome, numero);
        }
        arquivo.close();
        cout << "Dados dos candidatos carregados com sucesso." << endl;
    } else {
        cout << "Nao foi possivel abrir o arquivo de candidatos." << endl;
    }
}

void carregarEleitores() {
    ifstream arquivo("eleitores.txt");
    if (arquivo.is_open()) {
        liberarEleitores();
        string linha;
        while (getline(arquivo, linha)) {
            string nome;
            int titulo;
            sscanf(linha.c_str(), "%s %d", &nome[0], &titulo);
            inserirEleitor(nome, titulo);
        }
        arquivo.close();
        cout << "Dados dos eleitores carregados com sucesso." << endl;
    } else {
        cout << "Nao foi possivel abrir o arquivo de eleitores." << endl;
    }
}

int main() {
    int opcao;
    bool sair = false;

    while (!sair) {
        cout << "-------- Festa da Democracia --------" << endl;
        cout << "1 - Inserir candidato" << endl;
        cout << "2 - Inserir eleitor" << endl;
        cout << "3 - Listar candidatos" << endl;
        cout << "4 - Listar eleitores" << endl;
        cout << "5 - Salvar candidatos" << endl;
        cout << "6 - Salvar eleitores" << endl;
        cout << "7 - Carregar candidatos" << endl;
        cout << "8 - Carregar eleitores" << endl;
        cout << "9 - Sair" << endl;
        cout << "-------------------------------------" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                string nome;
                int numero;
                cout << "Digite o nome do candidato: ";
                cin >> nome;
                cout << "Digite o numero do candidato: ";
                cin >> numero;
                inserirCandidato(nome, numero);
                break;
            }
            case 2: {
                string nome;
                int titulo;
                cout << "Digite o nome do eleitor: ";
                cin >> nome;
                cout << "Digite o titulo do eleitor: ";
                cin >> titulo;
                inserirEleitor(nome, titulo);
                break;
            }
            case 3:
                listarCandidatos();
                break;
            case 4:
                listarEleitores();
                break;
            case 5:
                salvarCandidatos();
                break;
            case 6:
                salvarEleitores();
                break;
            case 7:
                carregarCandidatos();
                break;
            case 8:
                carregarEleitores();
                break;
			case 9:
                sair = true;
                break;
            default:
                cout << "Opcao invalida. Digite novamente." << endl;
        }

        cout << endl;
    }

    liberarCandidatos();
    liberarEleitores();

    return 0;
}

