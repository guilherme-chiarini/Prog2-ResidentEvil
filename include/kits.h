#ifndef KITS_H
#define KITS_H

#include "tipos.h"

typedef enum {
    KIT_TIPO_A,
    KIT_TIPO_B,
    KIT_TIPO_C
} TIPO_KIT;

typedef enum{
    KIT_NO_MAPA,
    KIT_TRANSPORTADO,
    KIT_ENTREGUE
} ESTADO;

typedef struct {
    int id;
    POSICAO posicao;
    TIPO_KIT tipo;
    ESTADO estado;
} KIT;

typedef struct {
    POSICAO posicao;
    TIPO_KIT tipoAceito;
} ABRIGO;

#endif