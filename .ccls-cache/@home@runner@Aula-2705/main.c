#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://replit.com/@LuisFernando4/Aula-07-Revisao-de-C?v=1#main.c
// Tema: Flores 🌸🌼🌷🌹🌺🌻

typedef struct flor {
  int id;
  char nome[50];
  float preco;
  char especie[40];
  char cor[30];
  int tempoMedio;
} Flor;

int main(void) {
  Flor florArray[20];

  FILE *arq = fopen("flores.txt", "r");
  FILE *arqBin = fopen("flores.bin", "wb");

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
           florArray[i].cor, &florArray[i].tempoMedio);

    //printf("%d,%s,%.2f,%s,%s,%d\n", florArray[i].id, florArray[i].nome,
    //       florArray[i].preco, florArray[i].especie, florArray[i].cor,
    //       florArray[i].tempoMedio);

    // fwrite(&florArray[i], sizeof(Flor), 1, arqBin); --> foi utilizado para
    // escrever o binário

    i++;
  }
  end = clock();

  diff = end - start;
  printf("Tempo gasto: %f\n", (double) diff / CLOCKS_PER_SEC);
  
  fclose(arq);
  fclose(arqBin);

  return 0;
}