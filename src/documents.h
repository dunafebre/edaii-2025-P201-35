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
} Document;

typedef struct DocumentNode {
  Document *doc;
  struct DocumentNode *next;
} DocumentNode;

typedef struct {
  DocumentNode *primer;
  int count;
} DocumentList;

Document *document_desserialize(char *path);
Links *LinksInit();
void FreeDocument(Document *document);

DocumentList *InitDocumentList();
void AddDocument(DocumentList *list, Document *doc);
DocumentList *LoadDocumentsFromTheDataset();

#endif