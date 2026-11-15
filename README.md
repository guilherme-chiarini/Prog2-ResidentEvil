# Resident Evil — Projeto de Programação de Computadores II

## Sobre o projeto

Este repositório contém o desenvolvimento de um jogo eletrônico inspirado na franquia **Resident Evil**, elaborado como parte do trabalho prático da disciplina de **Programação de Computadores II**.

O projeto consiste na implementação de um jogo em linguagem C, utilizando a biblioteca gráfica **Raylib**, com o objetivo de aplicar, de maneira prática e integrada, os conceitos de programação estudados ao longo da disciplina.

A proposta é desenvolver um jogo de exploração e gerenciamento de recursos em um ambiente representado por uma grade bidimensional. O jogador assume o papel de um entregador que precisa percorrer diferentes cenários, coletar kits de suprimentos e transportá-los até os abrigos correspondentes, enquanto enfrenta obstáculos, administra seu tempo e evita zumbis que circulam pelo mapa.

A experiência é organizada em fases consecutivas, cada uma representada por um arquivo externo de mapa. Esses arquivos definem a disposição dos elementos do cenário, incluindo paredes, caminhos, jogador, kits, abrigos, zumbis, portões e saídas. Dessa forma, o jogo utiliza mapas carregados dinamicamente, permitindo a construção de diferentes ambientes sem a necessidade de modificar diretamente o código-fonte.

### Funcionamento geral

O jogador deve percorrer o cenário e realizar a coleta de diferentes tipos de kits, transportando-os até os abrigos compatíveis. O transporte segue uma estrutura de pilha com capacidade limitada a três itens, respeitando a ordem LIFO: o último kit coletado é o primeiro que poderá ser entregue.

Durante a exploração, o jogador precisa administrar sua movimentação e o tempo disponível, considerando as limitações impostas pela quantidade de itens transportados. Além disso, deve evitar os zumbis que se movimentam pelo cenário e observar os portões, que alternam periodicamente entre estados abertos e fechados.

O contato com zumbis pode provocar penalidades e perda de vidas, enquanto o esgotamento do tempo pode exigir o reinício da fase. Após a conclusão de todas as entregas necessárias, a saída do mapa é liberada, permitindo o avanço para o próximo cenário.

O jogo também contempla uma interface com informações sobre o estado da partida, incluindo vidas, pontuação, fase atual, tempo restante e itens transportados. Além disso, são previstas funcionalidades de menu inicial, pausa, salvamento e carregamento de partidas.

### Pastas e arquivos

 - source
   - main.c
   - jogo.c
   - mapa.c
   - jogador.c
   - kits.c
   - zumbis.c
   - interface.c
   - menu.c
   - eventos.c
   - save.c

 - include
   - jogo.h
   - mapa.h
   - jogador.h
   - kits.h
   - zumbis.h
   - interface.h
   - menu.h
   - eventos.h
   - save.h

 - mapas
   - mapa1.txt
   - mapa2.txt

 - saves
   - save.bin
