#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>
#include <string>

class Matriz{

    private:

    struct Node{
        Node *direita;
        Node *abaixo;
        int linha;
        int coluna;
        double valor;

        Node(Node *direita, Node *abaixo, double valor, int linha, int coluna);
    };

//------------------------------------------------------------------------------------

//*********************************** ITERATOR ***************************************

    // o iterator apresenta um movimento limitado, só conseguindo andar reto enquanto
    // estiver dentro da matriz. O objetivo do iterator é conseguir percorrer uma
    // linha ou coluna por inteiro, sem desviar de seu caminho.

    struct Iterator{

        enum lastMoviment{
            NEXT, DOWN
        };

        Matriz::Node *it = nullptr;
        int itColuna = 0;
        int itLinha = 0;
        lastMoviment lastMov;


        void setLastMov(lastMoviment mov);
    };

    public:

    // Move o iterator para o inicio da matriz, para o nó pivô.
    void begin();

    // Move o iterador para direita caso o sentido do movimento do iterador seja
    // preservado.
    void next();

    // Move o iterador para o próximo elemento diferente de zero à sua direita. 
    void nextNotZero();

    // Move o iterator para baixo caso o sentido do movimento do iterador seja pre-
    // servado.
    void down();

    // Move o iterator para o próximo elemento abaixo diferente de zero.
    void downNotZero();

    // Retorna o valor da posição em que o iterator se encontra.
    double getKey();

    // Printa o valor e as coordenadas da posição do iterator.
    void printNode();

    // Retorna verdadeiro caso o iterator se encontre em um nó cabeça.
    bool inHeadNode();

    // Retorna verdadeiro caso o iterator se encontre no nó cabeça principal da matriz.
    bool inMainHeadNode();

    // Retorna a coluna em que o iterador se encontra.
    int getIteratorColumn();

    // Retorna a linha em que o iterador se encontra.
    int getIteratorLine();

    private:

    // Retorna verdadeiro caso a posição verdadeira do nó passado seja um nó cabeça.
    bool inHeadNode(Node *pos);

    // Retorna verdadeiro caso o nó passado se encontre no nó pivô da matriz.
    bool inMainHeadNode(Node *pos);

//------------------------------------------------------------------------------------

    private:

    Node *matriz;
    Iterator iterator;
    int numColunas;
    int numLinhas;

//------------------------------------------------------------------------------------

    public:

    // Inicializa uma matriz esparsa vazia com capacidade para m linhas e n colunas.
    Matriz(int m, int n);

    // Destrutor que libera toda a memória que foi alocada dinamicamente para esta
    // estrutura de dados.
    ~Matriz();

    //getters
    int getLinhas();

    int getColunas();

    // Insere um valor na célula (i, j) da matriz, onde i é a linha e j é a coluna.
    void insert(int i, int j, double value);

    // Devolve o valor na célula (i, j) da matriz, onde i é a linha e j é a coluna.
    double getValue(int i, int j);

    // Esse método imprime a matriz, inclusive os elementos iguais a zero.
    void print();

//------------------------------------------------------------------------------------

    private:

    // Retorna o nó acima da posição (i, j), ou seja, (i - 1, j);
    Node *aboveNode(int i, int j);

    // Retorna o nó a esquerda da posição (i, j), ou seja, (i, j - 1);
    Node *leftNode(int i, int j);

};



// Essa função recebe como parâmetro as matrizes A e B, devolvendo uma matriz C que
// é a soma de A e B.
Matriz *soma(Matriz *A, Matriz *B);

// Essa função recebe como parâmetro as matrizes A e B, devolvendo uma matriz C que
// é produto de A e B.
Matriz *multiplica(Matriz *A, Matriz *B);

// Essa função lê, de um arquivo de entrada, os elementos diferentes de zero de uma
// matriz e monta a estrutura especificada anteriormente, devolvendo um ponteiro 
// para uma Matriz alocada dinamicamente. Considere que a primeira linha do arquivo
// de entrada consiste dos valroes de m e n, e as demais linhas do arquivo são
// constituídas de triplas (i, j, valor) para os elementos diferentes de zero da
// matriz.
Matriz *lerMatrizDeArquivo(std::string nome_do_arquivo);

class ArgumentoInvalidoMatriz{
    
    std::string mensagem;

    public:
    
    ArgumentoInvalidoMatriz();

    std::string what();

    void emptyVectorMatriz();

    void notPositiveNumber();

    void invalidPosition();

    void occupedPosition();

    void notSameOrder();

    void notPossibleMult();

    void notPossibleOpenFile();

    void illegalMovement();

    void notPossibleReturnHeadnode();
};

#endif