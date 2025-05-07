#ifndef CONSULTES_H
#define CONSULTES_H

#define MAX_PARAULA 100

// lab02

typedef struct QueryNode {
  char *word;
  struct QueryNode *next;
} QueryNode;

typedef struct {
  QueryNode *head;
  int count;
} QueryList;

QueryList *InitQueryList();
void AddQueryWord(QueryList *list, const char *word);
void KeyWords();
void SearchDocs(DocumentList *docs, char paraules_clau[][MAX_PARAULA], int N);

#endif