#include "../../include/structures.h"

// Fonction pour creer et allouer une station
Station *new_station()
{
    Station *station = (Station *)malloc(sizeof(Station));
    assert(station != NULL);
    return station;
}

// Fonction pour creer et allouer une arete
Arete *new_arete()
{
    Arete *arete = (Arete *)malloc(sizeof(Arete));
    assert(arete != NULL);
    return arete;
}

// Fonction pour creer et allouer un graphe
Graphe *new_graphe(int nbStations, int nbAretes)
{
    Graphe *graphe = (Graphe *)malloc(sizeof(Graphe));
    assert(graphe != NULL);
    graphe->stations = (Station **)malloc(nbStations * sizeof(Station *));
    assert(graphe->stations != NULL);
    for (int i = 0; i < nbStations; i++)
        graphe->stations[i] = new_station();
    graphe->aretes = (Arete **)malloc(nbStations * sizeof(Arete *));
    assert(graphe->aretes != NULL);
    for (int i = 0; i < nbAretes; i++)
        graphe->aretes[i] = new_arete();
    graphe->nbStations = nbStations;
    graphe->nbAretes = nbAretes;
    return graphe;
}

// Fonction pour lire les données des stations à partir d'un fichier
Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes)
{
    FILE *fichierStations = fopen(nomFichierStations, "r");
    FILE *fichierAretes = fopen(nomFichierAretes, "r");
    char *tmpChar;
    int tmpInt;
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
    while (fscanf(fichierStations, "%[^,],%d\n", tmpChar, ) != EOF)
    {
        nbStations++;
        printf("%d\n", nbStations);
    }
    nbStations--; // On ne compte pas la premier ligne du fichier qui est l'entete
    rewind(fichierStations);

    // On compte le nombre d'arrete dans le fichier nomFichierAretes
    int nbAretes = 0;
    while (fscanf(fichierAretes, "\n") != EOF)
        nbAretes++;
    nbAretes--; // On ne compte pas la premier ligne du fichier qui est l'entete
    rewind(fichierAretes);

    Graphe *graphe = new_graphe(nbStations, nbAretes);
    int count = 0;

    // On charge les stations dans le graphe
    while (fscanf(fichierStations, "%[^,],%d", graphe->stations[count]->nom, &graphe->stations[count]->id) != EOF)
        count++;

    // On charge les aretes dans le graphe
    count = 0;
    while (fscanf(fichierAretes, "%d,%d,%[^\n]\n", &graphe->aretes[count]->origine, &graphe->aretes[count]->destination, graphe->aretes[count]->ligne) != EOF)
        count++;

    fclose(fichierStations);
    fclose(fichierAretes);

    return graphe;
}