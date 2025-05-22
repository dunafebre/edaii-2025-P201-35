#ifndef REVERSE_INDEX_H
#define REVERSE_INDEX_H

#include "documents.h"

#define MAX_WORD_LEN 30
#define MAX_BUCKETS 1009 // nombre primer, millora dispersió

typedef struct WordEntry {
    char word[MAX_WORD_LEN];
    DocumentList *docs; // llista de documents on apareix la paraula
    struct WordEntry *next; // gestió de col·lisions
} WordEntry;

typedef struct {
    WordEntry *buckets[MAX_BUCKETS];
} ReverseIndex;

ReverseIndex *InitReverseIndex();
void AddWordToIndex(ReverseIndex *index, const char *word, Document *doc);
DocumentList *GetDocumentsForWord(ReverseIndex *index, const char *word);
void BuildReverseIndex(ReverseIndex *index, DocumentList *docs);
unsigned int hash(const char *str);
void FreeReverseIndex(ReverseIndex *index);

#endif