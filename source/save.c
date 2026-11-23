#include "save.h"
#include <stdio.h>
#include <stdlib.h>

bool existeSave(const char *caminhoArquivo) {
    FILE *arq = fopen(caminhoArquivo, "rb");
    if (arq != NULL) {
        fclose(arq);
        return true;
    }
    return false;
}

bool salvarJogo(const JOGO *jogo, const char *caminhoArquivo) {
    if (jogo == NULL || caminhoArquivo == NULL) return false;

    FILE *arq = fopen(caminhoArquivo, "wb");
    if (arq == NULL) return false;

    // 1. Dados gerais da partida e do jogador
    fwrite(&jogo->fase, sizeof(int), 1, arq);
    fwrite(&jogo->tempoRestante, sizeof(float), 1, arq);
    fwrite(&jogo->jogador, sizeof(JOGADOR), 1, arq);

    // 2. Dimensoes, posicao inicial e matriz dinamica do mapa
    fwrite(&jogo->mapa.linhas, sizeof(int), 1, arq);
    fwrite(&jogo->mapa.colunas, sizeof(int), 1, arq);
    fwrite(&jogo->mapa.posicaoInicial, sizeof(POSICAO), 1, arq);

    for (int i = 0; i < jogo->mapa.linhas; i++) {
        fwrite(jogo->mapa.terreno[i], sizeof(char), jogo->mapa.colunas, arq);
    }

    // 3. Kits
    fwrite(&jogo->quantidadeKits, sizeof(int), 1, arq);
    if (jogo->quantidadeKits > 0) {
        fwrite(jogo->kits, sizeof(KIT), jogo->quantidadeKits, arq);
    }

    // 4. Abrigos
    fwrite(&jogo->quantidadeAbrigos, sizeof(int), 1, arq);
    if (jogo->quantidadeAbrigos > 0) {
        fwrite(jogo->abrigos, sizeof(ABRIGO), jogo->quantidadeAbrigos, arq);
    }

    // 5. Zumbis
    fwrite(&jogo->quantidadeZumbis, sizeof(int), 1, arq);
    if (jogo->quantidadeZumbis > 0) {
        fwrite(jogo->zumbis, sizeof(ZUMBI), jogo->quantidadeZumbis, arq);
    }

    // 6. Portoes
    fwrite(&jogo->quantidadePortoes, sizeof(int), 1, arq);
    if (jogo->quantidadePortoes > 0) {
        fwrite(jogo->portoes, sizeof(PORTAO), jogo->quantidadePortoes, arq);
    }

    fclose(arq);
    return true;
}

bool carregarJogo(JOGO *jogo, const char *caminhoArquivo) {
    if (jogo == NULL || caminhoArquivo == NULL) return false;

    FILE *arq = fopen(caminhoArquivo, "rb");
    if (arq == NULL) return false;

    // 1. Dados gerais da partida e do jogador
    if (fread(&jogo->fase, sizeof(int), 1, arq) != 1) { fclose(arq); return false; }
    fread(&jogo->tempoRestante, sizeof(float), 1, arq);
    fread(&jogo->jogador, sizeof(JOGADOR), 1, arq);

    // 2. Mapa
    fread(&jogo->mapa.linhas, sizeof(int), 1, arq);
    fread(&jogo->mapa.colunas, sizeof(int), 1, arq);
    fread(&jogo->mapa.posicaoInicial, sizeof(POSICAO), 1, arq);

    jogo->mapa.terreno = (char **)malloc(jogo->mapa.linhas * sizeof(char *));
    for (int i = 0; i < jogo->mapa.linhas; i++) {
        jogo->mapa.terreno[i] = (char *)malloc(jogo->mapa.colunas * sizeof(char));
        fread(jogo->mapa.terreno[i], sizeof(char), jogo->mapa.colunas, arq);
    }

    // 3. Kits
    fread(&jogo->quantidadeKits, sizeof(int), 1, arq);
    if (jogo->quantidadeKits > 0) {
        jogo->kits = (KIT *)malloc(jogo->quantidadeKits * sizeof(KIT));
        fread(jogo->kits, sizeof(KIT), jogo->quantidadeKits, arq);
    } else {
        jogo->kits = NULL;
    }

    // 4. Abrigos
    fread(&jogo->quantidadeAbrigos, sizeof(int), 1, arq);
    if (jogo->quantidadeAbrigos > 0) {
        jogo->abrigos = (ABRIGO *)malloc(jogo->quantidadeAbrigos * sizeof(ABRIGO));
        fread(jogo->abrigos, sizeof(ABRIGO), jogo->quantidadeAbrigos, arq);
    } else {
        jogo->abrigos = NULL;
    }

    // 5. Zumbis
    fread(&jogo->quantidadeZumbis, sizeof(int), 1, arq);
    if (jogo->quantidadeZumbis > 0) {
        jogo->zumbis = (ZUMBI *)malloc(jogo->quantidadeZumbis * sizeof(ZUMBI));
        fread(jogo->zumbis, sizeof(ZUMBI), jogo->quantidadeZumbis, arq);
    } else {
        jogo->zumbis = NULL;
    }

    // 6. Portoes
    fread(&jogo->quantidadePortoes, sizeof(int), 1, arq);
    if (jogo->quantidadePortoes > 0) {
        jogo->portoes = (PORTAO *)malloc(jogo->quantidadePortoes * sizeof(PORTAO));
        fread(jogo->portoes, sizeof(PORTAO), jogo->quantidadePortoes, arq);
    } else {
        jogo->portoes = NULL;
    }

    fclose(arq);
    return true;
}
