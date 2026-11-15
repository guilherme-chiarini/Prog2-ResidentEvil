#ifndef TIPOS_H
#define TIPOS_H

typedef struct {
    int linha;
    int coluna;
} POSICAO;

typedef enum {
    CIMA,       // CIMA = 0 
    BAIXO,      // BAIXO = 1
    ESQUERDA,   // ESQUERDA = 2
    DIREITA     // DIREITA = 3
} DIRECAO;

#endif