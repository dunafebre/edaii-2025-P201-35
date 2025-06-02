#include "consultes.h"
#include "documents.h"
#include "graph.h"
#include "hashmap.h"
#include <stdio.h>
#include <time.h>

#define NUM_DOCUMENTS 12

int main() {
  // carrega i inicialitza dades
  DocumentList *docs = LoadDocumentsFromDataset();
  ReverseIndex *index = InitHashMap();
  BuildHashMap(index, docs);

  DocumentGraph *graph = InitDocumentGraph(NUM_DOCUMENTS);
  BuildGraphFromDocuments(graph, docs);
  CalculateRelevance(graph, docs);

  // menu principal
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

  //Calcular temps d'execució
  struct timespec start, end;
  long elapsed_ms;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // Code to be timed (example)
  for (long i = 0; i < 1000000000; ++i);

  clock_gettime(CLOCK_MONOTONIC, &end);
  elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 +
                 (end.tv_nsec - start.tv_nsec) / 1000000;

  printf("Elapsed time: %ld ms\n", elapsed_ms);
}
