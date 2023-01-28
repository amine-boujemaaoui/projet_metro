#include "../../include/structures.h"

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
    int count = 0; // 1 pour skip l'entete du fichier CSV
    while (fscanf(fichierStations, "%[^,],%d") != EOF)
    {
        count++;
    }
    graphe->stations = (Station *)malloc(sizeof(Station));
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

    return graphe;
}