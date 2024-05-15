#include <iostream>
using namespace std;

struct Aluno{
    string nome;
    string disciplina;
    float nota;
    Aluno* proximo;
};

void inserirLista(Aluno*& cabeca,string nome,string disciplina,float nota){
    Aluno* novo = new Aluno{nome,disciplina,nota,nullptr};
    if(cabeca == nullptr){
        cabeca = novo;
    }else{
        Aluno* temp = cabeca;
        while(temp->proximo != nullptr){
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }
}

void exibirLista(const Aluno* cabeca){
    const Aluno* temp = cabeca;
    while(temp != nullptr){
        cout << temp->nome << endl;
        cout << temp->disciplina << endl;
        cout << temp->nota << endl << endl;
        temp = temp->proximo;
    }
}

void desalocarLista(Aluno*& cabeca){
    while(cabeca != nullptr){
        Aluno* proximo = cabeca->proximo;
        delete cabeca;
        cabeca = proximo;
    }
}

void removerLista(Aluno*& cabeca,string nome){
    Aluno* aux = cabeca;
    Aluno* aRemover = nullptr;
    if(aux->nome == nome){
        aRemover = cabeca;
        cabeca = aRemover->proximo;
    }else{
        while(aux->proximo && aux->proximo->nome != nome){
            aux = aux->proximo;
        }
        if(aux->proximo){
            aRemover = aux->proximo;
            aux->proximo = aRemover->proximo;
            delete aRemover;
        }else{
            cout << "Aluno nao encontrado" << endl;
            return;
        }
    }
}

int main(){
    Aluno* minhaLista = nullptr;
    inserirLista(minhaLista,"Natan","calculo",7.5);
    inserirLista(minhaLista,"Fernando","LP1",9.6);
    inserirLista(minhaLista,"Lucas","Banco de dados",7.9);
    exibirLista(minhaLista);

    removerLista(minhaLista,"Natan");
    exibirLista(minhaLista);

    desalocarLista(minhaLista);
}