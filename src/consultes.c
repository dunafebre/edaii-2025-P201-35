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

QueryList *InitQueryList() { // inicialitzem la llista de consultes
  QueryList *list = (QueryList *)malloc(sizeof(QueryList));
  list->head = NULL;
  list->count = 0;
  return list;
}

void AddQueryWord(
    QueryList *list,
    const char *word) { // afegim una consulta a la llista enllaçada
  QueryNode *node = (QueryNode *)malloc(sizeof(QueryNode));
  node->word = (char *)malloc(sizeof(char) * (strlen(word) + 1)); //+1 pel '\0'
  strcpy(node->word, word); // funció que copia un text en una variable
  node->next = list->head; // el punter next ara apuntarà a la primera consulta,
                           // que ara serà la segona
  list->head = node; // el primer element de la llista pasa a ser el node nou
                     // que volem afegir
}

void SearchDocs(DocumentList *docs, char paraules_clau[][MAX_PARAULA],
                int N) { // funció que busca les paraules clau en els documents
  int trobats = 0;       // variable que ens ajudarà a comptar els 5 primers doc
  for (DocumentNode *node = docs->primer; node != NULL && trobats < 5;
       node = node->next) {       // iterem sobre els documents
    int coincideixen = true;      // suposem que les tres paraules s'han trobat
    for (int i = 0; i < N; i++) { // iterem sobre la quantitat de paraules clau
      if (strstr(node->doc->body, paraules_clau[i]) ==
          NULL) { // funció que busca coincidencies entre dos cadenes de text
        coincideixen = false; // si alguna no troba coincidencies, canvia la
                              // variable a falsa
        break;                // deixem de buscar
      }
    }
    if (coincideixen) { // si la variable coincideixen està en true, imprimim el
                        // doc on s'ha trobat la paraula clau
      trobats++;
      if (trobats <=
          5) { // imprimeix el 5 primers doc on apareixen les paraules clau
        printf("Document trobat amb totes les paraules:\n");
        printf("ID: %d\n", node->doc->document_id);
        printf("Títol: %s\n", node->doc->title);
        //printf("Body: %s\n\n", node->doc->body);
      }
    }
  }

  if (trobats == 0) { // informem si no s'han trobat
    printf("No s'han trobat documents amb les paraules clau.\n");
  }
}

void KeyWords() { // funció per a que l'usuari trii les paraules clau
  int N;          // quantitat de paraules
  printf("Quantes paraules clau vols introduir?\n");
  scanf("%d", &N);

  char paraules_clau[N][MAX_PARAULA]; // llista on emmagatzemar les paraules

  QueryList *list = InitQueryList(); // inicialitzem la llista de consultes i la
                                     // guardem en la variable list

  for (int i = 0; i < N; i++) {
    printf("Introdueix la paraula clau %d: ",
           i + 1);                 // demanem les paraules clau
    scanf("%s", paraules_clau[i]); // les anem emmagatzeman a la llista
    AddQueryWord(
        list,
        paraules_clau[i]); // aprofitem el bucle per anar guardan les paraules
                           // també a la llista enllaçada CUIDADOOO ALERTAA!!
  }

  printf(
      "Has introduït les següents paraules clau:\n\n"); // imprimim les paraules
                                                        // clau trobades
  for (int i = 0; i < N; i++) {
    printf("%s\n", paraules_clau[i]);
  }
  DocumentList *llista =
      LoadDocumentsFromDataset(); // cridem a les funcions anteriors per fer la
                                  // búsqueda en els docs
  SearchDocs(llista, paraules_clau, N);
}

void CercaDocumentsAmbIndex(
    ReverseIndex *index, char paraules_clau[][MAX_PARAULA],
    int N) { // funció que retorna els docs on aparaiexen totes les paraules
             // demanades, utilitzant reverse index
  DocumentList *docs_all_words = NULL; // inicilitzem a NULL una llista de docs

  for (int i = 0; i < N; i++) {
    char word[MAX_PARAULA];
    strcpy(word,
           paraules_clau[i]); // accedim a la primera paraula de les keywords
    Normalize(word);

    DocumentList *docs_one_word = GetDocumentsForWord(
        index, word); // obtenim els docs que contenen aquesta paraula
    if (docs_one_word == NULL) {
      printf("Cap document conté la paraula: %s\n",
             word); // si alguna paraula no es troba en cap document, sortim
      return;
    }

    if (docs_all_words == NULL) {
      docs_all_words = InitDocumentList(); // inicialitzem la llista de docs amb
                                           // totes les paraules buscades alhora
      for (DocumentNode *node = docs_one_word->primer; node != NULL;
           node = node->next) { // recorrem tots els docs de la llista
                                // "docs_one_word"
        AddDocument(docs_all_words, node->doc);
      }
    } else {
      DocumentList *interseccio_temp =
          InitDocumentList(); // inicialitzem una llista de documents que serà
                              // temporal per poder comparar
      for (DocumentNode *node1 = docs_all_words->primer; node1 != NULL;
           node1 = node1->next) {
        for (DocumentNode *node2 = docs_one_word->primer; node2 != NULL;
             node2 =
                 node2->next) { // comparem la llista de la paraula individual i
                                // la llista interseccio (la que conté ja els
                                // documents comuns amb totes les paraules)
          if (node1->doc->document_id ==
              node2->doc->document_id) { // si son iguals afegeix el doc en
                                         // qüestió en la temporal

            AddDocument(interseccio_temp, node1->doc);
          }
        }
      }
      // FreeDocumentList(docs_all_words);  // alliberem l'antiga intersecció
      docs_all_words = interseccio_temp; // actualitzem docs_all_words amb la
                                         // 'nova' intersecció
    }
  }

  if (docs_all_words == NULL || docs_all_words->primer == NULL) {
    printf("Cap document conté totes les paraules clau.\n");
    return;
  }

  printf("\nDocuments trobats:\n"); // mostrem fins a 5 documents
  int count = 0;
  for (DocumentNode *node = docs_all_words->primer; node != NULL && count < 5;
       node = node->next) {
    printf("- ID: %d, Títol: %s\n", node->doc->document_id, node->doc->title);
    count++;
  }
}

void FerConsultaAmbIndex(
    ReverseIndex *index) { // versió millorada amb reverse_index de la busqueda
                           // amb llistes del lab 2
  int N;
  printf("Quantes paraules clau vols buscar? ");
  scanf("%d", &N);

  char paraules[N][MAX_PARAULA];
  for (int i = 0; i < N; i++) {
    printf("Introdueix la paraula %d: ", i + 1);
    scanf("%s", paraules[i]);
  }

  CercaDocumentsAmbIndex(index, paraules, N);
}
