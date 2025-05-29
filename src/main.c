#include "consultes.h"
#include "documents.h"
#include "graph.h"
#include "hashmap.h"
#include <stdio.h>

#define NUM_DOCUMENTS 12

int main() {
  // carrega i inicialitza dades
  DocumentList *docs = LoadDocumentsFromDataset();
  ReverseIndex *index = InitHashMap();
  BuildHashMap(index, docs);

  DocumentGraph *graph = InitDocumentGraph(NUM_DOCUMENTS);
  BuildGraphFromDocuments(graph, docs);
  CalculateRelevance(graph, docs);

  // menú principal
  int opcio = 0;
  while (opcio != 4) {
    printf("\nMENÚ PRINCIPAL:\n");
    printf("1. Visualitzar un document\n");
    printf("2. Fer una consulta per paraules clau\n");
    printf("3. Saber quins son els documents amb més rellevància\n");
    printf("4. Sortir\n> ");
    scanf("%d", &opcio);

    if (opcio == 1) {
      SelectOneDoc();
    } else if (opcio == 2) {
      FerConsultaAmbIndex(index);
    } else if (opcio == 3) {
      PrintDocumentsByRelevance(docs);
    } else if (opcio == 4) {
      printf("Sortint del programa.\n");
    } else {
      printf("Opció no vàlida.\n");
    }
  }
  FreeHashMap(index);
  FreeDocumentGraph(graph);
  return 0;
}
