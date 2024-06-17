#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct flor {
  int id;
  char nome[50];
  char cor[30];
  int active;
};
typedef struct flor Flor;

int buscaBin(Flor* v, int id, int tamanho);
int partition(Flor* values, int left, int right);
void quickSort(Flor* values, int left, int right);
void sort_arquivo(void);

void lista_txtSRT(void);
void le_txtSRT(int id);
void adiciona_txtSRT(char* nome, char* cor, int* ids_existentes); 
void atualiza_txtSRT(int id, char *nomeNovo, char *corNova);
void remove_txtSRT(int id);   