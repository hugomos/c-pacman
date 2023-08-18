#ifndef _MAPA_H_
#define _MAPA_H_

#include <stdio.h>
#include <stdlib.h>

#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'

struct mapa {
  char** matriz;
  int linhas;
  int colunas;
};

struct posicao {
  int x;
  int y;
};

typedef struct mapa MAPA;
typedef struct posicao POSICAO;

FILE* carregar_mapa();
void liberar_mapa(MAPA *m);
void criar_mapa(MAPA *m, FILE *f);
void ler_mapa(MAPA *m);
int encontrar_no_mapa(MAPA* m, POSICAO* p, char c);
void anda_no_mapa(MAPA *m, int from_x, int from_y, int to_x, int to_y);
int eh_vazia(MAPA *m, int x, int y);
void aloca_mapa(MAPA *m);
void copia_mapa(MAPA *origem, MAPA *destino);
int eh_parede(MAPA *m, int x, int y);
int eh_personagem(MAPA *m, char personagem, int x, int y);
int pode_andar(MAPA *m, char personagem, int x, int y);

#endif