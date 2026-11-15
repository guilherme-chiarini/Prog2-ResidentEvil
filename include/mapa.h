#ifndef MAPA_H
#define MAPA_H

#include "tipos.h"

typedef struct {

    // Le o terreno do arquivo mapa.txt
    char **terreno;
    
    // Definem dimensao do mapa
    int linhas;
    int colunas;

    // Define posicao inicial do jogador
    POSICAO posicaoInicial;
} MAPA;

#endif