# Report: Building a search engine like Google
## Diagrama de components (C4) 

```mermaid
flowchart TD

    %% Fonts d'entrada
    UI["User Input (consultes)"]
    FILE["documents.txt (persistent)"]

    %% Components del sistema
    PARSER["Document Parser (crea structs)"]
    DOCS["Documents (Struct - volàtil)"]
    GRAPH["Graph (adjacency list - volàtil)"]
    INDEX["Reverse Index (HashMap - volàtil)"]
    QPARSER["Query Parser"]
    SEARCH["Search Engine (filtra i ordena)"]
    OUTPUT["Resultats a terminal"]

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

- Color **blau clar** (`#b3d9ff`) → **Components persistents** (fitxers, input extern)
- Color **verd clar** (`#ccffcc`) → **Components en memòria** (estructures, funcions, dades)

---


