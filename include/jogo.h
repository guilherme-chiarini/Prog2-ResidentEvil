#ifndef JOGO_H
#define JOGO_H

#include "eventos.h"
#include "jogador.h"
#include "kits.h"
#include "mapa.h"
#include "tipos.h"
#include "zumbis.h"

typedef struct {
  MAPA mapa;
  JOGADOR jogador;
} JOGO;

#endif
