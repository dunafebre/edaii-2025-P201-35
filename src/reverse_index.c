#include "reverse_index.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % MAX_BUCKETS;
}


ReverseIndex *InitReverseIndex() {
    ReverseIndex *index = malloc(sizeof(ReverseIndex));
    for (int i = 0; i < MAX_BUCKETS; ++i){
        index->buckets[i] = NULL;
    }
    return index;
}

void normalize(char *word) {
    for (int i = 0; word[i]; ++i) {
        if (ispunct(word[i])) word[i] = '\0'; //ispunct comprova si es un simbol de puntuacio
        else word[i] = tolower(word[i]); //tolower converteix de mauscula a minuscula
    }
}

//aquesta funcio afegeix la paraula i tots els docs on apareix al seu corresponent index de la taula hash
void AddWordToIndex(ReverseIndex *index, const char *w, Document *doc) {
    char word[MAX_WORD_LEN];
    strncpy(word, w, MAX_WORD_LEN - 1);
    word[MAX_WORD_LEN - 1] = '\0';
    normalize(word);
    unsigned int h = hash(word);
    WordEntry *entry = index->buckets[h];

    while (entry) {
        if (strcmp(entry->word, word) == 0) {
            AddDocument(entry->docs, doc);
            return;
        }
        entry = entry->next;
    }

    entry = malloc(sizeof(WordEntry));
    strcpy(entry->word, word);
    entry->docs = InitDocumentList();
    AddDocument(entry->docs, doc);
    entry->next = index->buckets[h];
    index->buckets[h] = entry;
}

//separa cada paraula dels texts
void extractWords(ReverseIndex *index, Document *doc, const char *text) {
    char word[MAX_WORD_LEN];
    int idx = 0;

    for (int i = 0; ; ++text) {
        if (*text == ' ' || *text == '\n' || *text == '\0') {
            if (idx > 0) {
                word[idx] = '\0';
                AddWordToIndex(index, word, doc);
                idx = 0;
            }
            if (*text == '\0') break;
        } else if (isalnum(*text)) { //comprova que sigui un numero
            if (idx < MAX_WORD_LEN - 1) {
                word[idx++] = *text;
            }
        }
    }
}

void BuildReverseIndex(ReverseIndex *index, DocumentList *docs) {
    for (DocumentNode *node = docs->primer; node; node = node->next) {
        extractWords(index, node->doc, node->doc->title);
        extractWords(index, node->doc, node->doc->body);
    }
}

DocumentList *GetDocumentsForWord(ReverseIndex *index, const char *w) {
    char word[MAX_WORD_LEN];
    strncpy(word, w, MAX_WORD_LEN - 1);
    word[MAX_WORD_LEN - 1] = '\0';
    normalize(word);
    unsigned int h = hash(word);
    WordEntry *entry = index->buckets[h];

    while (entry) {
        if (strcmp(entry->word, word) == 0) {
            return entry->docs;
        }
        entry = entry->next;
    }

    return NULL;
}

void FreeReverseIndex(ReverseIndex *index) {
    for (int i = 0; i < MAX_BUCKETS; i++) {
        WordEntry *entry = index->buckets[i];
        while (entry) {
            WordEntry *tmp = entry;
            entry = entry->next;
            free(tmp);
        }
    }
    free(index);
}