# Report: Building a search engine like Google
## Diagrama de components (C4) 

```mermaid
flowchart TD

    %% Fonts d'entrada
    UI[User Input<br/>(consultes)]
    FILE[documents.txt<br/>(persistent)]

    %% Components del sistema
    PARSER[Document Parser<br/>(crea structs)]
    DOCS[Documents (Struct)<br/>(volàtil)]
    GRAPH[Graph<br/>(adjacency list)]
    INDEX[Reverse Index (HashMap)]
    QPARSER[Query Parser]
    SEARCH[Search Engine<br/>(filtra i ordena)]
    OUTPUT[Resultats a terminal]

    %% Connexions
    FILE --> PARSER
    PARSER --> DOCS
    PARSER --> GRAPH
    PARSER --> INDEX
    UI --> QPARSER
    QPARSER --> SEARCH
    INDEX --> SEARCH
    GRAPH --> SEARCH
    DOCS --> SEARCH
    SEARCH --> OUTPUT

    %% Colors
    style FILE fill:#b3d9ff,stroke:#333,stroke-width:1px
    style DOCS fill:#ccffcc,stroke:#333,stroke-width:1px
    style GRAPH fill:#ccffcc,stroke:#333,stroke-width:1px
    style INDEX fill:#ccffcc,stroke:#333,stroke-width:1px
    style PARSER fill:#ccffcc,stroke:#333,stroke-width:1px
    style QPARSER fill:#ccffcc,stroke:#333,stroke-width:1px
    style SEARCH fill:#ccffcc,stroke:#333,stroke-width:1px
    style OUTPUT fill:#ccffcc,stroke:#333,stroke-width:1px
    style UI fill:#b3d9ff,stroke:#333,stroke-width:1px


---

### 🧠 Llegenda visual (si vols afegir-la després del diagrama)

- Color **blau clar** (`#b3d9ff`) → **Components persistents** (fitxers, input extern)
- Color **verd clar** (`#ccffcc`) → **Components en memòria** (estructures, funcions, dades)

---


