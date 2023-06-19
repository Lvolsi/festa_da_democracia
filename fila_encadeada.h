#include <iostream>
#include <cstdlib>
using namespace std;

typedef int elem;

typedef struct bloco{
        elem info;
        struct bloco *prox = NULL;
}no;

typedef struct {
        no *inicio, *fim;
        int total;
} Fila;

void Create_Queue(Fila *F);
void Enter_Queue(Fila *F, elem* X, bool *erro);
elem Out_Queue(Fila *F, bool *erro);
bool IsEmpty_Queue(Fila *F);
void Print_Queue(Fila *F);

void Create_Queue(Fila *F) {
    F->inicio=NULL;
    F->fim=NULL;
    F->total=0;
}



void Enter_Queue(Fila *F, elem *X, bool *erro) 
{
    no *novo_no;
    novo_no=(no*)malloc(sizeof(no));
    /* se eu não conseguir criar o p é porque a memória está com espaço cheio, 
	por isso não precisa da função IsFull
	*/
    if (novo_no==NULL)
        *erro=true;
    else{
    	*erro=false;
    	novo_no->info = *X;
    	novo_no->prox = NULL;
    	if (F->inicio==NULL) // se for o primeiro a entrar na fila
		{
    		F->inicio = novo_no;
    		F->fim = novo_no;
    		novo_no->prox = NULL;
    		F->total++;
    	}
    	else
		{// se já tiver alguem na fila
			F->fim->prox = novo_no;
			F->fim = novo_no;
			novo_no->prox = NULL;
			F->total++;
		} 
	}
}

elem X;
elem Out_Queue(Fila *F, bool *erro) 
{
    if (!IsEmpty_Queue(F))
	{
    	*erro=false;	
		X = F->inicio->info;
		if (F->inicio == F->fim)
		{// se tiver somente 1 na fila
			F->inicio=NULL;
			F->fim=NULL;
			F->total--;
			return X;
		}
		else{ // retira o primeiro bloco da fila
			F->inicio = F->inicio->prox;
			F->total--;			   
			return X;
		}
	*erro=true;
	}
}
      
      
bool IsEmpty_Queue(Fila *F) 
{
    if (F->inicio==NULL)
       return true;
    else 
		return false;
}

void Print_Queue(Fila *F)
{
	no *aux;
	aux = F->inicio;
	int total = F->total;
	cout << "Elementos da Fila (do inicio ao fim): ";
	while(total>0)
	{
		cout << aux->info;
		aux = aux->prox;
		cout << " ";
		total--;
	}
	
}


void Search_Queue(Fila *F, elem x) 
{
    no *aux;
    int total = F->total;
    aux=F->inicio;
    while (total>0){
		if(aux->info==x)
			cout << "Elemento: " << aux->info << " foi encontrado." << endl;
		aux=aux->prox;
		total--;
    }
	
	if(total==0)
		cout << "Elemento não encontrado" << endl;
}
