#include <iostream>
#include <string>
#include <vector>
#include "Matriz.h"

using namespace std;

void menuPrint(){
    
    cout << "--------------------------------MENU--------------------------------" << endl;
    cout << "i: linha, j: coluna, M e N: matriz" << endl;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "******************************ITERATOR******************************" << endl;
    cout << "direita: next M" << "\t\t\t" << "abaixo:  down M" << endl;
    cout << "getKey:  get M" << "\t\t\t" << "begin:   begin M" << endl;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "*******************************MATRIZ*******************************" << endl;
    cout << "criar:   new i, j" << "\t\t" << "print:   print M" << endl;
    cout << "insert:  ins i, j, value, M" << "\t" << "getPos:  pos i, j, M" << endl;
    cout << "somar:   sum M, N" << "\t\t" << "mult:    mult M, N" << endl; 
    cout << "pop:     pop" << "\t\t\t" << "ler:     ler nome_do_arquivo.txt" << endl;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "menu:    menu" << "\t\t\t" << "sair:    sair" << endl;
    cout << "clear:   clear" << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

void criarMatriz(vector<Matriz*> &matrizes); void next(vector<Matriz*> &matrizes); void down(vector<Matriz*> &matrizes); void get(vector<Matriz*> &matrizes);
void begin(vector<Matriz*> &matrizes); void print(vector<Matriz*> &matrizes); void insert(vector<Matriz*> &matrizes); void pos(vector<Matriz*> &matrizes);
void soma(vector<Matriz*> &matrizes); void multiplica(vector<Matriz*> &matrizes); void pop(vector<Matriz*> &matrizes); void ler(vector<Matriz*> &matrizes);
void sair(vector<Matriz*> &matrizes, bool &control);

int main(){

    string option;
    vector<Matriz*> matrizes;
    bool control = true;

    menuPrint();

    while(control){

        cin >> option;

        if(!option.compare("next"))
            try{
                next(matrizes);
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("down"))
            try{
                down(matrizes);
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("get"))
            try{
                get(matrizes);
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("begin"))
            try{
                begin(matrizes);
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("new"))
            criarMatriz(matrizes);

        else if(!option.compare("print"))
            try{
                print(matrizes);
                cout << endl;
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("ins"))
        try{
            insert(matrizes);
        }catch(ArgumentoInvalidoMatriz &e){
            cout << e.what() << endl;
        }

        else if(!option.compare("pos"))
            try{
                pos(matrizes);
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("sum"))
            try{
                soma(matrizes);
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("mult"))
            try{
                multiplica(matrizes);
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("pop"))
            try{
                pop(matrizes);
            }catch(ArgumentoInvalidoMatriz &e){
                cout << e.what() << endl;
            }

        else if(!option.compare("ler"))
            ler(matrizes);

        else if(!option.compare("menu"))
            menuPrint();

        else if(!option.compare("sair"))
            sair(matrizes, control);

        else if(!option.compare("clear"))
            system("clear");

        else{
            cout << "Comando inexistente." << endl;
            cin.clear();
        }
        option.clear();
    }
}

void criarMatriz(vector<Matriz*> &matrizes){

    int m, n;
    cin >> m >> n;

    try{
        Matriz *mat = new Matriz(m, n);
        matrizes.push_back(mat);

        cout << "Matriz resultante " << matrizes.size() - 1 << " foi criada." << endl;

    }catch(ArgumentoInvalidoMatriz &e){
        cout << e.what() << endl;
    }
}

void next(vector<Matriz*> &matrizes){

    int M;
    cin >> M;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size()){
        try{
            matrizes[M]->next();
        }catch(ArgumentoInvalidoMatriz &e){
            cout << e.what() << endl;
        }
    }else
        cout << "Matriz inexistente." << endl;
}

void down(vector<Matriz*> &matrizes){

    int M;
    cin >> M;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size()){
        try{
            matrizes[M]->down();
        }catch(ArgumentoInvalidoMatriz &e){
            cout << e.what() << endl;
        }
    }else
        cout << "Matriz inexistente." << endl;
}

void get(vector<Matriz*> &matrizes){

    int M;
    cin >> M;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size()){
        matrizes[M]->printNode();
    }else
        cout << "Matriz inexistente." << endl;
}

void begin(vector<Matriz*> &matrizes){
    
    int M;
    cin >> M;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size()){
        matrizes[M]->begin();
    }else
        cout << "Matriz inexistente." << endl;
}

void print(vector<Matriz*> &matrizes){

    int M;
    cin >> M;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size()){
        matrizes[M]->print();
    }else
        cout << "Matriz inexistente." << endl;
}

void insert(vector<Matriz*> &matrizes){

    int i, j, M;
    double value;
    cin >> i >> j >> value >> M;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size()){
        try{
            matrizes[M]->insert(i, j, value);
        }catch(ArgumentoInvalidoMatriz &e){
            cout << e.what() << endl;
        }
    }else
        cout << "Matriz inexistente." << endl;
}

void pos(vector<Matriz*> &matrizes){

    int i, j, M;
    cin >> i >> j >> M;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size()){
        try{
            cout << matrizes[M]->getValue(i, j) << endl;
        }catch(ArgumentoInvalidoMatriz &e){
            cout << e.what() << endl;
        }
    }else
        cout << "Matriz inexistente." << endl;
}

void soma(vector<Matriz*> &matrizes){

    int M, N;
    cin >> M >> N;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size() && N < matrizes.size()){
        try{
            Matriz *sum = soma(matrizes[M], matrizes[N]);
            matrizes.push_back(sum);
            cout << "Matriz resultante " << matrizes.size() - 1 << " foi criada." << endl;

        }catch(ArgumentoInvalidoMatriz &e){
            cout << e.what() << endl;
        }
    }else
        cout << "Matriz inexistente." << endl;
}

void multiplica(vector<Matriz*> &matrizes){

    int M, N;
    cin >> M >> N;

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;
    }

    if(M < matrizes.size() && N < matrizes.size()){
        try{
            Matriz *mult = multiplica(matrizes[M], matrizes[N]);
            matrizes.push_back(mult);
            cout << "Matriz resultante " << matrizes.size() - 1 << " foi criada." << endl;

        }catch(ArgumentoInvalidoMatriz &e){
            cout << e.what() << endl;
        }
    }else
        cout << "Matriz inexistente." << endl;
}

void pop(vector<Matriz*> &matrizes){

    if(matrizes.empty()){
        ArgumentoInvalidoMatriz e;
        e.emptyVectorMatriz();
        throw e;

    }else{
        delete matrizes.back();
        cout << "Matriz " << matrizes.size() - 1 << " deletada." << endl;
        matrizes.pop_back();
    }
}

void ler(vector<Matriz*> &matrizes){

    string nomeDoArquivo;
    cin >> nomeDoArquivo;

    try{
        Matriz* matrizLida = lerMatrizDeArquivo(nomeDoArquivo);
        matrizes.push_back(matrizLida);
        cout << "Matriz resultante " << matrizes.size() - 1 << " foi criada." << endl;

    }catch(ArgumentoInvalidoMatriz &e){
        cout << e.what() << endl;
    }
}

void sair(vector<Matriz*> &matrizes, bool &control){
    for(int i = 0; i < matrizes.size(); i++){
        delete matrizes[i];
    }
        matrizes.clear();
        control = false;
        cout << "Programa encerrado." << endl;
}