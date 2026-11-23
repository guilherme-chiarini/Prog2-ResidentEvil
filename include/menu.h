#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

typedef enum {
    TELA_MENU_INICIAL,
    TELA_JOGANDO,
    TELA_PAUSA,
    TELA_VITORIA,
    TELA_DERROTA,
    TELA_SAIR
} ESTADO_TELA;

typedef enum {
    ACAO_NENHUMA,
    ACAO_NOVO_JOGO,
    ACAO_CARREGAR_JOGO,
    ACAO_CONTINUAR,
    ACAO_SALVAR_JOGO,
    ACAO_VOLTAR_MENU,
    ACAO_SAIR
} ACAO_MENU;
ACAO_MENU atualizarDesenharMenuInicial(bool temSaveDisponivel);
ACAO_MENU atualizarDesenharMenuPausa(bool jogoSalvoFeedback);
ACAO_MENU atualizarDesenharTelaFim(bool vitoria, int pontuacaoFinal, const char *motivoDerrota);

#endif
