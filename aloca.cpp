//
// Created by mateu on 17/04/2018.
//

#include "aloca.h"



meualoc::meualoc(int tamanhoMemoria, int politicaMem) {
    switch(politicaMem){
        case BESTFIT:
            break;
        case FIRSTFIT:
            break;
        case NEXTFIT:
            break;
        default:
            break;
    }
}

char *meualoc::aloca(unsigned short int tamanho) {
    return nullptr;
}

char *meualoc::verifica(char *ponteiro, int posicao) {
    return nullptr;
}

void meualoc::imprimeDados() {

}

int meualoc::libera(char *ponteiro) {
    return 0;
}

meualoc::~meualoc() {

}
