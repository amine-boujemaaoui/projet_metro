#include "../../include/structures.h"

// Fonction pour creer et allouer une station
Station *new_station()
{
    Station *station = (Station*)malloc(sizeof(Station));
    if (station == NULL)
    {
        printf("ERREUR: impossible de creer la station\n");
        exit(1);
    }
    return station;
}

// Fonction pour creer et allouer une arete
Arete *new_arete()
{
    Arete *arete = (Arete*)malloc(sizeof(Arete));
    if (arete == NULL)
    {
        printf("ERREUR: impossible de creer l'arete\n");
        exit(1);
    }
    return arete;
}

// Fonction pour creer et allouer un graphe
Graphe *new_graphe(int nbStations, int nbAretes)
{
    Graphe *graphe = (Graphe*)malloc(sizeof(Graphe));
    if (graphe == NULL)
    {
        printf("ERREUR: impossible de creer le graphe\n");
        exit(1);
    }
    graphe->stations = (Station**)malloc(nbStations * sizeof(Station*));
    if (graphe->stations == NULL)
    {
        printf("ERREUR: impossible de creer les stations du graphe\n");
        exit(1);
    }
    for (int i = 0; i < nbStations; i++)
        graphe->stations[i] = new_station();
    graphe->aretes = (Arete **)malloc(nbAretes * sizeof(Arete *));
    if (graphe->aretes == NULL)
    {
        printf("ERREUR: impossible de creer les aretes du graphe\n");
        exit(1);
    }
    for (int i = 0; i < nbAretes; i++)
    {
        graphe->aretes[i] = new_arete();
    }
    graphe->nbStations = nbStations;
    graphe->nbAretes = nbAretes;
    return graphe;
}

// Fonction pour lire les données des stations à partir d'un fichier
Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes)
{
    FILE *fichierStations = fopen(nomFichierStations, "r");
    FILE *fichierAretes = fopen(nomFichierAretes, "r");
    char tmpChar[50];
    int tmpInt, tmpInt2;
    if (fichierStations == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichierStations);
        exit(1);
    }
    if (nomFichierAretes == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichierAretes);
        exit(1);
    }
    // On compte le nombre de station dans le fichier nomFichierAretes
    int nbStations = 0;
    fscanf(fichierStations, "%[^,],%[^\n]", tmpChar, tmpChar); // on passe l'entete du fichier
    while (fscanf(fichierStations, "%[^,],%d\n", tmpChar, &tmpInt) != EOF)
        nbStations++;
    rewind(fichierStations);
    // On compte le nombre d'arrete dans le fichier nomFichierAretes
    int nbAretes = 0;
    fscanf(fichierAretes, "%[^,],%[^,],%[^\n]", tmpChar, tmpChar, tmpChar); // on passe l'entete du fichier
    while (fscanf(fichierAretes, "%d,%d,%[^\n]", &tmpInt, &tmpInt2, tmpChar) != EOF)
        nbAretes++;
    rewind(fichierAretes);
    Graphe *graphe = new_graphe(nbStations, nbAretes);
    // On charge les stations dans le graphe
    int count = 0;
    fscanf(fichierStations, "%[^,],%[^\n]", tmpChar, tmpChar); // on passe l'entete du fichier
    while (fscanf(fichierStations, "%[^,],%d\n", graphe->stations[count]->nom, &graphe->stations[count]->id) != EOF)
        count++;
    printf("c\n");
    // On charge les aretes dans le graphe
    count = 0;
    fscanf(fichierAretes, "%[^,],%[^,],%[^\n]", tmpChar, tmpChar, tmpChar); // on passe l'entete du fichier
    while (fscanf(fichierAretes, "%d,%d,%[^\n]", &graphe->aretes[count]->origine, &graphe->aretes[count]->destination, graphe->aretes[count]->ligne) != EOF)
    {
        graphe->aretes[count]->poids = MINUTE_CONNEXION;
        count++;
    }
    fclose(fichierStations);
    fclose(fichierAretes);
    return graphe;
}