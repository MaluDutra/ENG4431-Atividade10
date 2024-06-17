#include "crudTxt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lista_txt(FILE* arqTxt)
{
  Flor florArray[20];

  FILE *arq = fopen("flores.txt", "r");
  FILE *arqBin = fopen("flores.bin", "rb");

  clock_t start, end, diff;

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo.");
    exit(1);
  }

  if (arqBin == NULL) {
    printf("Erro ao abrir o arquivo binario.");
    exit(1);
  }

  start = clock();

  int i = 0;
  while (!feof(arq)) {
    fscanf(arq, "%d,%[^,],%f,%[^,],%[^,],%d\n", &florArray[i].id,
           florArray[i].nome, &florArray[i].preco, florArray[i].especie,
           florArray[i].cor,
           &florArray[i].tempoMedio); // utilizado para ler o arquivo txt

    // printf("%d,%s,%.2f,%s,%s,%d\n", florArray[i].id, florArray[i].nome,
    //        florArray[i].preco, florArray[i].especie, florArray[i].cor,
    //        florArray[i].tempoMedio);

    // fwrite(&florArray[i], sizeof(Flor), 1, arqBin); --> foi utilizado para
    // escrever o binário

    i++;
  }
  fclose(arq);
}

void le_txt()
{

}

void adiciona_txt()
{

}

void atualiza_txt()
{

}

void remove_txt()
{

}