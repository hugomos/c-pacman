#include "mapa.h"
#include "ui.h"

#include <stdio.h>
#include <stdlib.h>

char desenho_fantasma[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char desenho_parede[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char desenho_heroi[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char desenho_pilula[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char desenho_vazio[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void imprime_parte(char desenho[4][7], int parte)
{
  printf("%s", desenho[parte]);
}

void imprimir_mapa(MAPA *m)
{
  for(int i = 0; i < m->linhas; i++){

    for (int parte = 0; parte < 4; parte++){

      for(int j = 0; j < m->colunas; j++){
        
        switch (m->matriz[i][j]){
          case FANTASMA:
            imprime_parte(desenho_fantasma, parte);
            break;

          case HEROI:
            imprime_parte(desenho_heroi, parte);
            break;

          case PILULA:
            imprime_parte(desenho_pilula, parte);
            break;

          case PAREDE_VERTICAL:
          case PAREDE_HORIZONTAL:
            imprime_parte(desenho_parede, parte);
            break;

          case VAZIO:
            imprime_parte(desenho_vazio, parte);
            break;
        }
      }
      printf("\n");
    }
  }
}