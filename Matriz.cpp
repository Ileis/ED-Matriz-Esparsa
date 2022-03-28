#include "Matriz.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

//------------------------------------------------------------------------------------
// UFC - Campus Quixadá
// AP 02 - Projeto de Implementação - Matrizes Esparsas.
// Aluno: Gabriel Ileis Araújo Vieira
// Matrícula: 493973
//------------------------------------------------------------------------------------

Matriz::Node::Node(Node *direita = nullptr, Node *abaixo = nullptr, double valor = 0, int linha = -1, int coluna = -1){
    this->direita = direita;
    this->abaixo = abaixo;
    this->linha = linha;
    this->coluna = coluna;
    this->valor = valor;
}

//*********************************** ITERATOR ***************************************

// o iterator apresenta um movimento limitado, só conseguindo andar reto enquanto
// estiver dentro da matriz. O objetivo do iterator é conseguir percorrer uma
// linha ou coluna por inteiro, sem desviar de seu caminho. A implementação do
// iterador foi pensada com o objetivo de desenvolver uma interface para o usuario
// da classe, escondendo os detalhes de implementação e possibilitando que este
// percorra pela matriz. Funções como soma e multiplica não devem ter acesso aos
// ponteiros e endereços da classe Matriz mas ao mesmo tempo precisam ter acesso
// aos valores da matriz. O iterator faz o trabalho de percorrer a matriz e retornar
// os valores, mesmo que o nó não tenha sido alocado.
//      FUNCIONAMENTO DO ITERATOR:
// O iterator é composto por um ponteiro para nó, 2 variaveis que representam
// sua falsa coordenada e um enum que guarda seu ultimo movimento. O iterator 
// só vai para frente ou para baixo caso o seu movimento dentro da matriz seja
// preservado e caso a sua "coordenada relativa" seja igual a coordenada real do
// próximo nó. Enquanto a sua "coordenada relativa" for diferente de sua coordenada real
// ele retornará 0, caso sua coordenada seja igual a cordenada do nó apontado ele retornará
// o seu real valor. Quanto o iterator chega em um nó cabeça todas as suas coordenadas
// são zeradas e o seu movimento se faz livre, uma vez que é garantido que todos os nós
// cabeças existem. Também é possivel mover o iterator para valores diferentes de 0,
// simplesmente avançando na lista.

// Variavel responsavel por armazenar o ultimo movimento do iterator.
void Matriz::Iterator::setLastMov(lastMoviment mov){
    lastMov = mov;
}

void Matriz::begin(){
    iterator.it = matriz;
    iterator.itColuna = 0;
    iterator.itLinha = 0;
}

void Matriz::next(){

    if((iterator.itColuna > 0 && iterator.itLinha > 0) && iterator.lastMov == iterator.DOWN){
        ArgumentoInvalidoMatriz e;
        e.illegalMovement();
        throw e;
    }

    iterator.itColuna++;

    iterator.setLastMov(iterator.NEXT);

    if(inHeadNode(iterator.it->direita)){
        if(inHeadNode(iterator.it)){
            iterator.it = iterator.it->direita;
            
        }else if(iterator.itColuna > getColunas())
            iterator.it = iterator.it->direita;

    }else{
        if(iterator.itColuna == iterator.it->direita->coluna)
            iterator.it = iterator.it->direita;
    }
    if(iterator.itColuna > getColunas())
        iterator.itColuna = 0;
}

// ARRUMAR: Coordenadas de nextNotZero

void Matriz::nextNotZero(){
    iterator.setLastMov(iterator.NEXT);

    iterator.it = iterator.it->direita;
    iterator.itColuna = iterator.it->coluna;
}

void Matriz::down(){

    if((iterator.itColuna > 0 && iterator.itLinha > 0) && iterator.lastMov == iterator.NEXT){
        ArgumentoInvalidoMatriz e;
        e.illegalMovement();
        throw e;
    }

    iterator.itLinha++;

    iterator.setLastMov(iterator.DOWN);

    if(inHeadNode(iterator.it->abaixo)){
        if(inHeadNode(iterator.it)){
            iterator.it = iterator.it->abaixo;

        }else if(iterator.itLinha > getLinhas())
            iterator.it = iterator.it->abaixo;

    }else{
        if(iterator.itLinha == iterator.it->abaixo->linha)
            iterator.it = iterator.it->abaixo;
    }
    if(iterator.itLinha > getLinhas())
        iterator.itLinha = 0;
}

// ARRUMAR: Coordenadas de downNotZero

void Matriz::downNotZero(){
    iterator.setLastMov(iterator.DOWN);

    iterator.it = iterator.it->abaixo;
    iterator.itLinha = iterator.it->linha;
}

double Matriz::getKey(){
    if(iterator.it->valor == 0 && getIteratorColumn() == 0 || getIteratorLine() == 0){
        ArgumentoInvalidoMatriz e;
        e.notPossibleReturnHeadnode();
        throw e;
    }

    if(iterator.itColuna == iterator.it->coluna && iterator.itLinha == iterator.it->linha)
        return iterator.it->valor;
    else
        return 0;
}

void Matriz::printNode(){
    try{
        std::cout << getKey();
    }catch(ArgumentoInvalidoMatriz &e){
        std::cout << e.what();
    }
    std::cout << " (" << iterator.itLinha << ", " << iterator.itColuna << ")" << std::endl;
}

bool Matriz::inHeadNode(){
    return inHeadNode(iterator.it);
}

bool Matriz::inMainHeadNode(){
    return inMainHeadNode(iterator.it);
}

int Matriz::getIteratorColumn(){
    if(iterator.itColuna < 0)
        return 0;
    else
        return iterator.itColuna;
}

int Matriz::getIteratorLine(){
    if(iterator.itLinha < 0)
        return 0;
    else
        return iterator.itLinha;
}

// Os unicos nós alocados que apresentam o valor zero são os nós cabeças.
bool Matriz::inHeadNode(Node *pos){
    return pos->valor == 0;
}

bool Matriz::inMainHeadNode(Node *pos){
    return pos == matriz;
}

//------------------------------------------------------------------------------------

Matriz::Matriz(int m, int n){

    // - Valores inválidos:
    //      - valores menores ou iguais a 0.

    if(m <= 0 || n <= 0){
        ArgumentoInvalidoMatriz e;
        e.notPositiveNumber();
        throw e;
    }

    this->numLinhas = m;
    this->numColunas = n;
    this->matriz = new Node;
    this->iterator.it = matriz;

    // Contando com os nós cabeças, a matriz construída precisa ter uma estrutura de
    // (m + 1) x (n + 1), onde o ponteiro matriz servirá como uma especie de ponteiro
    // pivô para o calculo da posição, pois apontará para o nó cabeça superior 
    // esquerdo.

    Node *aux;
    aux = matriz;

    // O nó pivô já existe, então são adicionados m elementos à direita e n elementos
    // abaixo dele, formando a estrutura (m + 1) x (n + 1) dos nós cabeças.

    // Criando nó cabeça superior
    for(int i = 0; i < getColunas(); i++){
        aux->direita = new Node;
        aux = aux->direita;
        aux->abaixo = aux;
    }
    aux->direita = matriz;
    aux = matriz;

    // Criando nó cabeça lateral
    for(int i = 0; i < getLinhas(); i++){
        aux->abaixo = new Node;
        aux = aux->abaixo;
        aux->direita = aux;
    }
    aux->abaixo = matriz;
    aux = matriz;
}

Matriz::~Matriz(){

    // A destruição é feita linha por linha, começando pela primeira.
    Node *auxLinhaDestruida = matriz;
    Node *auxDestroiNo = nullptr;

    for(int i = 0; i <= getLinhas(); i++){
        // Destrói uma linha inteira até que o nó cabeça aponte para ele mesmo
        while(auxLinhaDestruida->direita != auxLinhaDestruida){
            auxDestroiNo = auxLinhaDestruida->direita;
            auxLinhaDestruida->direita = auxDestroiNo->direita;
            delete auxDestroiNo;

            auxDestroiNo = nullptr;
        }

        // Destrói o nó cabeça e avança para a próxima linha
        auxDestroiNo = auxLinhaDestruida;
        auxLinhaDestruida = auxDestroiNo->abaixo;
        delete auxDestroiNo;

        auxDestroiNo = nullptr;
    }
    matriz = nullptr;
}

int Matriz::getLinhas(){
    return this->numLinhas;
}

int Matriz::getColunas(){
    return this->numColunas;
}

void Matriz::insert(int i, int j, double value){

    // - Valores inválidos:
    //      - valores menores ou iguais a 0;
    //      - valores maiores que as dimensões da matriz;
    //      - posições ocupadas.

    if(i <= 0 || i > getLinhas()){
        ArgumentoInvalidoMatriz e;
        e.invalidPosition();
        throw e;
    }

    if(j <= 0 || j > getColunas()){
        ArgumentoInvalidoMatriz e;
        e.invalidPosition();
        throw e;
    }

    if(value != 0){

        Matriz::Node *nodeSuperior = aboveNode(i, j);
        Matriz::Node *nodeEsquerdo = leftNode(i, j);

        if(nodeSuperior->abaixo->linha == i && nodeSuperior->abaixo->coluna == j){
            ArgumentoInvalidoMatriz e;
            e.occupedPosition();
            throw e;
        }

        // Para inserir um nó se faz necessário o ajuste das listas, o novo nó precisa
        // apontar para o elemento a direita e abaixo de sua posição, assim como o
        // elemento acima e a esquerda também precisam apontar para ele.

        Matriz::Node *nodeNovo = new Matriz::Node(nodeEsquerdo->direita, nodeSuperior->abaixo, value, i, j);

        nodeEsquerdo->direita = nodeNovo;
        nodeSuperior->abaixo = nodeNovo;
    }
}

double Matriz::getValue(int i, int j){

    // - Valores inválidos:
    //      - valores menores ou iguais a 0.
    //      - valores maiores que as dimensões da matriz.

    if(i <= 0 || i > getLinhas()){
        ArgumentoInvalidoMatriz e;
        e.invalidPosition();
        throw e;
    }
    
    if(j <= 0 || j > getColunas()){
        ArgumentoInvalidoMatriz e;
        e.invalidPosition();
        throw e;
    }

    Matriz::Node *returnableNode = aboveNode(i, j);
    returnableNode = returnableNode->abaixo;

    if(returnableNode->linha == i && returnableNode->coluna == j)
        return returnableNode->valor;
    else
        return 0;
}

void Matriz::print(){

    Matriz::Node *lineHead = matriz->abaixo;
    Matriz::Node *printNode = lineHead->direita;

    while(lineHead != matriz){
        for(int coluna = 1; coluna <= getColunas(); coluna++){
            if(printNode->coluna == coluna){
                std::cout << std::setw(10) << printNode->valor << '\t';
                printNode = printNode->direita;
            }else
                std::cout << std::setw(10) << 0 << '\t';
        }

        std::cout << std::endl;
        std::cout << std::endl;

        lineHead = lineHead->abaixo;
        printNode = lineHead->direita;
    }
}

Matriz::Node *Matriz::aboveNode(int i, int j){
    Matriz::Node *nodePosition = this->matriz;

    for(int coluna = 0; coluna < j; coluna++)
        nodePosition = nodePosition->direita;

    while(nodePosition->abaixo->linha < i && nodePosition->abaixo->linha != -1)
        nodePosition = nodePosition->abaixo;

        return nodePosition;
}

Matriz::Node *Matriz::leftNode(int i, int j){
    Matriz::Node *nodePosition = this->matriz;

    for(int linha = 0; linha < i; linha++)
        nodePosition = nodePosition->abaixo;

    while(nodePosition->direita->coluna < j && nodePosition->direita->coluna != -1)
        nodePosition = nodePosition->direita;

    return nodePosition;
}

Matriz *soma(Matriz *A, Matriz *B){

    if(A->getColunas() != B->getColunas() && A->getLinhas() != B->getLinhas()){
        ArgumentoInvalidoMatriz e;
        e.notSameOrder();
        throw e;
    }

    Matriz *aPlusB = new Matriz(A->getLinhas(), A->getColunas());

    // Posicionando os iteradores no nó cabeça principal da matriz.
    A->begin();
    B->begin();

    // Posicionando os iteradores no nó cabeça da primeira linha.
    A->down();
    B->down();

    while(!A->inMainHeadNode() || !B->inMainHeadNode()){
        A->nextNotZero();
        B->nextNotZero();

        while(!A->inHeadNode() || !B->inHeadNode()){
            if(!A->inHeadNode() && !B->inHeadNode()){

                if(A->getIteratorColumn() < B->getIteratorColumn()){
                    aPlusB->insert(A->getIteratorLine(), A->getIteratorColumn(), A->getKey());
                    A->nextNotZero();

                }else if(A->getIteratorColumn() > B->getIteratorColumn()){
                    aPlusB->insert(B->getIteratorLine(), B->getIteratorColumn(), B->getKey());
                    B->nextNotZero();
                }else{
                    aPlusB->insert(A->getIteratorLine(), A->getIteratorColumn(), A->getKey() + B->getKey());
                    A->nextNotZero();
                    B->nextNotZero();
                }

            }else if(!A->inHeadNode()){
                aPlusB->insert(A->getIteratorLine(), A->getIteratorColumn(), A->getKey());
                A->nextNotZero();

            }else if(!B->inHeadNode()){
                aPlusB->insert(B->getIteratorLine(), B->getIteratorColumn(), B->getKey());
                B->nextNotZero();
            }
        }
        A->down();
        B->down();
    }

    return aPlusB;
}

Matriz *multiplica(Matriz *A, Matriz *B){
    
    if(A->getColunas() != B->getLinhas()){
        ArgumentoInvalidoMatriz e;
        e.notPossibleMult();
        throw e;
    }

    Matriz *aMultB = new Matriz(A->getLinhas(), B->getColunas());
    double posKey;

    A->begin();
    B->begin();

    A->down();
    B->next();

    while(!A->inMainHeadNode()){

        while(!B->inMainHeadNode()){
        posKey = 0;

        A->nextNotZero();
        B->downNotZero();

        int linha = A->getIteratorLine();
        int coluna = B->getIteratorColumn();

            while(!B->inHeadNode() || !A->inHeadNode()){
                if(!A->inHeadNode() && !B->inHeadNode()){

                    if(A->getIteratorColumn() < B->getIteratorLine()){
                        A->nextNotZero();

                    }else if(A->getIteratorColumn() > B->getIteratorLine()){
                        B->downNotZero();
                    }else{
                        posKey += A->getKey() * B->getKey();

                        A->nextNotZero();
                        B->downNotZero();
                    }
                }else if(A->inHeadNode()){
                    while(!B->inHeadNode())
                        B->downNotZero();

                }else if(B->inHeadNode()){
                    while(!A->inHeadNode())
                        A->nextNotZero();
                }
            }
            aMultB->insert(linha, coluna, posKey);

            B->next();
        }
        B->next();
        A->down();
    }

    A->begin();
    B->begin();

    return aMultB;
}

Matriz *lerMatrizDeArquivo(std::string nome_do_arquivo){

    std::ifstream inFile(nome_do_arquivo);

    if(!inFile){
        ArgumentoInvalidoMatriz e;
        e.notPossibleOpenFile();
        throw e;
    }

    int linha, coluna;
    double value;

    inFile >> linha >> coluna;

    try{
        Matriz *matrizLida = new Matriz(linha, coluna);

        while(inFile >> linha >> coluna >> value){
            try{
                matrizLida->insert(linha, coluna, value);
            }catch(ArgumentoInvalidoMatriz &e){
                std::cout << e.what() << std::endl;
            }
        }

        return matrizLida;

    }catch(ArgumentoInvalidoMatriz &e){
        throw e;
    }
}

ArgumentoInvalidoMatriz::ArgumentoInvalidoMatriz(){
    this->mensagem.clear();
}

std::string ArgumentoInvalidoMatriz::what(){
    return "Erro: " +  mensagem;
}

void ArgumentoInvalidoMatriz::emptyVectorMatriz(){
    this->mensagem = "Não há matrizes.";
}

void ArgumentoInvalidoMatriz::illegalMovement(){
    this->mensagem = "Movimento ilegal.";
}

void ArgumentoInvalidoMatriz::invalidPosition(){
    this->mensagem = "posição inválida.";
}

void ArgumentoInvalidoMatriz::notPositiveNumber(){
    this->mensagem = "O número é não positivo.";
}

void ArgumentoInvalidoMatriz::notPossibleMult(){
    this->mensagem = "Não é possivel multiplicar as matrizes.";
}

void ArgumentoInvalidoMatriz::notPossibleOpenFile(){
    this->mensagem = "Não foi possível abrir o arquivo.";
}

void ArgumentoInvalidoMatriz::notPossibleReturnHeadnode(){
    this->mensagem = "Não é possivel retornar o valor do nó cabeça.";
}

void ArgumentoInvalidoMatriz::notSameOrder(){
    this->mensagem = "As matrizes não são da mesma ordem.";
}

void ArgumentoInvalidoMatriz::occupedPosition(){
    this->mensagem = "posição ocupada.";
}