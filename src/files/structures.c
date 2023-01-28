#include "structures.h"

// Fonction pour lire les données des stations à partir d'un fichier
Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes)
{
    Graphe *graphe = (Graphe *)malloc(sizeof(Graphe));
    FILE *fichierStations = fopen(nomFichierStations, "r");
    if (fichierStations == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichierStations);
        exit(1);
    }
    fscanf(fichierStations, "%d", &graphe->nbStations);
    graphe->stations = (Station *)malloc(graphe->nbStations * sizeof(Station));
    for (int i = 0; i < graphe->nbStations; i++)
    {
        graphe->stations[i].id = i;
        graphe->stations[i].nom = (char *)malloc(50 * sizeof(char));
        fscanf(fichierStations, "%s", graphe->stations[i].nom);
    }
    fclose(fichierStations);
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
        fscanf(fichierAretes, "%d,%d,%d", &graphe->aretes[i].origine, &graphe->aretes[i].destination, &graphe->aretes[i].ligne);
        graphe->aretes[i].poids = MINUTE_CONNEXION;
    }
    fclose(fichierAretes);
    return graphe;
}