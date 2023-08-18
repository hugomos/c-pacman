#include "mapa.h"
#include "ui.h" 
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


MAPA m;
POSICAO heroi;
int tem_pilula = 0;

int para_onde_o_fastasma_vai(int from_x, int from_y, int *to_x, int *to_y)
{
  int opcoes[4][2] = {
    {from_x, from_y + 1},
    {from_x, from_y - 1},
    {from_x + 1, from_y},
    {from_x - 1, from_y},
  };

  srand(time(0));
  for (int i = 0; i < 10; i++){
    int posicao = rand() % 4;

    if(pode_andar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])){
      *to_x = opcoes[posicao][0];
      *to_y = opcoes[posicao][1];

      return 1;
    }
  }
  return 0;
}

void fantasmas()
{
  MAPA copia;
  copia_mapa(&m, &copia);

  for(int i = 0; i < m.linhas; i++){
    for(int j = 0; j < m.colunas; j++){
      if(copia.matriz[i][j] == FANTASMA){
        
        int to_x;
        int to_y;
        int encontrou = para_onde_o_fastasma_vai(i, j, &to_x, &to_y);

        if(encontrou){
          anda_no_mapa(&m, i, j, to_x, to_y);
        }
      }
    }
  }

  liberar_mapa(&copia);
}

int acabou()
{
  POSICAO pos;
  int encontrou_heroi_no_mapa = encontrar_no_mapa(&m, &pos, HEROI);
  return !encontrou_heroi_no_mapa;
}

int eh_direcao(char direcao)
{
  return direcao == CIMA || direcao == ESQUERDA || direcao == BAIXO || direcao == DIREITA;
}

void move(char direcao)
{
  if(!eh_direcao(direcao)) return;

  int proxima_posicao_x = heroi.x;
  int proxima_posicao_y = heroi.y;

  switch(direcao){
    case CIMA:
      proxima_posicao_x--;
      break;
    case DIREITA:
      proxima_posicao_y++;
      break;
    case BAIXO:
      proxima_posicao_x++;
      break;
    case ESQUERDA:
      proxima_posicao_y--;
      break;
  }

  if(!pode_andar(&m, HEROI, proxima_posicao_x, proxima_posicao_y)){
    return;
  }

  if(eh_personagem(&m, PILULA, proxima_posicao_x, proxima_posicao_y)){
    tem_pilula = 1;
  }

  anda_no_mapa(&m, heroi.x, heroi.y, proxima_posicao_x, proxima_posicao_y);

  heroi.x = proxima_posicao_x;
  heroi.y = proxima_posicao_y;
}

void explode_pilula()
{
  if(!tem_pilula) return;

  explode_pilula2(heroi.x, heroi.y, 0, 1, 3);
  explode_pilula2(heroi.x, heroi.y, 0, -1, 3);
  explode_pilula2(heroi.x, heroi.y, 1, 0, 3);
  explode_pilula2(heroi.x, heroi.y, -1, 0, 3);
}

void explode_pilula2(int x, int y, int soma_x, int soma_y, int qtd)
{
  // condicao de parada obrigatoria
  if(qtd == 0) return;

  int novo_x = x + soma_x;
  int novo_y = y + soma_y;

  if(eh_parede(&m, novo_x, novo_y)) return;
  m.matriz[novo_x][novo_y] = VAZIO; //subtitui por "."

  explode_pilula2(novo_x, novo_y, soma_x, soma_y, qtd - 1); // recursiva
}

int main()
{
  ler_mapa(&m);
  encontrar_no_mapa(&m, &heroi, HEROI); //seta a posição do heroi

  do{
    printf("Tem pilula: %s\n", tem_pilula ? "Sim" : "Não");
    imprimir_mapa(&m);

    char comando;
    scanf(" %c", &comando);
    
    move(comando);

    if(comando == BOMBA){
      explode_pilula(heroi.x, heroi.y, 3);
    }

    fantasmas();

  } while (!acabou());

  liberar_mapa(&m);
}