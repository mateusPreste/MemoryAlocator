//
// Created by mateu on 17/04/2018.
//

#include <iostream>
#include <bitset>
#include <vector>
#include <time.h>
#include <algorithm>
#include "aloca.h"

using namespace std;

/* Escreve o cabeçalho
 * variavel clear é ativada em desalocações para limpar o numero magico da memoria
*/
void meualoc::writeHeader(char* start, short int size, int clear){
    start[0] = static_cast<char>(size >> 8);
    start[1] = static_cast<char>(size);
    if(clear){
        start[2] = static_cast<char>(magicNumber >> 8);
        start[3] = static_cast<char>(magicNumber);
    } else{
        start[2] = 0;
        start[3] = 0;
    }
}

//Retorna a variavel tamanho do cabeçalho do bloco alocado
short int meualoc::blockSize(char* address, short int magicNumber){
    //mascara de bits utilizada para evitar a repetição de 1 a direita
    short int numberMemory = (address[3]& 0xff);
    short int size = (address[1]& 0xff);
    size += (((short int) address[0])<< 8);
    numberMemory += ((short int)address[2]) << 8;

    if(numberMemory == magicNumber){
        return size;
    } else{
        return 0;
    }
}

//Construtor
meualoc::meualoc(int tamanhoMemoria, int politicaMem) {
    politic = politicaMem;
    memoria = (char*) malloc(tamanhoMemoria);
    srand (time(NULL));
    magicNumber = rand();
    //lista de espaço começa com espaço de tamanho N
    freespace first;
        first.size = tamanhoMemoria;
        first.initAddress = 0;
    spacelist.push_back(first);
}

char *meualoc::aloca(unsigned short int size) {
    //Iterador de blocos livres
    auto it = spacelist.begin();
    //tamanho do bloco escolhido
    short int bestSize = -1;
    //Ponteiro para o Bloco escolhido
    auto choosed = it;

    //Variaveis next fit
    //indica que o primeiro elemento ainda não foi verificado
    bool nextfirst = true;

    for(it; it != spacelist.end(); ){
        short int thisSize = (*it).size;
        cout << "tamanho" << thisSize << " " << size+4 << endl;
        switch(politic){
            case 0://BESTFIT
            {
                if(bestSize == -1){
                    bestSize = 32767;
                }
                // O bloco tem que ser o menor possivel
                if(thisSize >= size+4 && thisSize < bestSize){
                    bestSize = thisSize;
                    choosed = it;
                }
                ++it;
                break;
            }
            case 1: //FIRSTFIT
                if(thisSize >= size+4){
                    bestSize = thisSize;
                    choosed = it;
                    // encontrou o primeiro bloco valido, termine a busca
                    it = spacelist.end();
                } else{
                    ++it;
                }
                break;
            case 2: //NEXTFIT
                /*
                 * Para implementar a lista circular no vector
                 * verificamos o primeiro elemento
                 * marcamos ele (variavel choosed)
                 * colocamos ele no fim da fila
                 * repetimos o processo de colocar o head no fim da fila
                 * até que encontramos o elemento marcado
                 * indicando que percorremos toda a fila
                 */
                //lista circular, terminando no primeiro elemento verificado
                if(nextfirst || it != choosed){
                    if(thisSize >= size+4){
                        bestSize = thisSize;
                        choosed = it;
                        // encontrou o primeiro bloco valido, termine a busca
                        it = spacelist.end();
                    } else{
                        //rotação da lista
                        rotate(spacelist.begin(), spacelist.begin() + 1, spacelist.end());
                        //indica que o primeiro elemento ja foi verificado
                        nextfirst = false;
                    }
                } else{
                    //nenhum bloco encontrado, forçar o fim do for
                    it = spacelist.end();
                }
                break;
        }
    }

    //nenhum bloco foi encontrado a variavel bestSize permanece a mesma
    if(bestSize == 32767 || bestSize == -1){
        cout << "NAO HA ESPACO PARA A ALOCACAO" << endl;
        return nullptr;
    }

    //Endereço de memoria que sera alocado
    char* alocatedPos = memoria+(*choosed).initAddress;
    //Sera escrita na memoria o cabecalho
    writeHeader(alocatedPos, size+4, 1);
    //redimencionar o bloco livre
    choosed->initAddress += size+4;
    choosed->size -= size+4;

    //verificar se o bloco esta vazio
    if(choosed->size == 0){
        spacelist.erase(choosed);
    }

    //retorna o ponteiro apos o cabecalho
    return alocatedPos+4;
}

// retornando o proprio ponteiro caso a area tenha sido alocada, senão retorna nullptr
char *meualoc::verifica(char *ponteiro, int posicao) {
    if(blockSize(ponteiro+posicao, magicNumber) > 0){
        return ponteiro;
    } else{
        return nullptr;
    }
}

void meualoc::imprimeDados() {
    int bigger = 0;
    int average = 0;
    int amount = 0;

    auto pt = spacelist.begin();
    for (pt; pt != spacelist.end(); ++pt) {
        if(pt->size > bigger){
            bigger = pt->size;
        }
        average += pt->size;
        ++amount;
    }

    average /= amount;

    cout << "Tamanho da Lista de Vazios: " << spacelist.size() << endl
         << "Maior elemento da lista: " << bigger << endl
         << "Média dos elementos da lista: " << average << endl;
}

int meualoc::libera(char *local) {
    //IMPLEMENTAR
}

//Desconstrutor
meualoc::~meualoc() {
    free(memoria);
    spacelist.clear();
}

int main(){
    vector<char*> alocados;
    meualoc aloc(130, 2);
    aloc.imprimeDados();
    alocados.push_back(aloc.aloca(3));
    aloc.imprimeDados();
    alocados.push_back(aloc.aloca(8));
    aloc.imprimeDados();
    alocados.push_back(aloc.aloca(5));
    aloc.imprimeDados();
    alocados.push_back(aloc.aloca(2));
    aloc.imprimeDados();
    alocados.push_back(aloc.aloca(1));
    aloc.imprimeDados();
    for(char* add : alocados){
        aloc.libera(add);
        aloc.imprimeDados();
    }
}
