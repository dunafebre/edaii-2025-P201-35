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
    
    %% Data Structures 
    DOC["
        typedef struct {
        char *title;
        int document_id;
        char *body;
        Links *links;
        int relevance;
        } Document;"] 
    
    QUERY_LIST["typedef struct {
        QueryNode *head;
        int count;
        } QueryList;"]
    
    WORD_ENTRY["typedef struct WordEntry {
        char word[MAX_WORD_LEN];
        DocumentList *docs;    
        struct WordEntry *next;
        } WordEntry;"]

    GRAF["typedef struct {
        int **adjacency; 
        int size;        
        } DocumentGraph;"]
    

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
    style F_PARSER fill:#c8a2c8,stroke:#333,stroke-width:1px
    style F_DOCUMENTS fill:#c8a2c8,stroke:#333,stroke-width:1px
    style F_HASHMAP fill:#c8a2c8,stroke:#333,stroke-width:1px
    style F_GRAPH fill:#c8a2c8,stroke:#333,stroke-width:1px
    style F_Q_PARSER fill:#c8a2c8,stroke:#333,stroke-width:1p
    style F_RELLEVANCE fill:#c8a2c8,stroke:#333,stroke-width:1px

    %% Llegenda
    subgraph L[" Llegenda "]
        blue["Components persistents (fitxers)"]
        green["Components volàtils (memòria)"]
        purple["Funcions"]
        orange["Data Structures"]
    end

    style blue fill:#b3d9ff,stroke:#333,stroke-width:1px
    style green fill:#ccffcc,stroke:#333,stroke-width:1px
    style purple fill:#c8a2c8,stroke:#333,stroke-width:1px
    style lavanda fill:#eeedff,stroke:#333,stroke-width:1px

```
## Anàlisi de complexitat

| Descripció                                                           | Big-O       | Justificació                                                                 |
|----------------------------------------------------------------------|-------------|------------------------------------------------------------------------------|
| Parsing d’un document al `struct` (amb enllaços)                    | O(n)        | n = paraules del document; es processen una per una 
Es llegeixen totes les paraules del document una a una                        |
| Parsing d’una consulta al `struct`                                  | O(k)        | k = paraules clau de la consulta
La consulta es divideix en k paraules clau, cada una es processa un cop                                            |
| Recompte de veïns al graf global (`adjacencyList`)                  | O(V + E)    | V = documents, E = enllaços; es recorre tot el graf  
S’exploren tots els nodes (documents) i les seves connexions                       |
| Recompte de veïns d’un document                                     | O(d)        | d = grau del document; accés directe a la seva llista d’adjacència   
S’accedeix a la llista d’adjacència del document     |
| Cerca de documents amb una paraula clau (`HashMap`)                 | O(1)        |    
El `HashMap` permet accés constant per clau                                                    |
| Cerca de documents que continguin totes les paraules clau           | O(k · d)    | d = mida mitjana de la llista de documents per paraula          
Es recuperen k llistes i es comparen els documents que hi apareixen            |
| Ordenació dels documents per score de rellevància                   | O(n log n)  | n = documents candidats a ordenar                                      
Es fa sort d’una llista de m documents candidats segons el score     |







