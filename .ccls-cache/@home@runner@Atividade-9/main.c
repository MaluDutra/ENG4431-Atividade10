#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Tema: Flores 🌸🌼🌷🌹🌺🌻

struct flor {
  int id;
  char nome[50];
  char cor[30];
  int active;
};
typedef struct flor Flor;

void lista_txt(void);
void le_txt(int id);
void adiciona_txt(char* nome, char* cor, int* ids_existentes); 
void atualiza_txt(int id, char* nomeNovo, char* corNova, Flor* listaFlores);
void remove_txt(int id, Flor* listaFlores);   

Flor* ler_array_bin(void);
void lista_bin(void);
void le_bin(int id);
void adiciona_bin(char* nome, char* cor, int* ids_existentes); 
void atualiza_bin(int id, char* nomeNovo, char* corNova, Flor* listaFlores);
void remove_bin(int id, Flor* listaFlores);   

int main(void) {
  Flor florArray[200];
  Flor* listaFloresBin;
  int lista_ids[200]; 

  FILE *arq = fopen("flores.txt", "r");

  if (arq == NULL) {
    printf("Erro ao abrir o arquivo.");
    exit(1);
  }

  int i = 0;
  while (!feof(arq)) {
    fscanf(arq, "%d,%[^,],%[^,],%d\n", &florArray[i].id, florArray[i].nome,
           florArray[i].cor,
           &florArray[i].active); // utilizado para ler o arquivo txt

    lista_ids[i] = florArray[i].id; // inserindo ids na lista de ids

    i++;
  }
  fclose(arq);

  // lista_txt(); // lista os registros do arquivo txt
  // putchar('\n');
  // lista_bin(); // lista os registros do arquivo binário
  // putchar('\n');

  // le_txt(77); // leitura de uma entrada do arquivo txt
  // putchar('\n');
  // le_bin(77); // leitura de uma entrada do arquivo binário
  // putchar('\n');

  // adiciona_txt("Tulipinha", "Vermelha", lista_ids); // adiciona uma entrada no arquivo txt
  // putchar('\n');
  // adiciona_bin("Tulipinha", "Vermelha", lista_ids); // adiciona uma entrada no arquivo bin
  // putchar('\n');

  // atualiza_txt(77, "Rosa", "Vermelha", florArray); // atualiza uma entrada no arquivo txt
  // putchar('\n');
  // atualiza_bin(77, "Rosa", "Vermelha", florArray); // atualiza uma entrada no arquivo bin
  // atualiza_bin(900, "Rosa", "Vermelha", florArray); // tentativa de atualizar uma entrada inexistente no arquivo bin
  // putchar('\n');

  // remove_txt(6, florArray); // remove uma entrada no arquivo txt
  // remove_txt(1000, florArray); // tentativa de remover uma entrada inexistente no arquivo txt
  // putchar('\n');
  // remove_bin(6, florArray); // remove uma entrada no arquivo bin
  // putchar('\n');

  // lista_txt(); // lista os registros do arquivo txt
  // putchar('\n');
  // lista_bin(); // lista os registros do arquivo binário
  // putchar('\n');

  return 0;
}

//arquivo txt
//================================================================================

void lista_txt(void) {
  Flor florAux;
  FILE *arqTxt;

  clock_t start, end, diff;
  start = clock();

  arqTxt = fopen("flores.txt", "r");

  if (arqTxt == NULL) {
    printf("Erro ao abrir o arquivo txt para listagem.");
    exit(1);
  }

  printf("Leitura arquivo txt:\n");

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

void le_txt(int id) {
  Flor florAux;
  FILE *arqTxt;
  int achado = 0;

  clock_t start, end, diff;
  start = clock();

  arqTxt = fopen("flores.txt", "r");

  if (arqTxt == NULL) {
    printf("Erro ao abrir o arquivo txt para leitura.");
    exit(1);
  }

  printf("Leitura arquivo txt:\n");

  while (!feof(arqTxt)) {
    fscanf(arqTxt, "%d,%[^,],%[^,],%d\n", &florAux.id, florAux.nome,
           florAux.cor,
           &florAux.active); // utilizado para ler o arquivo txt

    if (florAux.active == 0 && florAux.id == id) {
      printf("%d: %s - cor: %s\n", florAux.id, florAux.nome, florAux.cor);
      achado = 1;
    }
  }
  fclose(arqTxt);

  if (achado == 0)
  {
    printf("Não foi encontrado nenhum registro com o id %d.\n", id);
  }
  
  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void adiciona_txt(char* nome, char* cor, int* ids_existentes) {
  Flor florAux;
  FILE* arqTxt;
  int aux = 0;

  clock_t start, end, diff;
  start = clock();

  arqTxt = fopen("flores.txt", "a");
  
  if (arqTxt == NULL) {
    printf("Erro ao abrir o arquivo txt para adicionar.");
    exit(1);
  }
  
  strcpy(florAux.nome, nome);
  strcpy(florAux.cor, cor);
  florAux.active = 0;
  florAux.id = rand() % 100;

  do{
    for (int i = 0; i < 200; i++){
      if (florAux.id == ids_existentes[i]){
        florAux.id = rand() % 100;
        aux = i;
      }
    }
  } while (florAux.id == ids_existentes[aux]);
  
  fprintf(arqTxt, "\n%d,%s,%s,%d", florAux.id, florAux.nome, florAux.cor, florAux.active);

  fclose(arqTxt);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void atualiza_txt(int id, char* nomeNovo, char* corNova, Flor* listaFlores) {
  FILE *arqTxt;
  int achado = 0;
  int index = 0;

  clock_t start, end, diff;
  start = clock();

  for (int i = 0; i < 200; i++){
    if (listaFlores[i].id == id){
      achado = 1;
      index = i;
    }
  }

  if (achado == 0){
    printf("Não foi encontrado nenhum registro com o id %d.\n", id);
    end = clock();
    diff = end - start;
    printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
    return;
  }

  strcpy(listaFlores[index].nome, nomeNovo);
  strcpy(listaFlores[index].cor, corNova);

  arqTxt = fopen("flores.txt", "w");

  if (arqTxt == NULL) {
    printf("Erro ao abrir o arquivo txt para atualizar.");
    exit(1);
  }

  int aux = 0;
  fprintf(arqTxt, "%d,%s,%s,%d", listaFlores[aux].id, listaFlores[aux].nome,
    listaFlores[aux].cor,
    listaFlores[aux].active);
  aux++;
  
  while (listaFlores[aux].id){
    fprintf(arqTxt, "\n%d,%s,%s,%d", listaFlores[aux].id, listaFlores[aux].nome,
      listaFlores[aux].cor,
      listaFlores[aux].active);
    
    aux++;
  }
  
  fclose(arqTxt);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void remove_txt(int id, Flor* listaFlores) {
  FILE *arqTxt;
  int achado = 0;
  int index = 0;

  clock_t start, end, diff;
  start = clock();

  for (int i = 0; i < 200; i++){
    if (listaFlores[i].id == id){
      achado = 1;
      index = i;
    }
  }

  if (achado == 0){
    printf("Não foi encontrado nenhum registro com o id %d.\n", id);
    end = clock();
    diff = end - start;
    printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
    return;
  }

  listaFlores[index].active = 1;

  arqTxt = fopen("flores.txt", "w");

  if (arqTxt == NULL) {
    printf("Erro ao abrir o arquivo txt para deletar.");
    exit(1);
  }

  int aux = 0;
  while (listaFlores[aux].id){
    if (listaFlores[aux].active == 0){
      if (aux == 0){
        fprintf(arqTxt, "%d,%s,%s,%d", listaFlores[aux].id, listaFlores[aux].nome,
          listaFlores[aux].cor,
          listaFlores[aux].active);
      } 
      else {
        fprintf(arqTxt, "\n%d,%s,%s,%d", listaFlores[aux].id, listaFlores[aux].nome,
          listaFlores[aux].cor,
          listaFlores[aux].active);
      }
    }    
    aux++;
  }

  fclose(arqTxt);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

// arquivo binário
// ===========================================================================

void lista_bin(void) {
  Flor florAux;
  FILE *arqBin;

  clock_t start, end, diff;
  start = clock();

  arqBin = fopen("flores.bin", "rb");

  if (arqBin == NULL) {
    printf("Erro ao abrir o arquivo bin para listagem.");
    exit(1);
  }

  printf("Leitura arquivo binário:\n");

  while (fread(&florAux, sizeof(Flor), 1, arqBin) == 1) {
    if (florAux.active == 0) {
      printf("%d,%s,%s\n", florAux.id, florAux.nome, florAux.cor);
    }
  }
  fclose(arqBin);
  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void le_bin(int id) {
  Flor florAux;
  FILE *arqBin;
  int achado = 0;

  clock_t start, end, diff;
  start = clock();

  arqBin = fopen("flores.bin", "rb");

  if (arqBin == NULL) {
    printf("Erro ao abrir o arquivo bin para leitura.");
    exit(1);
  }

  printf("Leitura arquivo binário da flor de id %d:\n", id);

  while (fread(&florAux, sizeof(Flor), 1, arqBin) == 1) {
    if (florAux.active == 0 && florAux.id == id) {
      printf("%d: %s - cor: %s\n", florAux.id, florAux.nome, florAux.cor);
      achado = 1;
    }
  }
  fclose(arqBin);

  if (achado == 0)
  {
    printf("Não foi encontrado nenhum registro com o id %d.\n", id);
  }
  
  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void adiciona_bin(char* nome, char* cor, int* ids_existentes) {
  Flor florAux;
  FILE* arqBin;
  int aux = 0;

  clock_t start, end, diff;
  start = clock();

  arqBin = fopen("flores.bin", "ab");

  if (arqBin == NULL) {
    printf("Erro ao abrir o arquivo bin para adicionar.");
    exit(1);
  }

  strcpy(florAux.nome, nome);
  strcpy(florAux.cor, cor);
  florAux.active = 0;
  florAux.id = rand() % 100;

  do{
    for (int i = 0; i < 200; i++){
      if (florAux.id == ids_existentes[i]){
        florAux.id = rand() % 100;
        aux = i;
      }
    }
  } while (florAux.id == ids_existentes[aux]);

  fwrite(&florAux, sizeof(Flor), 1, arqBin);

  fclose(arqBin);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void atualiza_bin(int id, char* nomeNovo, char* corNova, Flor* listaFlores) {
  FILE *arqBin;
  int achado = 0;
  int index = 0;

  clock_t start, end, diff;
  start = clock();

  for (int i = 0; i < 200; i++){
    if (listaFlores[i].id == id){
      achado = 1;
      index = i;
    }
  }

  if (achado == 0){
    printf("Não foi encontrado nenhum registro com o id %d.\n", id);
    end = clock();
    diff = end - start;
    printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
    return;
  }

  strcpy(listaFlores[index].nome, nomeNovo);
  strcpy(listaFlores[index].cor, corNova);

  arqBin = fopen("flores.bin", "wb");

  if (arqBin == NULL) {
    printf("Erro ao abrir o arquivo bin para atualizar.");
    exit(1);
  }

  int aux = 0;
  while (listaFlores[aux].id){
    fwrite(&listaFlores[aux], sizeof(Flor), 1, arqBin);

    aux++;
  }

  fclose(arqBin);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}

void remove_bin(int id, Flor* listaFlores) {
  FILE *arqBin;
  int achado = 0;
  int index = 0;

  clock_t start, end, diff;
  start = clock();

  for (int i = 0; i < 200; i++){
    if (listaFlores[i].id == id){
      achado = 1;
      index = i;
    }
  }

  if (achado == 0){
    printf("Não foi encontrado nenhum registro com o id %d.\n", id);
    end = clock();
    diff = end - start;
    printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
    return;
  }

  listaFlores[index].active = 1;

  arqBin = fopen("flores.bin", "wb");

  if (arqBin == NULL) {
    printf("Erro ao abrir o arquivo bin para deletar.");
    exit(1);
  }

  int aux = 0;
  while (listaFlores[aux].id){
    if (listaFlores[aux].active == 0){
      fwrite(&listaFlores[aux], sizeof(Flor), 1, arqBin);
    }
    aux++;
  }

  fclose(arqBin);

  end = clock();
  diff = end - start;
  printf("Tempo gasto: %f\n", (double)diff / CLOCKS_PER_SEC);
}