#ifndef SAVE_H
#define SAVE_H
#include <stdbool.h>
#include "jogo.h"
bool salvarJogo(const JOGO *jogo, const char *caminhoArquivo);
bool carregarJogo(JOGO *jogo, const char *caminhoArquivo);
bool existeSave(const char *caminhoArquivo);

#endif
