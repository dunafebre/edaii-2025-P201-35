#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#define MAX_LINKS 1000

#include <stdlib.h>
#include <string.h>

// lab01

typedef struct {
  int ids[MAX_LINKS];
  int count;
} Links;

typedef struct {
  char *title;
  int document_id;
  char *body;
  Links *links;
  int relevance;
} Document;

typedef struct DocumentNode {
  Document *doc;
  struct DocumentNode *next;
} DocumentNode;

typedef struct {
  DocumentNode *primer;
  int count;
} DocumentList;

Links *LinksInit();
Document *document_desserialize(char *path);
void FreeDocument(Document *document);

DocumentList *InitDocumentList();
void AddDocument(DocumentList *list, Document *doc);
DocumentList *LoadDocumentsFromDataset();
void SelectOneDoc();

#endif