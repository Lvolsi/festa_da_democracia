#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

struct Candidatos {
    int num_candidato;
    char nome[30];
};

struct no {
    Candidatos* info;
    struct no* prox = NULL;
};

typedef struct {
    no* inicio, * fim;
    int total;
} Lista;

void Create_Lista(Lista* L);
void Insert_Lista(Lista* L, Candidatos* X);
Candidatos* Remove_Lista(Lista* L, bool* erro);
bool IsEmpty_Lista(Lista* L);
void Print_Lista(Lista* L);

void Create_Lista(Lista* L) {
    L->inicio = NULL;
    L->fim = NULL;
    L->total = 0;
}

void Insert_Lista(Lista* L, Candidatos* X) {
    no* novo_no;
    novo_no = (no*)malloc(sizeof(no));

    if (novo_no == NULL) {
        cout << "Erro ao alocar memória." << endl;
        return;
    }

    novo_no->info = (Candidatos*)malloc(sizeof(Candidatos));

    if (novo_no->info == NULL) {
        cout << "Erro ao alocar memória." << endl;
        free(novo_no);
        return;
    }

    strcpy(novo_no->info->nome, X->nome);
    novo_no->info->num_candidato = X->num_candidato;

    novo_no->prox = NULL;

    if (L->inicio == NULL) {
        L->inicio = novo_no;
        L->fim = novo_no;
    } else {
        L->fim->prox = novo_no;
        L->fim = novo_no;
    }

    L->total++;
}




Candidatos* Remove_Lista(Lista* L, bool* erro) {
    if (IsEmpty_Lista(L)) {
        cout << "A lista está vazia." << endl;
        *erro = true;
        return NULL;
    }

    no* removido = L->inicio;
    Candidatos* valor = removido->info;

    L->inicio = L->inicio->prox;
    free(removido);

    L->total--;

    if (L->inicio == NULL) {
        L->fim = NULL;
    }

    *erro = false;
    return valor;
}

bool IsEmpty_Lista(Lista* L) {
    return L->inicio == NULL;
}

/*void Print_Lista(Lista* L) {
    no* aux = L->inicio;

    cout << "Elementos da Lista: ";
    while (aux != NULL) {
        cout << aux->info->num_candidato << " ";
        aux = aux->prox;
    }
    cout << endl;
}*/

void Print_Lista(Lista* L) {
    if (IsEmpty_Lista(L)) {
        cout << "Não há candidatos na lista." << endl;
    } else {
        no* atual = L->inicio;

        cout << "Lista de candidatos inscritos na eleição:" << endl;
        while (atual != NULL) {
            Candidatos* cand = atual->info;
            cout << "Nome do candidato: " << cand->nome << endl;
            cout << "Número do candidato: " << cand->num_candidato << endl;
            cout << "*-------------------------------------*" << endl;

            atual = atual->prox;
        }
    }
}



void Search_Lista(Lista* L, int x) {
    no* aux = L->inicio;

    while (aux != NULL) {
        if (aux->info->num_candidato == x) {
            cout << "Elemento " << x << " foi encontrado." << endl;
            return;
        }
        aux = aux->prox;
    }

    cout << "Elemento não encontrado." << endl;
}
