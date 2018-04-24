//
// Created by mateu on 17/04/2018.
//

#ifndef MEMORYALOCATOR_ALOCA_H
#define MEMORYALOCATOR_ALOCA_H


#define BESTFIT 0
#define FIRSTFIT 1
#define NEXTFIT 2

#include <vector>

typedef struct{
    int initAddress;
    short int size;
} freespace;

//TAMANHO MÁXIMO DE ALOCACAO: 65535 (maior unsigned short)

class meualoc{
    char* memoria; //char* pois eh byte a byte
    short int magicNumber;
    int politic;
    std::vector<freespace> spacelist;
public:
    //tamanhoMemoria vai definir o tamanho da memória que o alocador vai utilizar
    //politicaMem define como escolher o bloco de onde saira a memória
    meualoc(int tamanhoMemoria,int politicaMem);

    //Pega um pedaco da variavel memoria e aloca, retornando o ponteiro para o comeco dessa regiao e atualizando a lista de livres.
    char *aloca(unsigned short int tamanho);

    //Verifica se a posicao dada pelo ponteiro esta alocada
    char* verifica(char* ponteiro,int posicao=0);

    //Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
    int libera(char* ponteiro);

    //Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
    void imprimeDados();

    void writeHeader(char* start, short int size, int clear);

    //retorna o tamanho de um bloco alocado
    short int blockSize(char* address, short int magicNumber);

    ~meualoc();


};


#endif //MEMORYALOCATOR_ALOCA_H
