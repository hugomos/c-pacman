#ifndef _GAME_H_
#define _GAME_H_

#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define BOMBA 'b'

int acabou();
void move(char direcao);
int eh_direcao(char direcao);
void fantasmas();
int para_onde_o_fastasma_vai(int from_x, int from_y, int *to_x, int *to_y);
void explode_pilula();
void explode_pilula2(int x, int soma_x, int y, int soma_y, int qtd);

#endif