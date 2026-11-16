#ifndef EVENTOS_H
#define EVENTOS_H

#include "tipos.h"

// Duvida se eh melhor usar sistema de enum ou sistema de bool TRUE ou FALSE para o estado dos portoes
typedef enum {
  ABERTO,
  FECHADO
} ESTADO;

typedef struct {
  POSICAO posicao;
  
  // Se esta aberto ou fechado
  ESTADO estado;

  // Informacoes temporais para alternar entre os estados
  float tempoEstado;
  float duracaoEstado;
} PORTAO;

#endif
