#include "interface.h"
#include "raylib.h"
#include <math.h>
#include <stdio.h>

void inicializarJanela(void) {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Prog2 - Resident Evil");
    SetTargetFPS(60);
    // Desativa o fechamento automatico pelo ESC para podermos abrir o menu de pausa
    SetExitKey(KEY_NULL);
}

void encerrarJanela(void) {
    CloseWindow();
}

static void desenharHUD(const JOGO *jogo) {
    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_HUD, (Color){20, 20, 25, 255});
    DrawLine(0, ALTURA_HUD, LARGURA_TELA, ALTURA_HUD, DARKGRAY);

    // Tempo arredondado para cima, limitado a zero
    int tempoExibido = (jogo->tempoRestante > 0.0f) ? (int)ceilf(jogo->tempoRestante) : 0;
    Color corTempo = (tempoExibido <= 10) ? RED : RAYWHITE;

    DrawText(TextFormat("FASE: %d", jogo->fase), 20, 15, 22, GOLD);
    DrawText(TextFormat("VIDAS: %d", jogo->jogador.vida), 20, 45, 22, RED);
    DrawText(TextFormat("PONTOS: %d", jogo->jogador.pontuacao), 200, 15, 22, RAYWHITE);
    DrawText(TextFormat("TEMPO: %02ds", tempoExibido), 200, 45, 22, corTempo);

    // Carga (Pilha LIFO de kits)
    int qtdCarga = jogo->jogador.topo + 1;
    DrawText(TextFormat("CARGA (%d/%d):", qtdCarga, CAPACIDADE_PILHA), 430, 15, 22, SKYBLUE);

    for (int i = 0; i < CAPACIDADE_PILHA; i++) {
        int boxX = 430 + (i * 55);
        int boxY = 42;
        DrawRectangleLines(boxX, boxY, 45, 28, LIGHTGRAY);

        if (i <= jogo->jogador.topo) {
            int idKit = jogo->jogador.pilha[i];
            const char *letra = "?";
            Color corKit = WHITE;

            // Busca o tipo do kit pelo ID
            for (int k = 0; k < jogo->quantidadeKits; k++) {
                if (jogo->kits[k].id == idKit) {
                    if (jogo->kits[k].tipo == KIT_TIPO_A) { letra = "A"; corKit = GREEN; }
                    else if (jogo->kits[k].tipo == KIT_TIPO_B) { letra = "B"; corKit = BLUE; }
                    else if (jogo->kits[k].tipo == KIT_TIPO_C) { letra = "C"; corKit = ORANGE; }
                    break;
                }
            }
            DrawRectangle(boxX + 2, boxY + 2, 41, 24, corKit);
            DrawText(letra, boxX + 15, boxY + 4, 20, BLACK);
        }
    }

    DrawText("[ESC] Pausa", LARGURA_TELA - 150, 30, 20, GRAY);
}

void desenharJogo(const JOGO *jogo) {
    BeginDrawing();
    ClearBackground((Color){15, 15, 18, 255});

    desenharHUD(jogo);

    if (jogo->mapa.linhas <= 0 || jogo->mapa.colunas <= 0) {
        EndDrawing();
        return;
    }

    // Calcula tamanho dinamico da celula para caber na tela
    int areaW = LARGURA_TELA - 40;
    int areaH = ALTURA_TELA - ALTURA_HUD - 40;
    int tamCelulaW = areaW / jogo->mapa.colunas;
    int tamCelulaH = areaH / jogo->mapa.linhas;
    int tamCelula = (tamCelulaW < tamCelulaH) ? tamCelulaW : tamCelulaH;

    int offsetX = (LARGURA_TELA - (jogo->mapa.colunas * tamCelula)) / 2;
    int offsetY = ALTURA_HUD + (areaH + 40 - (jogo->mapa.linhas * tamCelula)) / 2;

    // 1. Terreno base (paredes, chao, saida)
    for (int l = 0; l < jogo->mapa.linhas; l++) {
        for (int c = 0; c < jogo->mapa.colunas; c++) {
            int x = offsetX + c * tamCelula;
            int y = offsetY + l * tamCelula;
            char celula = jogo->mapa.terreno[l][c];

            if (celula == '#') {
                DrawRectangle(x, y, tamCelula, tamCelula, DARKGRAY);
            } else if (celula == 'S') {
                DrawRectangle(x, y, tamCelula, tamCelula, (Color){40, 160, 80, 255});
                DrawText("S", x + tamCelula / 3, y + tamCelula / 4, tamCelula / 2, WHITE);
            } else {
                DrawRectangle(x, y, tamCelula, tamCelula, (Color){35, 35, 42, 255});
            }
            DrawRectangleLines(x, y, tamCelula, tamCelula, (Color){25, 25, 30, 255});
        }
    }

    // 2. Abrigos
    for (int i = 0; i < jogo->quantidadeAbrigos; i++) {
        int x = offsetX + jogo->abrigos[i].posicao.coluna * tamCelula;
        int y = offsetY + jogo->abrigos[i].posicao.linha * tamCelula;
        Color cor = WHITE;
        const char *rotulo = "A";

        if (jogo->abrigos[i].tipoAceito == KIT_TIPO_A) { cor = DARKGREEN; rotulo = "A"; }
        else if (jogo->abrigos[i].tipoAceito == KIT_TIPO_B) { cor = DARKBLUE; rotulo = "B"; }
        else if (jogo->abrigos[i].tipoAceito == KIT_TIPO_C) { cor = BROWN; rotulo = "C"; }

        DrawRectangle(x + 2, y + 2, tamCelula - 4, tamCelula - 4, cor);
        DrawText(rotulo, x + tamCelula / 3, y + tamCelula / 4, tamCelula / 2, WHITE);
    }

    // 3. Portoes
    for (int i = 0; i < jogo->quantidadePortoes; i++) {
        int x = offsetX + jogo->portoes[i].posicao.coluna * tamCelula;
        int y = offsetY + jogo->portoes[i].posicao.linha * tamCelula;

        if (jogo->portoes[i].estado == FECHADO) {
            DrawRectangle(x, y, tamCelula, tamCelula, MAROON);
            DrawRectangleLines(x + 2, y + 2, tamCelula - 4, tamCelula - 4, RED);
        } else {
            DrawRectangleLines(x + 2, y + 2, tamCelula - 4, tamCelula - 4, GREEN);
        }
    }

    // 4. Kits no mapa
    for (int i = 0; i < jogo->quantidadeKits; i++) {
        if (jogo->kits[i].estado == KIT_NO_MAPA) {
            int cx = offsetX + jogo->kits[i].posicao.coluna * tamCelula + tamCelula / 2;
            int cy = offsetY + jogo->kits[i].posicao.linha * tamCelula + tamCelula / 2;
            Color cor = WHITE;

            if (jogo->kits[i].tipo == KIT_TIPO_A) cor = GREEN;
            else if (jogo->kits[i].tipo == KIT_TIPO_B) cor = SKYBLUE;
            else if (jogo->kits[i].tipo == KIT_TIPO_C) cor = ORANGE;

            DrawCircle(cx, cy, tamCelula * 0.28f, cor);
        }
    }

    // 5. Zumbis
    for (int i = 0; i < jogo->quantidadeZumbis; i++) {
        int cx = offsetX + jogo->zumbis[i].posicao.coluna * tamCelula + tamCelula / 2;
        int cy = offsetY + jogo->zumbis[i].posicao.linha * tamCelula + tamCelula / 2;
        DrawCircle(cx, cy, tamCelula * 0.36f, LIME);
        DrawCircleLines(cx, cy, tamCelula * 0.36f, DARKGREEN);
    }

    // 6. Jogador (Entregador)
    int jx = offsetX + jogo->jogador.posicao.coluna * tamCelula + tamCelula / 2;
    int jy = offsetY + jogo->jogador.posicao.linha * tamCelula + tamCelula / 2;
    DrawCircle(jx, jy, tamCelula * 0.38f, YELLOW);
    DrawCircleLines(jx, jy, tamCelula * 0.38f, GOLD);

    EndDrawing();
}
