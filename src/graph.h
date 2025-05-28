#ifndef DOCUMENT_GRAPH_H
#define DOCUMENT_GRAPH_H

#include "documents.h"

// graf basat en matriu d'adjacència

typedef struct {
  int **adjacency; // matriu d'adjacència[][]
  int size;        // nombre total de documents
} DocumentGraph;

DocumentGraph *InitDocumentGraph(int numDocuments);
void AddEdge(DocumentGraph *graph, int fromId, int toId);
int GetIndegree(DocumentGraph *graph, int docId);
void CalculateRelevance(DocumentGraph *graph, DocumentList *docs);
void FreeDocumentGraph(DocumentGraph *graph);
DocumentList *SortDocumentsByRelevance(DocumentList *list);

#endif