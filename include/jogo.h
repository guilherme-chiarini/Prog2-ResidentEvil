#ifndef JOGO_H
#define JOGO_H

#include "eventos.h"
#include "jogador.h"
#include "kits.h"
#include "mapa.h"
#include "zumbis.h"

typedef struct {
  MAPA mapa;
  JOGADOR jogador;

  // Kits
  KIT *kits;
  int quantidadeKits;

  // Abrigos
  ABRIGO *abrigos;
  int quantidadeAbrigos;

  // Zumbis
  ZUMBI *zumbis;
  int quantidadeZumbis;

  // Portoes
  PORTAO *portoes;
  int quantidadePortoes;

  int fase;
  float tempoRestante;
} JOGO;

#endif
