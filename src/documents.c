#include "documents.h"
#include <assert.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// lab01

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

DocumentList *InitDocumentList() { // inicialitzem la llista enllaçada de doc
  DocumentList *llista = malloc(sizeof(DocumentList)); // creem l'espai
  llista->primer = NULL; // encara no hi ha cap doc a la llista
  llista->count = 0;
  return llista;
}

void AddDocument(
    DocumentList *list,
    Document *doc) { // funció que afegeix un document a la llista de doc
  // comprovem si ja hi és
  for (DocumentNode *node = list->primer; node != NULL; node = node->next) {
    if (node->doc->document_id == doc->document_id) {
      return; // ja hi és, no cal afegir-lo
    }
  }
  DocumentNode *node =
      malloc(sizeof(DocumentNode)); // creem l'espai per al node
  node->doc = doc;                  // el punter doc apuntarà al document
  node->next = list->primer; // el punter next apuntarà al primer doc, que ara
                             // serà el segon
  list->primer =
      node; // actualitzem la primera posició de la llista com el nou doc
  list->count++;
}

DocumentList *LoadDocumentsFromDataset() { // funció que carrega els documents
                                           // de la carpeta "datasets"
  char path[200]; // creem una array on guardarem els directoris, carpetes on
                  // estan els arxius wikipedia
  DocumentList *list = InitDocumentList(); // inicialitzem la llista de
                                           // documents
  for (int i = 12; i >= 0; i--) {
    sprintf(
        path, "datasets/wikipedia12/%d.txt",
        i); // copiem en l'array de directoris els noms per accedir als arxius
    Document *doc = document_desserialize(
        path); // convertim els documents a la datastructure Document
    AddDocument(list, doc); // afegim cada document convertit
  }
  return list;
}

void SelectOneDoc() { // funció que permet a l'usuari llegir els documents
  int DocumentSeleccionat;
  DocumentList *list =
      LoadDocumentsFromDataset(); // la llista que retorna la funció anterior la
                                  // guardem en la forma de la data structure
                                  // DocumentList

  int index = 0;
  for (DocumentNode *node = list->primer; node != NULL;
       node = node->next) { // inicialitzem un document anomenat node i anem
                            // iterant passant pels "next"
    printf("[%d] %s\n", index,
           node->doc->title); // imprimim els titols de tots els documents per a
                              // que l'usuari els pugui llegir
    index++;
  }

  printf(
      "Selecciona el document que vols visualitzar: "); // preguntem a l'usuari
                                                        // quin doc escull, pel
                                                        // seu índex
  scanf("%d", &DocumentSeleccionat);

  index = 0;
  for (DocumentNode *node = list->primer;
       node != NULL; // tornema iterar sobre els documents
       node = node->next, index++) {
    if (index == (DocumentSeleccionat)) { // quan trobem el document seleccionat
      printf("ID: %d\n",
             node->doc->document_id); // imprimim el seu títol, ID i cos
      printf("Títol: %s\n", node->doc->title);
      printf("Cos:\n%s\n", node->doc->body);
      return;
    }
  }
  printf("Index no vàlid.\n");
}
