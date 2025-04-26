#include "documents.h"
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

Links *LinksInit() { // inicilitzem una llista de links
  Links *links = (Links *)malloc(sizeof(Links)); // reservem espai per la llista
  links->count = 0; // inicialitzem el comptador a 0
  return links;     // retornem la llista
}

Document *document_desserialize(
    char *path) { // converteix els fitxers a la data strucutre
  FILE *f = fopen(path, "r");
  assert(f != NULL);

  Document *document = (Document *)malloc(sizeof(Document));

  char buffer[262144];
  int bufferSize = 262144;
  int bufferIdx = 0;
  char ch;

  // parse id
  while ((ch = fgetc(f)) != '\n') { // llegeix fins que troba un salt de linea
    assert(bufferIdx < bufferSize); // comprova possibles errors
    buffer[bufferIdx++] = ch; // introdueix en la llista buffer els caràcters
                              // que va llegint al document
  }
  assert(bufferIdx < bufferSize); // comprova possibles errors
  buffer[bufferIdx++] = '\0'; // afegeix un caracter nul al final de la llista,
                              // per indicar final del text
  document->document_id =
      atoi(buffer); // converteix de char a integer i afegeix aquest nombre en
                    // l'apartat "id" de la data structure

  // parse title
  bufferIdx = 0;                    // tornem a inicialitzar el index a 0
  while ((ch = fgetc(f)) != '\n') { // llegeix fins que troba un salt de linea
    assert(bufferIdx < bufferSize); // comprova possibles errors
    buffer[bufferIdx++] = ch; // introdueix en la llista buffer els caràcters
                              // que va llegint al document
  }
  assert(bufferIdx < bufferSize); // comprova possibles errors
  buffer[bufferIdx++] = '\0'; // afegeix un caracter nul al final de la llista,
                              // per indicar final del text

  document->title = (char *)malloc(sizeof(char) * (bufferIdx + 1));

  strcpy(document->title, buffer); // copiem el text de buffer en l'apartat
                                   // title de la data structure
  document->title[sizeof(document->title) - 1] = '\0'; // tanquem el text

  // parse body
  char linkBuffer[64];
  int linkBufferSize = 64;
  int linkBufferIdx = 0;
  bool parsingLink = false;
  Links *links = LinksInit();

  bufferIdx = 0;
  while ((ch = fgetc(f)) !=
         EOF) { // llegeix fins que arriba al final del document
    assert(bufferIdx < bufferSize);
    buffer[bufferIdx++] = ch;
    if (parsingLink) {
      if (ch == ')') { // end of link
        parsingLink =
            false; // indica que deixem el link anterior i passem a un nou
        assert(linkBufferIdx < linkBufferSize);
        linkBuffer[linkBufferIdx++] = '\0';
        int linkId = atoi(linkBuffer);

        // ja hem llegit el link, per tant, l'introduim a la llista de links
        // add to links
        links->ids[links->count++] =
            linkId; // emmgatazemem l'id del link en l'apartat "ids" de la data
                    // structure

        linkBufferIdx = 0;
      } else if (ch != '(') { // skip first parenthesis of the link
        assert(linkBufferIdx < linkBufferSize);
        linkBuffer[linkBufferIdx++] = ch;
      }
    } else if (ch ==
               ']') { // found beginning of link id, e.g.: [my link text](123)
      parsingLink = true; // indica que estem llegint un link
    }
  }
  assert(bufferIdx < bufferSize);
  buffer[bufferIdx++] = '\0';

  char *body = (char *)malloc(sizeof(char) * bufferIdx);
  strcpy(body, buffer);

  document->body = (char *)malloc(sizeof(char) * (bufferIdx + 1));
  strcpy(document->body, buffer);
  // preguntar espai links data structure document

  document->links = links; // actulitzem la llista de links de la data structure
                           // document amb la que hem omplert anteriorment

  fclose(f); // tanquem el document
  return document;
}

void FreeDocument(Document *document) {
  free(document->title); // alliberem tot l'espai (dels mallocs)
  free(document->body);
  free(document->links);
  free(document);
}
