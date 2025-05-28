#include <stdio.h>
#include "documents.h"
#include "consultes.h"
#include "reverse_index.h"
#include "graph.h"

int main() {
    // 1. Carregar documents
    DocumentList *docs = LoadDocumentsFromDataset();

    // 2. Construir l'índex invertit
    ReverseIndex *index = InitReverseIndex();
    BuildReverseIndex(index, docs);

    // 3. Menú principal
    int opcio;
    do {
        printf("\nMENÚ PRINCIPAL:\n");
        printf("1. Visualitzar un document\n");
        printf("2. Fer una consulta per paraules clau\n");
        printf("3. Sortir\n> ");
        scanf("%d", &opcio);

        switch (opcio) {
            case 1:
                SelectOneDoc();
                break;
            case 2:
                paraules_clau();
                break;
            case 3:
                printf("Sortint del programa.\n");
                break;
            default:
                printf("Opció no vàlida.\n");
                break;
        }
    } while (opcio != 3);

    return 0;
}

