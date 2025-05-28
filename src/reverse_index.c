#include "reverse_index.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// funció hash
unsigned int hash(const char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash % MAX_BUCKETS;
}

ReverseIndex *
InitReverseIndex() { // funció que inicialitza l'índex en el hashmap
  ReverseIndex *index = malloc(sizeof(ReverseIndex));
  for (int i = 0; i < MAX_BUCKETS; ++i) {
    index->buckets[i] = NULL; // omple la llista de paraules a NULL
  }
  return index;
}

void normalize(
    char *word) { // funció que converteix una string a la seva equivalent en
                  // minúscules i sense signes de puntuació
  for (int i = 0; word[i]; ++i) {
    if (ispunct(word[i]))
      word[i] = '\0'; // ispunct comprova si es un simbol de puntuació
    else
      word[i] = tolower(word[i]); // tolower converteix de majuscula a minuscula
  }
}

// aquesta funcio afegeix la paraula i el doc on apareix al seu corresponent
// index de la taula hash
void AddWordToIndex(ReverseIndex *index, const char *w, Document *doc) {
  char word[MAX_WORD_LEN];
  strcpy(word, w); // copiem la paraula en una variable word per poder
                   // tractar-la sense modificar la original
  normalize(word); // passem la paraula a minúscules i eliminem els signes de
                   // puntuació amb la funció creada anteriorment
  unsigned int h = hash(word); // h = index on anirà la paraula en el hashmap
  WordEntry *entry = index->buckets[h]; // accedim al bucket del hashmap on
                                        // hauria d'anar la paraula

  while (entry) { // si la paraula ja ha estat afegida amb anterioritat, o
                  // sigui, que entry ja existeix
    if (strcmp(entry->word, word) == 0) { // comprovem que la paraula coincideix
      AddDocument(entry->docs, doc);      // afegeix el document a la llista de
                                     // documents de la paraula en qüestió
      return;
    }
    entry = entry->next; // si l'entry existeix i la paraula no concideix
                         // busquem en la següent posició
  }
  // si la paraula encara no existeix a l'índex
  entry = malloc(sizeof(WordEntry)); // reservem espai per aquesta paraula
  strcpy(entry->word, word);         // copia la paraula
  entry->docs = InitDocumentList();  // incialitzem la llista de doc buida
  AddDocument(entry->docs, doc);     // afegim el doc
  entry->next = index->buckets[h];   // el next de la nova paraula apunta a la
                                   // primera que ja hi havia
  index->buckets[h] = entry; // afegeix la nova entrada al principi del bucket
}

// separa cada paraula dels texts
void extractWords(ReverseIndex *index, Document *doc, const char *text) {
  char word[MAX_WORD_LEN];
  int idx = 0;

  for (int i = 0; text[i] != '\0';
       ++i) { // bucle fins que arriba al final del text
    if (text[i] == ' ' ||
        text[i] == '\n') { // quan arribem al final d'una paraula
      if (idx > 0) {
        word[idx] = '\0';                 // tanquem la paraula
        AddWordToIndex(index, word, doc); // i l'afegim al seu corresponent
                                          // índex
        idx = 0; // tornem a inicilitzar a 0, per començar el procès amb una
                 // paraula nova
      }
    } else if (isalnum(
                   text[i])) { // isalum comprova que siguin números o lletres,
                               // o sigui, signes de puntuació, per exemple
      if (idx < MAX_WORD_LEN - 1) { // si la paraula no es pasa de la mida
                                    // maxima
        word[idx++] = text[i]; // construim la paraula, lletra per lletra, en la
                               // variable word
      }
    }
  }

  // última paraula si el text no acabava amb espai
  if (idx > 0) {
    word[idx] = '\0';
    AddWordToIndex(index, word, doc);
  }
}

void BuildReverseIndex(
    ReverseIndex *index,
    DocumentList *docs) { // funció que analitza tots els doc i guarda cada
                          // paraula al diccionari ReverseIndex
  for (DocumentNode *node = docs->primer; node != NULL;
       node = node->next) { // des del primer node la de llista de doc i acaba
                            // quan node == NULL
    extractWords(index, node->doc,
                 node->doc->title); // separem les paraules del titol
    extractWords(index, node->doc,
                 node->doc->body); // separem les paraules del cos
  }
}

DocumentList *GetDocumentsForWord(
    ReverseIndex *index,
    const char
        *w) { // funció que donada una paraula troba els doc en què apareix
  char word[MAX_WORD_LEN];
  strcpy(word, w);
  normalize(word); // convertim la paraula per assegurar-nos de que coincideix
                   // amb la que tenim guardada
  unsigned int h = hash(word);
  WordEntry *entry = index->buckets[h];

  while (entry) { // mentre existeixi entry (no sigui NULL)
    if (strcmp(entry->word, word) ==
        0) { // comparem la paraula a buscar amb la que hi ha a l'índex
      return entry->docs; // retornem el doc en qüestió
    }
    entry = entry->next; // si la paraula no coincideix passem a la següent
                         // paraula dins del mateix bucket
  }

  return NULL; // retorna NULL si no s'han trobat coincidencies amb la paraula
               // en el bucket o bé si l'índex està buit
}

void FreeReverseIndex(ReverseIndex *index) { // buidem el hashmap
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