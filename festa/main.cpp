#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

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
    int voto;
    Eleitor* prox;
};

Candidato* listaCandidatos = NULL;
Eleitor* listaEleitores = NULL;
Eleitor* filaVotacao = NULL;

void cadastrarCandidato() {
    string nome;
    int numero;

    cout << "Digite o nome do candidato: ";
    cin.ignore();
    getline(cin, nome);

    cout << "Digite o numero do candidato: ";
    cin >> numero;

    Candidato* novoCandidato = new Candidato;
    novoCandidato->nome = nome;
    novoCandidato->numero = numero;
    novoCandidato->prox = NULL;

    if (listaCandidatos == NULL) {
        listaCandidatos = novoCandidato;
    } else {
        Candidato* atual = listaCandidatos;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoCandidato;
    }

    // Salvar candidato no arquivo
    ofstream arquivoCandidatos("candidatos.txt", ios::app); // Abre o arquivo em modo de escrita (append)
    if (arquivoCandidatos.is_open()) {
        arquivoCandidatos << nome << "," << numero << endl;
        arquivoCandidatos.close();
        cout << "Candidato cadastrado com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo de candidatos." << endl;
    }
}

void cadastrarEleitor() {
    string nome;
    int titulo;

    cout << "Digite o nome do eleitor: ";
    cin.ignore();
    getline(cin, nome);

    cout << "Digite o titulo do eleitor: ";
    cin >> titulo;

    Eleitor* novoEleitor = new Eleitor;
    novoEleitor->nome = nome;
    novoEleitor->titulo = titulo;
    novoEleitor->prox = NULL;

    if (listaEleitores == NULL) {
        listaEleitores = novoEleitor;
    } else {
        Eleitor* atual = listaEleitores;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoEleitor;
    }

    // Salvar eleitor no arquivo
    ofstream arquivoEleitores("eleitores.txt", ios::app); // Abre o arquivo em modo de escrita (append)
    if (arquivoEleitores.is_open()) {
        arquivoEleitores << nome << " " << titulo << endl;
        arquivoEleitores.close();
        cout << "Eleitor cadastrado com sucesso." << endl;
    } else {
        cout << "Erro ao abrir o arquivo de eleitores." << endl;
    }
}
void carregarCandidatos() {
    ifstream arquivo("candidatos.txt");
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string nomeNumero;
            ss >> nomeNumero;

            // Encontrar a posição da última vírgula na string
            size_t pos = nomeNumero.find_last_of(",");

            // Extrair o nome e o número com base na posição da última vírgula
            string nome = nomeNumero.substr(0, pos);
            int numero = atoi(nomeNumero.substr(pos + 1).c_str());

            Candidato* novoCandidato = new Candidato;
            novoCandidato->nome = nome;
            novoCandidato->numero = numero;
            novoCandidato->prox = NULL;

            if (listaCandidatos == NULL) {
                listaCandidatos = novoCandidato;
            } else {
                Candidato* atual = listaCandidatos;
                while (atual->prox != NULL) {
                    atual = atual->prox;
                }
                atual->prox = novoCandidato;
            }
        }
        arquivo.close();
        cout << "Candidatos carregados com sucesso." << endl;
    } else {
        cout << "Nao foi possivel abrir o arquivo de candidatos." << endl;
    }
}



void carregarEleitores() {
    ifstream arquivo("eleitores.txt");
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string nome;
            int titulo;
            ss >> nome >> titulo;
            Eleitor* novoEleitor = new Eleitor;
            novoEleitor->nome = nome;
            novoEleitor->titulo = titulo;
            novoEleitor->prox = NULL;
            if (listaEleitores == NULL) {
                listaEleitores = novoEleitor;
            } else {
                Eleitor* atual = listaEleitores;
                while (atual->prox != NULL) {
                    atual = atual->prox;
                }
                atual->prox = novoEleitor;
            }
        }
        arquivo.close();
        cout << "Eleitores carregados com sucesso." << endl;
    } else {
        cout << "Nao foi possivel abrir o arquivo de eleitores." << endl;
    }
}

void listarCandidatos() {
    Candidato* atual = listaCandidatos;
    if (atual == NULL) {
        cout << "Nao ha candidatos cadastrados." << endl;
    } else {
        cout << "Candidatos:" << endl;
        while (atual != NULL) {
            cout << "Nome: " << atual->nome << ", Numero: " << atual->numero << endl;
            atual = atual->prox;
        }
    }
}



void listarEleitores() {
    Eleitor* atual = listaEleitores;
    if (atual == NULL) {
        cout << "Nao ha eleitores cadastrados." << endl;
    } else {
        cout << "Eleitores:" << endl;
        while (atual != NULL) {
            cout << "Nome: " << atual->nome << ", Titulo: " << atual->titulo << endl;
            atual = atual->prox;
        }
    }
}

bool verificarAptoParaVotar(int tituloEleitor) {
    Eleitor* atual = listaEleitores;
    while (atual != NULL) {
        if (atual->titulo == tituloEleitor) {
            return true;
        }
        atual = atual->prox;
    }
    return false;
}

void inserirNaFila(int tituloEleitor) {
    if (!verificarAptoParaVotar(tituloEleitor)) {
        cout << "Eleitor nao esta apto para votar." << endl;
        return;  // Retorna sem inserir o eleitor na fila
    }

    Eleitor* eleitor = new Eleitor;
    eleitor->titulo = tituloEleitor;
    eleitor->voto = 0;
    eleitor->prox = NULL;

    if (filaVotacao == NULL) {
        filaVotacao = eleitor;
    } else {
        Eleitor* atual = filaVotacao;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = eleitor;
    }

    cout << "Eleitor inserido na fila de votacao." << endl;
}


 void salvarVotos() {
    ofstream arquivo("votos.txt");
    if (arquivo.is_open()) {
        Candidato* candidatoAtual = listaCandidatos;
        while (candidatoAtual != NULL) {
            int votosCandidato = 0;
            Eleitor* atual = listaEleitores;
            while (atual != NULL) {
                if (atual->voto == candidatoAtual->numero) {
                    votosCandidato++;
                }
                atual = atual->prox;
            }
            arquivo << "Candidato: " << candidatoAtual->nome << ", Votos: " << votosCandidato << endl;
            candidatoAtual = candidatoAtual->prox;
        }
        arquivo.close();
        cout << "Votos salvos com sucesso." << endl;
    } else {
        cout << "Não foi possível abrir o arquivo de votos." << endl;
    }
}


int totalVotosRegistrados = 0;
int eleitoresFaltantes = 0;

Candidato* buscarCandidato(const string& nome) {
    Candidato* atual = listaCandidatos;
    while (atual != NULL) {
        if (atual->nome == nome) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;  // Retorna NULL se o candidato não for encontrado
}

Candidato* buscarCandidatoPorNumero(int numero) {
    Candidato* atual = listaCandidatos;
    while (atual != NULL) {
        if (atual->numero == numero) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;  // Retorna NULL se o candidato não for encontrado
}


void salvarRelatorio() {
    ofstream arquivoRelatorio("votos.txt");
    if (arquivoRelatorio.is_open()) {
        arquivoRelatorio << "Relatorio de votos por candidato:" << endl;

        Candidato* atual = listaCandidatos;
        while (atual != NULL) {
            arquivoRelatorio << "Candidato: " << atual->nome << ", Votos: " << atual->votos << endl;
            atual = atual->prox;
        }

        arquivoRelatorio << "Total de votos registrados: " << totalVotosRegistrados << endl;
        arquivoRelatorio << "Eleitores faltantes: " << eleitoresFaltantes << endl;

        arquivoRelatorio.close();
    } else {
        cout << "Nao foi possivel abrir o arquivo de relatorio." << endl;
    }
}

bool verificarEleitorNaFila(int tituloEleitor) {
    Eleitor* atual = filaVotacao;
    while (atual != NULL) {
        if (atual->titulo == tituloEleitor) {
            return true;
        }
        atual = atual->prox;
    }
    return false;
}



int main() {
    int opcao;
    do {
        cout << "----- MENU -----" << endl;
        cout << "1 - Cadastrar candidatos" << endl;
        cout << "2 - Cadastrar eleitores" << endl;
        cout << "3 - Carregar candidatos" << endl;
        cout << "4 - Carregar eleitores" << endl;
        cout << "5 - Listar candidatos" << endl;
        cout << "6 - Listar eleitores" << endl;
        cout << "7 - Verificar aptidao eleitoral" << endl;
        cout << "8 - Inserir eleitor na fila de votacao" << endl;
        cout << "9 - Mostrar fila de votacao" << endl;
        cout << "10 - Registrar voto" << endl;
        cout << "11 - Salvar votos" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cout << "----------------" << endl;

        switch (opcao) {
        	case 1: {
                cadastrarCandidato();
                break;
            }
            case 2: {
                cadastrarEleitor();
                break;
            }
            case 3: {
                carregarCandidatos();
                break;
            }
            case 4: {
                carregarEleitores();
                break;
            }
            case 5: {
                listarCandidatos();
                break;
            }
            case 6: {
                listarEleitores();
                break;
            }
            case 7: {
                int titulo;
                cout << "Digite o titulo do eleitor: ";
                cin >> titulo;
                if (verificarAptoParaVotar(titulo)) {
                    cout << "Eleitor apto para votar." << endl;
                } else {
                    cout << "Eleitor nao apto para votar." << endl;
                }
                break;
            }
            case 8: {
                int titulo;
                cout << "Digite o titulo do eleitor: ";
                cin >> titulo;
                inserirNaFila(titulo);
                break;
            }
            case 9: {
                Eleitor* atual = filaVotacao;
                if (atual == NULL) {
                    cout << "Nao ha eleitores aguardando para votar." << endl;
                } else {
                    cout << "Fila de votacao:" << endl;
                    while (atual != NULL) {
                        cout << "Titulo: " << atual->titulo << endl;
                        atual = atual->prox;
                    }
                }
                break;
            }
         case 10: { 
		    // Registrar voto
		    int titulo, voto;
		    cout << "Digite o titulo do eleitor: ";
		    cin >> titulo;
		    
		    if (verificarAptoParaVotar(titulo)) {
		        if (verificarEleitorNaFila(titulo)) {
		            Candidato* candidatoAtual = listaCandidatos;
		            cout << "Candidatos disponiveis:" << endl;
		            while (candidatoAtual != NULL) {
		                cout << "Nome: " << candidatoAtual->nome << ", Numero: " << candidatoAtual->numero << endl;
		                candidatoAtual = candidatoAtual->prox;
		            }
		            cout << "Digite o numero do candidato: ";
		            cin >> voto;
		            Candidato* candidatoEscolhido = buscarCandidatoPorNumero(voto); // Função para buscar o candidato pelo número
		
		            if (candidatoEscolhido != NULL) {
		                Eleitor* eleitorAtual = listaEleitores;
		                while (eleitorAtual != NULL) {
		                    if (eleitorAtual->titulo == titulo) {
		                        eleitorAtual->voto = voto;
		                        break;
		                    }
		                    eleitorAtual = eleitorAtual->prox;
		                }
		                cout << "Voto registrado." << endl;
		            } else {
		                cout << "Numero de candidato invalido." << endl;
		            }
		        } else {
		            cout << "Eleitor nao incluido na fila de votacao." << endl;
		        }
		    } else {
		        cout << "Eleitor nao apto para votar." << endl;
		    }
		    	break;
			}

            case 11: {
               salvarVotos();
                break;
            }
           
            case 0: {
                cout << "Encerrando programa." << endl;
                break;
            }
            default: {
                cout << "Opcao invalida." << endl;
                break;
            }
        }

        cout << "----------------" << endl;
    } while (opcao != 0);

    return 0;
}

