#ifndef REVERSE_INDEX_H
#define REVERSE_INDEX_H

// lab03

#include "documents.h"

#define MAX_WORD_LEN 30
#define MAX_BUCKETS 1009 // nombre primer, millora dispersió

typedef struct WordEntry {
  char word[MAX_WORD_LEN];
  DocumentList *docs;     // llista de documents on apareix la paraula
  struct WordEntry *next; // gestió de col·lisions
} WordEntry;

typedef struct {
  WordEntry *buckets[MAX_BUCKETS]; // llista de totes les paraules amb els seus
                                   // respectius documents
} ReverseIndex;

ReverseIndex *InitHashMap();
void Normalize(char *word);
void AddWordToIndex(ReverseIndex *index, const char *word, Document *doc);
DocumentList *GetDocumentsForWord(ReverseIndex *index, const char *word);
void BuildHashMap(ReverseIndex *index, DocumentList *docs);
void extractWords(ReverseIndex *index, Document *doc, const char *text);
unsigned int hash(const char *str);
void FreeHashMap(ReverseIndex *index);

#endif