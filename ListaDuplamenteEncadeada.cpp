#include <iostream>
using namespace std;

struct No{
    int valor;
    No* next;
};

void appendList(No*& cabeca,int num){
    No* novo = new No{num,nullptr};
    if(cabeca == nullptr){
        cabeca = novo;
    }else{
        No* aux = cabeca;
        while(aux->next){
            aux = aux->next;
        }
        aux->next = novo;
    }
}

void removeList(No*& cabeca,int numero){
    No* aux = cabeca,*remove = nullptr;
    if(cabeca){
        if(aux->valor == numero){
            remove = aux;
            cabeca = remove->next;
            delete remove;
        }else{
            while(aux->next && aux->next->valor != numero){
                aux = aux->next;
            }
            if(aux->next){
                remove = aux->next;
                aux->next = remove->next;
                delete remove;
            }else{
                cout << "O elemento nao foi encontrado na lista" << endl;
                return;
            }
        }
    }else{
        cout << "A lista esta vazia, adicione elementos para poder remove-los" << endl;
        return;
    }
}

void concatList(No*& lista1,No*& lista2,No*& lista3){
    No* aux1 = lista1;
    No* aux2 = lista2;
    while(aux1){
        appendList(lista3,aux1->valor);
        aux1 = aux1->next;
    }
    

}

void deleteList(No*& cabeca){
    while(cabeca){
        No* aux = cabeca;
        cabeca = aux->next;
        delete aux;
    }
}


void printList(const No* cabeca){
    const No* aux = cabeca;
    while(aux){
        cout << aux->valor << " ";
        aux = aux->next;
    }
}

int main(){
    No* myList = nullptr;
    appendList(myList,17);
    appendList(myList,18);
    printList(myList);

    deleteList(myList);
    if(myList == nullptr){
        cout << endl << "Lista desalocada com sucesso" << endl;
    }else{
        cout << "Erro ao desalocar Lista" << endl;
    }
}