# Report: Building a search engine like Google
## Diagrama de components (C4) 

```mermaid
flowchart TD

    %% Fonts d'entrada
    UI["User Input"]
    FILE["documents.txt (Fitxer d’entrada que conté el contingut de tots els documents)"]

    %% Components del sistema
    PARSER["Document Parser (Processa els documents, separa les paraules, i construeix els documents amb la informació necessària)"]
    DOCS["Documents (Linked list dels documents carregats)"]
    GRAPH["Graph (Graf on cada node representa un document i les arestes representen enllaços entre ells)"]
    INDEX["HashMap (Índex que mapeja cada paraula clau a una llista de documents que la contenen)"]
    QPARSER["Query Parser (Pren les paraules clau i les prepara per a la cerca)"]
    SEARCH["Search Words (Filtra els documents que contenen totes les paraules clau alhora)"]
    RELLEVANCE["Rellevance (Mostra per pantalla els documents més rellevants, ordenats)"]

    %% Funcions
    F_PARSER["Document *document_desserialize(char *path)"]
    F_DOCUMENTS["DocumentList *LoadDocumentsFromDataset()"]
    F_HASHMAP["BuildHashMap(ReverseIndex *index, DocumentList *docs)"]
    F_GRAPH["BuildGraphFromDocuments(DocumentGraph *graph, DocumentList *docs)"]
    F_Q_PARSER["ExtractWords(ReverseIndex *index, Document *doc, const char *text)"]
    F_RELLEVANCE["CalculateRelevance(DocumentGraph *graph, DocumentList *docs)"]
    

    %% Connexions
    FILE --> PARSER
    PARSER --> F_PARSER
    PARSER --> DOCS
    PARSER --> GRAPH
    PARSER --> INDEX
    UI --> QPARSER
    QPARSER --> SEARCH
    QPARSER --> F_Q_PARSER
    INDEX --> SEARCH
    INDEX --> F_HASHMAP
    GRAPH --> SEARCH
    GRAPH --> F_GRAPH
    DOCS --> SEARCH
    DOCS --> F_DOCUMENTS
    SEARCH --> RELLEVANCE
    SEARCH --> F_RELLEVANCE

    %% Colors
    style FILE fill:#b3d9ff,stroke:#333,stroke-width:1px
    style DOCS fill:#ccffcc,stroke:#333,stroke-width:1px
    style GRAPH fill:#ccffcc,stroke:#333,stroke-width:1px
    style INDEX fill:#ccffcc,stroke:#333,stroke-width:1px
    style PARSER fill:#ccffcc,stroke:#333,stroke-width:1px
    style QPARSER fill:#ccffcc,stroke:#333,stroke-width:1px
    style SEARCH fill:#ccffcc,stroke:#333,stroke-width:1px
    style RELLEVANCE fill:#ccffcc,stroke:#333,stroke-width:1px
    style UI fill:#b3d9ff,stroke:#333,stroke-width:1px

    %% Llegenda
    subgraph L[ Llegenda ]
        blue[Components persistents (fitxers)]
        green[Components volàtils (memòria)]
        purple[Funcions]
    end

    style blue fill:#b3d9ff,stroke:#333,stroke-width:1px
    style green fill:#ccffcc,stroke:#333,stroke-width:1px
    style purple fill:#c8a2c8,stroke:#333,stroke-width:1px





