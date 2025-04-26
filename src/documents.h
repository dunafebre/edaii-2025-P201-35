#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#define MAX_LINKS 1000

typedef struct {
  int ids[MAX_LINKS];
  int count;
} Links;

typedef struct {
  char *title;
  int document_id;
  char *body;
  float relevance;
  Links *links;
} Document;

Document *document_desserialize(char *path);
Links *LinksInit();
void FreeDocument(Document *document);

#endif