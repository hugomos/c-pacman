#include "mapa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE* carregar_mapa()
{
  FILE* f;
  f = fopen("../mapa.txt", "r");

  if(f == 0){
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }

  return f;
}

void copia_mapa(MAPA *origem, MAPA *destino)
{
  destino->linhas = origem->linhas;
  destino->colunas = origem->colunas;

  aloca_mapa(destino);

  for(int i = 0; i < origem->linhas; i++){
    strcpy(destino->matriz[i], origem->matriz[i]);
  }
}

int encontrar_no_mapa(MAPA* m, POSICAO* p, char c)
{
  for (int i = 0; i < m->linhas; i++){
    for (int j = 0; j < m->colunas; j++){
      if(m->matriz[i][j] == c){
        p->x = i;
        p->y = j;
        return 1;
      }
    }
  }
  return 0;
}

void liberar_mapa(MAPA *m)
{
  for(int i = 0; i < m->linhas; i++){
    free(m->matriz[i]);
  }
  free(m->matriz);
}

void aloca_mapa(MAPA *m)
{
  m->matriz = malloc(sizeof(char*) * m->linhas); //linhas
  
  for(int i = 0; i < m->linhas; i++){
    m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1)); // colunas + 1 (\0)
  }
}

void criar_mapa(MAPA *m, FILE *f)
{
  aloca_mapa(m);

  // preenche as linhas da matriz
  for(int i = 0; i < 5; i++){
    fscanf(f, "%s", m->matriz[i]);
  }
}

void ler_mapa(MAPA *m)
{
  FILE* f = carregar_mapa();
  fscanf(f, "%d %d", &(m->linhas), &(m->colunas));

  criar_mapa(m, f);

  fclose(f);
}

void anda_no_mapa(MAPA *m, int from_x, int from_y, int to_x, int to_y)
{
  char personagem = m->matriz[from_x][from_y];

  m->matriz[from_x][from_y] = VAZIO;
  m->matriz[to_x][to_y] = personagem;
}

int eh_parede(MAPA *m, int x, int y)
{
  return m->matriz[x][y] == PAREDE_VERTICAL || m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int eh_vazia(MAPA *m, int x, int y)
{
  return m->matriz[x][y] == VAZIO;
}

int eh_personagem(MAPA *m, char personagem, int x, int y)
{
  return m->matriz[x][y] == personagem;
}

int pode_andar(MAPA *m, char personagem, int x, int y)
{
  return !eh_parede(m, x, y) && !eh_personagem(m, personagem, x, y);
}