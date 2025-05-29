#ifndef DOCUMENT_GRAPH_H
#define DOCUMENT_GRAPH_H

// lab04

#include "documents.h"

// graf basat en matriu d'adjacència

typedef struct {
  int **adjacency; // matriu d'adjacència[][]
  int size;        // nombre total de documents
} DocumentGraph;

DocumentGraph *InitDocumentGraph(int numDocuments);
void AddEdge(DocumentGraph *graph, int fromId, int toId);
void BuildGraphFromDocuments(DocumentGraph *graph, DocumentList *docs);
int GetIndegree(DocumentGraph *graph, int docId);
void CalculateRelevance(DocumentGraph *graph, DocumentList *docs);
void FreeDocumentGraph(DocumentGraph *graph);
DocumentList *SortDocumentsByRelevance(DocumentList *list);
void PrintDocumentsByRelevance(DocumentList *list);

#endif