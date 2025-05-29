#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// lab04

DocumentGraph *InitDocumentGraph(
    int numDocuments) { // inicialitza el graf amb una matriu d'adjacència
  DocumentGraph *graph =
      malloc(sizeof(DocumentGraph)); // reservem espai pel graph
  graph->size = numDocuments;        // assignem el nombre total de doc
  graph->adjacency = (int **)malloc(
      numDocuments * sizeof(int *)); // reservem espai per la matriu d'adj

  for (int i = 0; i < numDocuments;
       ++i) { // per cada node creem l'espai pels seus corresponents nodes (doc)
    graph->adjacency[i] =
        calloc(numDocuments,
               sizeof(int)); // calloc reserva memoria i inicialitza tot a 0
  }

  return graph;
}

void AddEdge(DocumentGraph *graph, int fromId,
             int toId) { // afegeix una aresta (un 1) entre doc relacionats
                         // (from ID i to ID)
  if (fromId < graph->size && toId < graph->size) {
    graph->adjacency[fromId][toId] = 1;
  }
}

void BuildGraphFromDocuments(
    DocumentGraph *graph,
    DocumentList *docs) { // funció que contrueix la connectivitat del graph
                          // segons els links dels docs
  for (DocumentNode *node = docs->primer; node != NULL;
       node = node->next) {    // recorrem els docs de la llista
    Document *doc = node->doc; // prenem un doc
    int fromId =
        doc->document_id; // guardem el seu id per després cridar a AddEdge

    for (int i = 0; i < doc->links->count; ++i) { // recorre els links del doc
      int toId = doc->links->ids[i]; // guardem els ids dels doc que estan
                                     // conectats amb el "principal"
      AddEdge(graph, fromId, toId);  // creem l'enllaç entre aquests docs
    }
  }
}

int GetIndegree(DocumentGraph *graph,
                int docId) { // retorna el grau d'entrada (quantes connexions hi
                             // ha amb un doc)
  int count = 0;
  for (int i = 0; i < graph->size; ++i) {
    count += graph->adjacency[i][docId]; // va sumant 1s i 0s (relació entre el
                                         // doc i la resta) al comptador
  }
  return count;
}

void CalculateRelevance(DocumentGraph *graph,
                        DocumentList *docs) { // calcula la rellevància de cada
                                              // document segons el seu indegree
  BuildGraphFromDocuments(graph, docs);
  for (DocumentNode *node = docs->primer; node != NULL;
       node = node->next) { // recorre tots els docs de llista
    int indegree = GetIndegree(
        graph, node->doc->document_id); // calcula el grau de cada doc
    node->doc->relevance =
        indegree; // afegeix aquest valor en la variable "relevance" de cada doc
  }
}

// ordena la llista de documents per rellevància (més rellevant primer)
DocumentList *SortDocumentsByRelevance(DocumentList *list) {
  if (list == NULL || list->count < 2) {
    return list; // si la llista no existeix o només té un doc (o menys), no cal
                 // endreçar
  }

  // converteix la llista a array
  DocumentNode **array = (DocumentNode **)malloc(
      list->count *
      sizeof(DocumentNode *)); // reserva espai per una array de punters a nodes
  int i = 0;
  for (DocumentNode *node = list->primer; node != NULL;
       node = node->next) { // recorre els element de la linked list
    array[i++] = node;      // va afegint cada node en l'array
  }

  // ordena l'array per rellevància (bubble sort per simplicitat)
  for (int i = 0; i < list->count; ++i) {
    for (int j = i + 1; j < list->count; ++j) {
      if (array[i]->doc->relevance < array[j]->doc->relevance) {
        DocumentNode *tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
      }
    }
  }

  // reconstrueix la llista
  for (int i = 0; i < list->count - 1; ++i) {
    array[i]->next =
        array[i + 1]; // fa la llista enllaçada de nou amb els index "i" i "i+1"
  }
  array[list->count - 1]->next = NULL; // l'últim doc té NULL com a next
  list->primer =
      array[0]; // el primer node de la llista és el primer doc de l'array

  free(array); // buidem l'array
  return list;
}

void PrintDocumentsByRelevance(
    DocumentList *list) { // imprimeix els docs amb ordre de rellèvancia
  list = SortDocumentsByRelevance(list);
  for (DocumentNode *node = list->primer; node != NULL; node = node->next) {
    printf("- [%d] %s (rellevància %d)\n", node->doc->document_id,
           node->doc->title, node->doc->relevance);
  }
}

void FreeDocumentGraph(DocumentGraph *graph) { // allibera la memòria del graf
  for (int i = 0; i < graph->size; ++i) {
    free(graph->adjacency[i]);
  }
  free(graph->adjacency);
  free(graph);
}