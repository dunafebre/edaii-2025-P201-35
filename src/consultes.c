#include "consultes.h"
#include "documents.h"
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_PARAULA 100

// lab02

QueryList *InitQueryList() { //inicialitzem la llista de consultes
  QueryList *list = (QueryList *)malloc(sizeof(QueryList));
  list->head = NULL;
  list->count = 0;
  return list;
}

void AddQueryWord(QueryList *list, const char *word) { //afegim una consulta a la llista enllaçada
  QueryNode *node = (QueryNode *)malloc(sizeof(QueryNode));
  node->word = (char *)malloc(sizeof(char) * (strlen(word) + 1)); //+1 pel '\0'
  strcpy(node->word, word); //funció que copia un text en una variable 
  node->next = list->head; //el punter next ara apuntarà a la primera consulta, que ara serà la segona
  list->head = node; //el primer element de la llista pasa a ser el node nou que volem afegir
}

void SearchDocs(DocumentList *docs, char paraules_clau[][MAX_PARAULA], int N){ //funció que busca les paraules clau en els documents
  int trobats = 0; //variable que ens ajudarà a comptar els 5 primers doc 
  for (DocumentNode *node = docs->primer; node != NULL && trobats < 5; node = node->next) { //iterem sobre els documents 
      int coincideixen = true; //suposem que les tres paraules s'han trobat 
      for (int i = 0; i < N; i++) { //iterem sobre la quantitat de paraules clau
          if (strstr(node->doc->body, paraules_clau[i]) == NULL) { //funció que busca coincidencies entre dos cadenes de text 
              coincideixen = false; //si alguna no troba coincidencies, canvia la variable a falsa
              break; //deixem de buscar
          }
      }
      if (coincideixen) { //si la variable coincideixen està en true, imprimim el doc on s'ha trobat la paraula clau
          printf("Document trobat:\n");
          printf("ID: %d\n", node->doc->document_id);
          printf("Títol: %s\n", node->doc->title);
          trobats++;
      }
  }

  if (trobats == 0) { //informem si no s'han trobat 
      printf("No s'han trobat documents amb les paraules clau.\n");
  } 
}

void KeyWords(){ //funció per a que l'usuari trii les paraules clau
  int N;  //quantitat de paraules
  printf("Quantes paraules clau vols introduir?\n");
  scanf("%d", &N);

  char paraules_clau[N][MAX_PARAULA];  //llista on emmagatzemar les paraules

  QueryList *list = InitQueryList(); //inicialitzem la llista de consultes i la guardem en la variable list

  for (int i = 0; i < N; i++) {
    printf("Introdueix la paraula clau %d: ", i + 1); //demanem les paraules clau
    scanf("%s", paraules_clau[i]); //les anem emmagatzeman a la llista
    AddQueryWord(list, paraules_clau[i]); //aprofitem el bucle per anar guardan les paraules també a la llista enllaçada CUIDADOOO ALERTAA!!
  }
  
  printf("Has introduït les següents paraules clau:\n"); //imprimim les paraules clau trobades
  for (int i = 0; i < N; i++) {
    printf("%s\n", paraules_clau[i]);
  }
  DocumentList *llista = LoadDocumentsFromDataset(); //cridem a les funcions anteriors per fer la búsqueda en els docs
  SearchDocs(llista, paraules_clau, N);
}


/*Inicialitzem la cua a NULL
static Query *queue[3] = {NULL, NULL, NULL};
static int count = 0;
// Show the last 3 queries using a queue
void query_queue(Query *q) {
  // Creem un bucle per desplaçar tots els elements de la cua una posició
  // endarrera
  if (count == 3) {
    Query_free(queue[2]);
    count = 2;
  }
  for (int i = count; i > 0; --i) {
    queue[i] = queue[i - 1];
  }
  // Introduïm el nou element al primer element de la cua, ja que és el més
  // recent
  queue[0] = q;
  count++; // Incrementem el contador

  printf("L'historial de les últimes consultes és:\n");
  for (int i = 0; i < count; ++i) {
    printf("·Query %d: ", i + 1);
    for (QueryNode *n = queue[i]->head; n; n = n->next) {
      if (n->exclude) {
        printf("-%s ", n->keyword);
      } else {
        printf("%s ", n->keyword);
      }
    }
    printf("\n");
  }
  printf("\n");
}

void query_queue_clear(void) {
  for (int i = 0; i < count; ++i) {
    Query_free(queue[i]);
    queue[i] = NULL;
  }
  count = 0;
}*/




