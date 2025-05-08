#include "documents.h"
#include <stdio.h>

int main() {
  Document *document = document_desserialize("datasets/wikipedia12/0.txt");
  printf("%d\n", document->document_id);
  FreeDocument(document);
  return 0;
}

// pROVA MARTA