#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

struct Disciplina{
    string nome;
    string nomeProfessor;
    int cargaHoraria;
    float notas[3];
    float notaFinal;
    int codigo;
    Disciplina* proxima;
};

struct Aluno{
    string nome;
    int numeroMatricula;
    Disciplina* disciplinas;
    Aluno* proximo;
};

void menu();
void cadastrarAluno(Aluno*& alunos);
void cadastrarDisciplina(Disciplina*& disciplina);
void desalocarAlunos(Aluno*& alunos);
void desalocarDisciplinas(Disciplina*& disciplinas);
void registrarNotas(Aluno* alunos);
void matricularAluno(Aluno* alunos, Disciplina* disciplinas);
void gerarBoletim(Aluno* alunos);
void printAluno(Aluno* alunos);
void printDisciplinas(Disciplina* disciplinas);

int main(){
    system("cls");int op;
    Aluno* alunos = nullptr;
    Disciplina *disciplinas = nullptr;

    do{
        system("cls");
        cout << "======ALUNOS MATRICULADOS======" << endl;
        printAluno(alunos);
        cout << endl << endl;
        cout << "======DISCIPLINAS CADASTRADAS======" << endl;
        printDisciplinas(disciplinas);
        cout << "\n\n\n";
        menu();
        cout << "Informe uma opcao: ";
        cin >> op;
        switch (op)
        {
        case 1:
            cadastrarAluno(alunos);
            break;
        case 2:
            cadastrarDisciplina(disciplinas);
            break;
        case 3:
            matricularAluno(alunos,disciplinas);
            break;
        case 4:
            registrarNotas(alunos);
            break;
        case 5:
            gerarBoletim(alunos);
            system("pause");
            break;
        default:
            break;
        }
    }while(op != 0);
    desalocarAlunos(alunos);
    desalocarDisciplinas(disciplinas);
    system("cls");
}


void menu(){
    cout << "   SISTEMA ACADEMICO   " << endl;
    cout << "Digite 1 para cadastrar um aluno no sistema" << endl;
    cout << "Digite 2 para cadastrar uma disciplina no sistema" << endl;
    cout << "Digite 3 para matricular o aluno em uma disciplina" << endl;
    cout << "Digite 4 cadastrar as notas do aluno" << endl;
    cout << "Digite 5 para gerar o boletim de um aluno" << endl;
    cout << "Digite 0 para sair do programa" << endl;

}

void cadastrarAluno(Aluno*& alunos){
    string nomeAluno;
    int numeroMatricula;
    cout << "Informe o nome do aluno: ";
    cin.ignore();
    getline(cin,nomeAluno);
    cout << "Informe o numero de matricula do aluno: ";
    cin >> numeroMatricula;

    Aluno* novo = new Aluno;
    if(novo){
        novo->nome = nomeAluno;
        novo->numeroMatricula = numeroMatricula;
        novo->disciplinas = nullptr;
        if(alunos){
            novo->proximo = alunos;
            alunos = novo;
        }else{
            alunos = novo;
            novo->proximo = nullptr;
        }
    }else{
        cout << "Erro ao cadastrar aluno" << endl;
        delete novo;
        return;
    }
}

void cadastrarDisciplina(Disciplina*& disciplina){
    string nomeDisciplina,nomeProfessor;
    int codigoDisciplina,cargaHoraria;
    cout << "Informe o nome da disciplina: ";
    cin.ignore();
    getline(cin,nomeDisciplina);
    cout << "Informe o nome do professor: ";
    cin.ignore();
    getline(cin,nomeProfessor);
    cout << "Informee o codigo da disciplina: ";
    cin >> codigoDisciplina;
    cout << "Informe a carga horaria da disciplina em horas: ";
    cin >> cargaHoraria;


    Disciplina* nova = new Disciplina;
    if(nova){
        nova->nome = nomeDisciplina;
        nova->nomeProfessor = nomeProfessor;
        nova->codigo = codigoDisciplina;
        nova->cargaHoraria = cargaHoraria;
        if(disciplina){
            nova->proxima = disciplina;
            disciplina = nova;
        }else{
            disciplina = nova;
            nova->proxima = nullptr;
        }
    }else{
        cout << "Erro ao cadastrar Disciplina" << endl;
        delete nova;
        return;
    }
}

void registrarNotas(Aluno* alunos){
    string nomeAluno,nomeDisciplina;
    int codigoDisciplina;
    cout << "Informe o nome do aluno: ";
    cin.ignore();
    getline(cin,nomeAluno);
    cin.ignore();
    cout << "Informe o nome da disciplina em que serao cadastradas as notas: ";
    cin.ignore();
    getline(cin,nomeDisciplina);
    cout << "Agora informe o codigo da disciplina: ";
    cin >> codigoDisciplina;

    Aluno* alunoAux = alunos;
    while(alunoAux && alunoAux->nome.find(nomeAluno) == string::npos){
        alunoAux = alunoAux->proximo;
    }
    if(alunoAux == nullptr){
        cout << "Aluno: " << nomeAluno << " nao encontrado" << endl;
        return;
    }

    if(alunoAux->disciplinas){
        Disciplina* disciplinaAux = alunoAux->disciplinas;
        while(disciplinaAux && disciplinaAux->nome.find(nomeDisciplina) == string::npos && disciplinaAux->codigo != codigoDisciplina){
        disciplinaAux = disciplinaAux->proxima;
        }
        if(disciplinaAux == nullptr){
            cout << "Nome ou codigo da disciplina nao encontrados,insira outra disciplina e tente novamente" << endl;
            return;
        }
        float soma = 0;
        for(int i = 0; i < 3; i++){
            cout << "Informe a nota " << i+1 << " do aluno: ";
            cin >> disciplinaAux->notas[i];
            if(disciplinaAux->notas[i] > 10 || disciplinaAux->notas[i] < 0){
                cout << "Nota invalida" << endl;
            }else{
                soma += disciplinaAux->notas[i];
            }    
        }
        disciplinaAux->notaFinal = soma/3;
        system("cls");
    }else{
        cout << "Nenhuma disciplina cadastrada,por favor cadastre disciplinas no sistema para matricular alunos" << endl;
        return;
    }
}


void matricularAluno(Aluno* alunos,Disciplina* disciplinas){

    if(alunos == nullptr || disciplinas == nullptr){
        cout << "Erro Alunos ou disciplinas nao cadastradas" << endl;
        return;
    }
    string nomeAluno,nomeDisciplina;
    int numeroMatricula;
    cout << "Informe o seu nome: ";
    cin.ignore();
    getline(cin,nomeAluno);
    cout << "Informe o seu numero de matricula: ";
    cin >> numeroMatricula;
    cout << "Informe o nome da disciplina de interesse: ";
    cin.ignore();
    getline(cin,nomeDisciplina);

    Aluno* alunoAux = alunos;
    Disciplina* disciplinaAux = disciplinas;

    while(alunoAux && alunoAux->nome.find(nomeAluno) == string::npos){
        alunoAux = alunoAux->proximo;
    }
    if(alunoAux == nullptr){
        cout << "Aluno: " << nomeAluno << " nao encontrado" << endl;
        return;
    }

    while(disciplinaAux && disciplinaAux->nome.find(nomeDisciplina) == string::npos){
        disciplinaAux = disciplinaAux->proxima;
    }
    if(disciplinaAux == nullptr){
        cout << "Disciplina: " << nomeDisciplina << " nao encontrada" << endl;
        return;
    }

    Disciplina* nova = new Disciplina;
    if(nova){
        nova->nome = disciplinaAux->nome;
        nova->nomeProfessor = disciplinaAux->nomeProfessor;
        nova->codigo = disciplinaAux->codigo;
        nova->cargaHoraria = disciplinaAux->cargaHoraria;
        if(alunoAux->disciplinas){
            nova->proxima = alunoAux->disciplinas;
            alunoAux->disciplinas = nova;
        }else{
            alunoAux->disciplinas = nova;
            nova->proxima = nullptr;
        }
    }else{
        cout << "Erro ao matricular aluno" << endl;
        delete nova;
        return;
    }

}

void gerarBoletim(Aluno* alunos){
    string nomeAluno;
    int numeroMatricula;
    cout << "Informe o nome do aluno: ";
    cin.ignore();
    getline(cin,nomeAluno);
    cout << "Informe o numero da matricula: ";
    cin >> numeroMatricula;

    Aluno* alunoAux = alunos;
    while(alunoAux && alunoAux->nome.find(nomeAluno) == string::npos && alunoAux->numeroMatricula != numeroMatricula){
        alunoAux = alunoAux->proximo;
    }
    if(alunoAux == nullptr){
        cout << "Aluno: " << nomeAluno << " nao foi encontrado";
        return;
    }

    cout << "======BOLETIM BIMESTRAL======" << endl;
    cout << "Nome do aluno: " << alunoAux->nome << endl;
    cout << "Numero da matricula: " << alunoAux->numeroMatricula << endl;
    Disciplina* disciplinaAux = alunoAux->disciplinas;
    while(disciplinaAux){
        cout << "Disciplina: " << disciplinaAux->nome << endl;
        for(int i = 0; i < 3; i++){
            cout << "Nota " << i+1 << ": " << disciplinaAux->notas[i] << endl;
        }
        cout << "Nota final: " << disciplinaAux->notaFinal << endl << endl;
        disciplinaAux = disciplinaAux->proxima;
    }
}

void printAluno(Aluno* alunos) {
    Aluno* aux = alunos;
    while (aux) {
        cout << "|Nome: " << aux->nome << "|";
        cout << "|Numero da matricula: " << aux->numeroMatricula << "|";

        if (aux->disciplinas) {
            Disciplina* disciplinaaux = aux->disciplinas;
            cout << "   Disciplinas: ";
            while (disciplinaaux) {
                cout << "|" << disciplinaaux->nome << "|";
                disciplinaaux = disciplinaaux->proxima;
            }
            cout << endl;
        }
        else {
            cout << "   Nenhuma disciplina matriculada" << endl;
        }

        aux = aux->proximo;
    }
}

void printDisciplinas(Disciplina* disciplina){
    Disciplina* aux = disciplina;
    while(aux){
        cout << "|Nome da disciplina: " << aux->nome << "|";
        cout << "|Professor: " << aux->nomeProfessor << "|";
        cout << "|codigo da disciplina " << aux->codigo << "|";
        cout << "|Carga horaria da disciplina " << aux->cargaHoraria << "h|" << endl;
        aux = aux->proxima;
    }
}

void desalocarAlunos(Aluno*& alunos){
   if(alunos){
     while(alunos){
        Aluno* alunoTemp = alunos;
        alunos = alunos->proximo;

        while(alunoTemp->disciplinas){
            Disciplina* disciplinaTemp = alunoTemp->disciplinas;
            alunoTemp->disciplinas = alunoTemp->disciplinas->proxima;
            delete disciplinaTemp;
        }
        delete alunoTemp;
    }
   }else{
    cout << "Erro ao desalocar, a lista de alunos esta vazia" << endl;
    return;
   }
}

void desalocarDisciplinas(Disciplina*& disciplinas){
    if(disciplinas){
        while(disciplinas){
        Disciplina* temp = disciplinas;
        disciplinas = disciplinas->proxima;
        delete temp;
        }
    }else{
        cout << "Erro ao desalocar,lsta de disciplinas vazia" << endl;
        return;
    }
}