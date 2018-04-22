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
    int size;
    char* initAddress;
} espacos;
//TAMANHO MÁXIMO DE ALOCACAO: 65535 (maior unsigned short)

class meualoc{
    char* memoria; //char* pois eh byte a byte
    int magicNumber;
    std::vector<espacos> lista;
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

    ~meualoc();


};


#endif //MEMORYALOCATOR_ALOCA_H
