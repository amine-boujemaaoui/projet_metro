#include "../../include/structures.h"

// Fonction pour creer et allouer une station
Station *new_station()
{
    Station *station = (Station *)malloc(sizeof(Station));
    assert(station != NULL);
    station->id = NULL;
    station->nom = NULL;
    return station;
}

// Fonction pour creer et allouer une arete
Arete *new_arete()
{
    Arete *arete = (Arete *)malloc(sizeof(Arete));
    assert(arete != NULL);
    arete->origine = NULL;
    arete->destination = NULL;
    arete->ligne = NULL;
    arete->poids = NULL;
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
    {
        graphe->stations[i] = new_station();
    }
    graphe->aretes = (Arete **)malloc(nbStations * sizeof(Arete *));
    assert(graphe->aretes != NULL);
    for (int i = 0; i < nbAretes; i++)
    {
        graphe->aretes[i] = new_arete();
    }
    graphe->nbStations = nbStations;
    graphe->nbAretes = nbAretes;
    return graphe;
}

// Fonction pour lire les données des stations à partir d'un fichier
void chargerGraphe(Graphe *graphe, char *nomFichierStations, char *nomFichierAretes)
{
    FILE *fichierStations = fopen(nomFichierStations, "r");
    FILE *fichierAretes = fopen(nomFichierAretes, "r");
    if (fichierStations == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichierStations);
        exit(1);
    }
    int nbStations = 0;
    while (fscanf(fichierStations, "%[^,],%d") != EOF)
    {
        nbStations++;
    }
    nbStations--; // On ne compte pas la premier ligne du fichier qui est l'entete
    int nbAretes = 0;
    while (fscanf(fichierAretes, "%[^,],%d") != EOF)
    {
        nbAretes++;
    }
    nbAretes--; // On ne compte pas la premier ligne du fichier qui est l'entete

    Graphe *graphe = new_graphe();
    for (int i = 0; i < count; i++)
    {
        graphe->stations[i] = (Station *)malloc(sizeof(Station));
    }
    while (fscanf(fichierStations, "%[^,],%d", graphe->stations[count].nom, &graphe->stations[count].id) != EOF)
    {
        count++;
    }
    // rewind(fichierStations);
    fclose(fichierStations);
    graphe->nbStations = count;

    /*
    fscanf(fichierStations, "%d", &graphe->nbStations);
    graphe->stations = (Station *)malloc(graphe->nbStations * sizeof(Station));
    for (int i = 0; i < graphe->nbStations; i++)
    {
        graphe->stations[i].id = i;
        graphe->stations[i].nom = (char *)malloc(50 * sizeof(char));
        fscanf(fichierStations, "%d,%[^\n]", &graphe->stations[i].id, &graphe->stations[i].nom);
    }
    fclose(fichierStations);
    */

    /*
    FILE *fichierAretes = fopen(nomFichierAretes, "r");
    if (fichierAretes == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichierAretes);
        exit(1);
    }
    fscanf(fichierAretes, "%d", &graphe->nbAretes);
    graphe->aretes = (Arete *)malloc(graphe->nbAretes * sizeof(Arete));
    for (int i = 0; i < graphe->nbAretes; i++)
    {
        fscanf(fichierAretes, "%d,%d,%s", &graphe->aretes[i].origine, &graphe->aretes[i].destination, &graphe->aretes[i].ligne);
        graphe->aretes[i].poids = MINUTE_CONNEXION;
    }
    fclose(fichierAretes);
    */
}