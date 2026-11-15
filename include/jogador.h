#ifndef JOGADOR_H
#define JOGADOR_H

#include "tipos.h"

#define CAPACIDADE_PILHA 3

typedef struct {
    
    POSICAO posicao;

    int vida;
    int pontuacao;

    int pilha[CAPACIDADE_PILHA];

    // Posicao do ultimo kit coletado
    int topo;

} JOGADOR;

#endif