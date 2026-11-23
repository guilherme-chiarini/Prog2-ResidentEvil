#ifndef INTERFACE_H
#define INTERFACE_H

#include "jogo.h"

#define LARGURA_TELA 1024
#define ALTURA_TELA 768
#define ALTURA_HUD 80

// Inicializa e encerra a janela Raylib
void inicializarJanela(void);
void encerrarJanela(void);

// Desenha o estado atual do jogo (mapa, entidades e HUD)
void desenharJogo(const JOGO *jogo);

#endif
