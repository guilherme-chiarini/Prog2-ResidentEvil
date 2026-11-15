#ifndef ZUMBIS_H
#define ZUMBIS_H

#include "tipos.h"

typedef struct {
    POSICAO posicao;
    POSICAO posicaoInicial;

    float tempoMovimento;
    float intervaloMovimento;
} ZUMBI;

#endif