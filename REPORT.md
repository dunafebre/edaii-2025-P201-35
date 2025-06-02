# Report: Building a search engine like Google
## Diagrama de components (C4) 

```mermaid
flowchart TD

    %% Fonts d'entrada
    UI["User Input (Entrada de l’usuari a través del teclat amb la tria d'una opció del menú i una consulta (query) de paraules clau)"]
    FILE["documents.txt (Fitxer d’entrada que conté el contingut de tots els documents. És llegit a l’inici per construir les estructures internes)"]

    %% Components del sistema
    PARSER["Document Parser (Processa els documents, separa les paraules, i construeix els structs Document amb la informació necessària (text, ID, enllaços))"]
    DOCS["Documents (Array de structs en memòria que contenen tota la informació dels documents carregats)"]
    GRAPH["Graph (Estructura de graf (llista d’adjacència) on cada node representa un document i les arestes representen enllaços entre documents)"]
    INDEX["HashMap (Índex que mapeja cada paraula clau a una llista de documents que la contenen. Optimitza la cerca per paraules)"]
    QPARSER["Query Parser (Divideix la consulta de l’usuari en paraules clau i les prepara per a la cerca)"]
    SEARCH["Search Words (Filtra els documents que contenen totes les paraules clau i calcula una puntuació de rellevància)"]
    RELLEVANCE["Rellevance (Mostra per pantalla la llista de documents més rellevants ordenats per score)"]

    %% Funcions
    F_PARSER["Document *document_desserialize(char *path): "]
    F_DOCUMENTS["DocumentList *LoadDocumentsFromDataset(): "]
    F_HASHMAP["BuildHashMap(ReverseIndex *index, DocumentList *docs): "]
    F_GRAPH["BuildGraphFromDocuments(DocumentGraph *graph, DocumentList *docs): Graf orientat implementat com una llista d’adjacència, on cada node és un document i les llistes apunten als seus veïns segons els enllaços del text"]
    F_Q_PARSER["ExtractWords(ReverseIndex *index, Document *doc, const char *text): "]
    F_RELLEVANCE["CalculateRelevance(DocumentGraph *graph, DocumentList *docs): "]
    

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





