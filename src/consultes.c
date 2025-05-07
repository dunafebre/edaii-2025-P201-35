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

QueryList *InitQueryList() {
  QueryList *list = (QueryList *)malloc(sizeof(QueryList));
  list->head = NULL;
  list->count = 0;
  return list;
}

void AddQueryWord(QueryList *list, const char *word) {
  QueryNode *node = (QueryNode *)malloc(sizeof(QueryNode));
  node->word = (char *)malloc(sizeof(char) * (strlen(word) + 1)); //+1 pel '\0'
  strcpy(node->word, word);
  node->next = list->head;
  list->head = node;
}

void SearchDocs(DocumentList *docs, char paraules_clau[][MAX_PARAULA], int N){
  int trobats = 0;
  for (DocumentNode *node = docs->primer; node != NULL && trobats < 5; node = node->next) {
      int coincideixen = 1;  
      for (int i = 0; i < N; i++) {
          if (strstr(node->doc->body, paraules_clau[i]) == NULL) {
              coincideixen = 0;
              break;
          }
      }
      if (coincideixen) {
          printf("\nDocument trobat:\n");
          printf("ID: %d\n", node->doc->document_id);
          printf("Títol: %s\n", node->doc->title);
          trobats++;
      }
  }

  if (trobats == 0) {
      printf("No s'han trobat documents amb totes les paraules clau.\n");
  } 
}

void KeyWords(){
  int N;  
  printf("Quantes paraules clau vols introduir?\n");
  scanf("%d", &N);

  char paraules_clau[N][MAX_PARAULA];  

  QueryList *list = InitQueryList();

  for (int i = 0; i < N; i++) {
    printf("Introdueix la paraula clau %d: ", i + 1);
    scanf("%s", paraules_clau[i]);
    AddQueryWord(list, paraules_clau[i]);
  }
  
  printf("Has introduït les següents paraules clau:\n");
  for (int i = 0; i < N; i++) {
    printf("%s\n", paraules_clau[i]);
  }
  DocumentList * list = LoadDocumentsFromTheDataset();
  SearchDocs(list, paraules_clau, N);
}







