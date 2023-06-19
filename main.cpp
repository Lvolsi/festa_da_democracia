#include <iostream>
#include <fstream>
#include <string>
#include "lista_dinamica.h"

using namespace std;

void SaveListaToFile(Lista* lista, const char* filename);
void LoadListaFromFile(Lista* lista, const char* filename);
void Search_Lista(Lista* L, int x);


void SaveListaToFile(Lista* lista, const char* filename){
	ofstream arquivo(filename, ios::out | ios::app);
   

    if (arquivo.is_open()) {
        no* atual = lista->inicio;

        while (atual != NULL) {
            Candidatos* cand = atual->info;
            arquivo << "Nome do candidato: " << cand->nome << endl;
            arquivo << "Número do candidato: " << cand->num_candidato << endl;
            //arquivo << "*-------------------------------------*" << endl;

            atual = atual->prox;
        }

        arquivo.close();
        cout << "Informações gravadas com sucesso!" << endl;
    }
    else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void LoadListaFromFile(Lista* lista, const char* filename) {
    ifstream arquivo(filename);

    if (arquivo.is_open()) {
        string line;

        while (getline(arquivo, line)) {
            if (line.find("Nome do candidato: ") == 0) {
                Candidatos* cand = new Candidatos;

                // Extrair o nome do candidato removendo o prefixo da linha
                string nome = line.substr(19);
                strcpy(cand->nome, nome.c_str());

                // Ler a próxima linha contendo o número do candidato
                getline(arquivo, line);
                if (line.find("Número do candidato: ") == 0) {
                    // Extrair o número do candidato removendo o prefixo da linha
                    string num_str = line.substr(21);
                    cand->num_candidato = atoi(num_str.c_str());

                    Insert_Lista(lista, cand);
                } else {
                    // A linha esperada não foi encontrada, descartar o candidato
                    delete cand;
                }
            }
        }

        arquivo.close();
        cout << "Informações carregadas com sucesso!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}




int main() {
    setlocale(LC_ALL, "Portuguese");

    Lista listaCandidatos;
    Create_Lista(&listaCandidatos);
    LoadListaFromFile(&listaCandidatos, "candidatos.txt");

    int menu;
    while (menu != 4) {
        cout << "*--------------------------------------------------*" << endl;
        cout << "Menu de opções da festa da democracia: " << endl;
        cout << "Escolha uma das opções abaixo: " << endl;
        cout << "1 - Inserir novos candidatos na eleição;" << endl;
        cout << "2 - Listar os candidatos inscritos na eleição;" << endl;
        cout << "3 - Remover candidatos da eleição;" << endl;
        cout << "4 - Sair." << endl;
        cout << "*--------------------------------------------------*" << endl;
        cout << "Digite o número da opção desejada: ";
        cin >> menu;

        switch (menu) {
            case 1: {
                Candidatos* cand = new Candidatos;

                cout << endl;
                cout << "Nome do candidato: ";
                cin >> cand->nome;
                cout << "Número do candidato: ";
                cin >> cand->num_candidato;

                Insert_Lista(&listaCandidatos, cand);

                cout << "Candidato inserido com sucesso!" << endl;
                break;
            }
            case 2: {
                cout << "Lista de candidatos inscritos na eleição: " << endl;
                if (IsEmpty_Lista(&listaCandidatos)) {
                    cout << "Não há candidatos na lista." << endl;
                } else {
                    Print_Lista(&listaCandidatos);
                }
                break;
            }
            case 3: {
                if (IsEmpty_Lista(&listaCandidatos)) {
                    cout << "Não há candidatos na lista." << endl;
                } else {
                    bool erro;
                    Candidatos* removedCandidate = Remove_Lista(&listaCandidatos, &erro);
                    cout << "Candidato removido: " << removedCandidate->nome << " (Número: " << removedCandidate->num_candidato << ")" << endl;
                    delete removedCandidate;
                }
                break;
            }
            case 4:
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opção inválida." << endl;
        }
    }

    SaveListaToFile(&listaCandidatos, "candidatos.txt");  // Grava a lista atualizada no arquivo

    return 0;
}

