#include "sortedFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// sorted no read one, no update one e no delete one tempo menor em comparação
// com o txt comum

int buscaBin(Flor *v, int id, int tamanho) {
  int inicio;
  int meio;
  int fim;

  inicio = 0;
  fim = tamanho - 1;

  while (inicio <= fim) {
    meio = (inicio + fim) / 2;

    if (id == v[meio].id) {
      return meio; // preciso retornar a posição do elemento
    } else if (id > v[meio].id) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
  }
  return -1;
}

int partition(Flor *flores, int left, int right) {
  int pivot = flores[left].id;
  int i = left;
  Flor aux;

  for (int j = left + 1; j <= right; j++) {
    if (flores[j].id <= pivot) {
      i += 1;
      aux = flores[i];
      flores[i] = flores[j];
      flores[j] = aux;
    }
  }

  // troca pivot (flores[left]) com i.
  aux = flores[left];
  flores[left] = flores[i];
  flores[i] = aux;

  return i;
}

void quickSort(Flor *flores, int left, int right) {
  if (left < right) {
    int index_pivot = partition(flores, left, right);
    quickSort(flores, left, index_pivot - 1);
    quickSort(flores, index_pivot + 1, right);
  }
}

void sort_arquivo(void) {
  Flor florArray[200];

  FILE *arq = fopen("floresSRT.txt", "r");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo txt sort.");
    exit(1);
  }

  int i = 0;
  while (!feof(arq)) {
    fscanf(arq, "%d,%[^,],%[^,],%d\n", &florArray[i].id, florArray[i].nome,
           florArray[i].cor,
           &florArray[i].active); // utilizado para ler o arquivo txt
    i++;
  }
  fclose(arq);

  quickSort(florArray, 0, i - 1);

  arq = fopen("floresSRT.txt", "w");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo txt sort para ajeitar ele.");
    exit(1);
  }

  int aux = 0;
  fprintf(arq, "%d,%s,%s,%d", florArray[aux].id, florArray[aux].nome,
          florArray[aux].cor, florArray[aux].active);
  aux++;

  while (florArray[aux].id) {
    fprintf(arq, "\n%d,%s,%s,%d", florArray[aux].id, florArray[aux].nome,
            florArray[aux].cor, florArray[aux].active);

    aux++;
  }

  fclose(arq);
}

void lista_txtSRT(void) {
  Flor florAux;
  FILE *arqTxt;

  clock_t start, end, diff;
  start = clock();

  arqTxt = fopen("floresSRT.txt", "r");

  if (arqTxt == NULL) {
    printf("Erro ao abrir o arquivo txt sort para listagem.");
    exit(1);
  }

  printf("Leitura arquivo txt sorted:\n");

  while (!feof(arqTxt)) {
    fscanf(arqTxt, "%d,%[^,],%[^,],%d\n", &florAux.id, florAux.nome,
           florAux.cor,
           &florAux.active); // utilizado para ler o arquivo txt

    if (florAux.active == 0) {
      printf("%d,%s,%s\n", florAux.id, florAux.nome, florAux.cor);
    }
  }
  fclose(arqTxt);
  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void le_txtSRT(int id) {
  Flor florAux[200];
  FILE *arq;
  int id_achado;

  clock_t start, end, diff;
  start = clock();

  arq = fopen("floresSRT.txt", "r");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo txt sort para leitura.");
    exit(1);
  }

  printf("Leitura arquivo txt sort:\n");
  int i = 0;
  while (!feof(arq)) {
    fscanf(arq, "%d,%[^,],%[^,],%d\n", &florAux[i].id, florAux[i].nome,
           florAux[i].cor,
           &florAux[i].active); // utilizado para ler o arquivo txt
    i++;
  }
  fclose(arq);

  id_achado = buscaBin(florAux, id, i);

  if (id_achado != -1 && florAux[id_achado].active == 0) {
    printf("%d: %s - cor: %s\n", florAux[id_achado].id, florAux[id_achado].nome,
           florAux[id_achado].cor);
  } else {
    printf("Não foi encontrado nenhum registro com o id %d.\n", id);
  }

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void adiciona_txtSRT(char *nome, char *cor, int *ids_existentes) {
  Flor florAux;
  FILE* arqTxt;
  int aux = 0;

  clock_t start, end, diff;
  start = clock();

  arqTxt = fopen("floresSRT.txt", "a");

  if (arqTxt == NULL) {
    printf("Erro ao abrir o arquivo txt sort para adicionar.");
    exit(1);
  }

  strcpy(florAux.nome, nome);
  strcpy(florAux.cor, cor);
  florAux.active = 0;
  florAux.id = rand() % 250;

  do{
    for (int i = 0; i < 200; i++){
      if (florAux.id == ids_existentes[i]){
        florAux.id = rand() % 250;
        aux = i;
      }
    }
  } while (florAux.id == ids_existentes[aux]);

  fprintf(arqTxt, "\n%d,%s,%s,%d", florAux.id, florAux.nome, florAux.cor, florAux.active);

  fclose(arqTxt);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
  sort_arquivo();
}

void atualiza_txtSRT(int id, char *nomeNovo, char *corNova) {
  Flor florAux[200];
  FILE *arq;
  int id_achado;

  arq = fopen("floresSRT.txt", "r");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo txt sort para leitura.");
    exit(1);
  }

  int i = 0;
  while (!feof(arq)) {
    fscanf(arq, "%d,%[^,],%[^,],%d\n", &florAux[i].id, florAux[i].nome,
           florAux[i].cor,
           &florAux[i].active); // utilizado para ler o arquivo txt
    i++;
  }
  fclose(arq);

  clock_t start, end, diff;
  start = clock();

  id_achado = buscaBin(florAux, id, i);

  if (id_achado == -1 || florAux[id_achado].active == 1) {
    printf("Não foi encontrado nenhum registro ativo com o id %d.\n", id);
    end = clock();
    diff = end - start;
    printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
    return;
  }

  strcpy(florAux[id_achado].nome, nomeNovo);
  strcpy(florAux[id_achado].cor, corNova);

  arq = fopen("floresSRT.txt", "w");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo txt sort para atualizar.");
    exit(1);
  }

  int aux = 0;
  fprintf(arq, "%d,%s,%s,%d", florAux[aux].id, florAux[aux].nome,
    florAux[aux].cor,
    florAux[aux].active);
  aux++;

  while (florAux[aux].id){
    fprintf(arq, "\n%d,%s,%s,%d", florAux[aux].id, florAux[aux].nome,
      florAux[aux].cor,
      florAux[aux].active);

    aux++;
  }

  fclose(arq);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void remove_txtSRT(int id) {
  Flor florAux[200];
  FILE *arq;
  int id_achado;

  arq = fopen("floresSRT.txt", "r");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo txt sort para leitura.");
    exit(1);
  }

  int i = 0;
  while (!feof(arq)) {
    fscanf(arq, "%d,%[^,],%[^,],%d\n", &florAux[i].id, florAux[i].nome,
           florAux[i].cor,
           &florAux[i].active); // utilizado para ler o arquivo txt
    i++;
  }
  fclose(arq);

  clock_t start, end, diff;
  start = clock();

  id_achado = buscaBin(florAux, id, i);

  if (id_achado == -1 || florAux[id_achado].active == 1) {
    printf("Não foi encontrado nenhum registro ativo com o id %d.\n", id);
    end = clock();
    diff = end - start;
    printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
    return;
  }

  florAux[id_achado].active = 1;

  arq = fopen("floresSRT.txt", "w");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo txt sort para deletar.");
    exit(1);
  }

  int aux = 0;
  while (florAux[aux].id){
    if (florAux[aux].active == 0){
      if (aux == 0){
        fprintf(arq, "%d,%s,%s,%d", florAux[aux].id, florAux[aux].nome,
          florAux[aux].cor,
          florAux[aux].active);
      } 
      else {
        fprintf(arq, "\n%d,%s,%s,%d", florAux[aux].id, florAux[aux].nome,
          florAux[aux].cor,
          florAux[aux].active);
      }
    }    
    aux++;
  }

  fclose(arq);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
  sort_arquivo();
}