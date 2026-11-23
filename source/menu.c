#include "menu.h"
#include "interface.h"
#include "raylib.h"

static bool desenharBotao(Rectangle ret, const char *texto, bool habilitado) {
    Vector2 mouse = GetMousePosition();
    bool hover = habilitado && CheckCollisionPointRec(mouse, ret);

    Color corFundo = !habilitado ? (Color){40, 40, 45, 255}
                   : hover       ? (Color){180, 40, 40, 255}
                                 : (Color){60, 60, 70, 255};
    Color corTexto = habilitado ? RAYWHITE : GRAY;

    DrawRectangleRec(ret, corFundo);
    DrawRectangleLinesEx(ret, 2, hover ? RED : DARKGRAY);

    int larguraTexto = MeasureText(texto, 24);
    DrawText(texto, ret.x + (ret.width - larguraTexto) / 2, ret.y + (ret.height - 24) / 2, 24, corTexto);

    return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

ACAO_MENU atualizarDesenharMenuInicial(bool temSaveDisponivel) {
    ACAO_MENU acao = ACAO_NENHUMA;

    BeginDrawing();
    ClearBackground((Color){15, 15, 18, 255});

    const char *titulo = "RESIDENT EVIL: SUPPLY RUN";
    DrawText(titulo, (LARGURA_TELA - MeasureText(titulo, 44)) / 2, 160, 44, RED);

    float btnW = 320, btnH = 55;
    float btnX = (LARGURA_TELA - btnW) / 2.0f;

    if (desenharBotao((Rectangle){btnX, 300, btnW, btnH}, "NOVO JOGO", true)) {
        acao = ACAO_NOVO_JOGO;
    }
    if (desenharBotao((Rectangle){btnX, 375, btnW, btnH}, "CARREGAR JOGO", temSaveDisponivel)) {
        acao = ACAO_CARREGAR_JOGO;
    }
    if (desenharBotao((Rectangle){btnX, 450, btnW, btnH}, "SAIR", true)) {
        acao = ACAO_SAIR;
    }

    EndDrawing();
    return acao;
}

ACAO_MENU atualizarDesenharMenuPausa(bool jogoSalvoFeedback) {
    ACAO_MENU acao = ACAO_NENHUMA;

    BeginDrawing();
    ClearBackground((Color){15, 15, 18, 255});

    const char *titulo = "JOGO PAUSADO";
    DrawText(titulo, (LARGURA_TELA - MeasureText(titulo, 40)) / 2, 150, 40, GOLD);

    if (jogoSalvoFeedback) {
        const char *msg = "Progresso salvo com sucesso!";
        DrawText(msg, (LARGURA_TELA - MeasureText(msg, 22)) / 2, 215, 22, GREEN);
    }

    float btnW = 320, btnH = 55;
    float btnX = (LARGURA_TELA - btnW) / 2.0f;

    if (desenharBotao((Rectangle){btnX, 270, btnW, btnH}, "CONTINUAR", true) || IsKeyPressed(KEY_ESCAPE)) {
        acao = ACAO_CONTINUAR;
    }
    if (desenharBotao((Rectangle){btnX, 345, btnW, btnH}, "SALVAR JOGO", true)) {
        acao = ACAO_SALVAR_JOGO;
    }
    if (desenharBotao((Rectangle){btnX, 420, btnW, btnH}, "MENU INICIAL", true)) {
        acao = ACAO_VOLTAR_MENU;
    }

    EndDrawing();
    return acao;
}

ACAO_MENU atualizarDesenharTelaFim(bool vitoria, int pontuacaoFinal, const char *motivoDerrota) {
    ACAO_MENU acao = ACAO_NENHUMA;

    BeginDrawing();
    ClearBackground((Color){15, 15, 18, 255});

    const char *titulo = vitoria ? "MISSAO CONCLUIDA!" : "FIM DE JOGO";
    Color corTitulo = vitoria ? GREEN : RED;
    DrawText(titulo, (LARGURA_TELA - MeasureText(titulo, 46)) / 2, 170, 46, corTitulo);

    if (!vitoria && motivoDerrota != NULL) {
        DrawText(motivoDerrota, (LARGURA_TELA - MeasureText(motivoDerrota, 24)) / 2, 240, 24, LIGHTGRAY);
    }

    const char *txtPontos = TextFormat("PONTUACAO FINAL: %d", pontuacaoFinal);
    DrawText(txtPontos, (LARGURA_TELA - MeasureText(txtPontos, 30)) / 2, 300, 30, GOLD);

    float btnW = 320, btnH = 55;
    float btnX = (LARGURA_TELA - btnW) / 2.0f;

    if (desenharBotao((Rectangle){btnX, 400, btnW, btnH}, "VOLTAR AO MENU", true)) {
        acao = ACAO_VOLTAR_MENU;
    }
    if (desenharBotao((Rectangle){btnX, 475, btnW, btnH}, "SAIR", true)) {
        acao = ACAO_SAIR;
    }

    EndDrawing();
    return acao;
}
