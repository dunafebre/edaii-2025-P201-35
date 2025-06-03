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
    clock_t start2 = clock();
    // Executa la cerca seqüencial (sense índex invers)
    ReverseIndex *index = InitHashMap();
    clock_t end2 = clock();

    double time_spent2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("Temps d'inicalització: %f segons\n", time_spent2);
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
      // Cerca amb reverse index
    clock_t start = clock();
    // Executa la cerca amb índex invers
    FerConsultaAmbIndex(index);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Temps de cerca amb reverse index: %f segons\n", time_spent);
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
