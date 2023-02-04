#include "../../include/includes.h"

void *myMalloc(char *message, uint64_t size)
{
    void *pointeur = malloc(size);
    if (pointeur == NULL)
    {
        printf("%s\n", message);
        exit(EXIT_FAILURE);
    }
    else
        return pointeur;
}

Station *new_station()
{
    Station *station = (Station *)myMalloc("ERREUR: impossible de creer la station\n", sizeof(Station));
    station->id = 0;
    station->estVisite = false;
    return station;
}

Arete *new_arete()
{
    Arete *arete = (Arete *)myMalloc("ERREUR: impossible de creer l'arete\n", sizeof(Arete));
    arete->origine = 0;
    arete->destination = 0;
    arete->poids = 0;
    return arete;
}

Maillon *new_maillon()
{
    Maillon *maillon = (Maillon *)myMalloc("ERREUR: impossible de creer le maillon\n", sizeof(Maillon));
    maillon->arete = NULL;
    maillon->stationPivot = NULL;
    maillon->stationAccessible = NULL;
    maillon->poids = 0;
    maillon->suivant = NULL;
    maillon->precedant = NULL;
    return maillon;
}

Liste *new_liste()
{
    Liste *liste = (Liste *)myMalloc("ERREUR: impossible de creer la liste\n", sizeof(Liste));
    liste->tete = NULL;
    liste->queue = NULL;
    liste->taille = 0;
    liste->poidsTotal = 0;
    return liste;
}

Graphe *new_graphe(uint32_t nbStations, uint32_t nbAretes)
{
    Graphe *graphe = (Graphe *)myMalloc("ERREUR: impossible de creer le graphe\n", sizeof(Graphe));
    graphe->stations = (Station **)myMalloc("ERREUR: impossible de creer les stations du graphe\n", nbStations * sizeof(Station *));
    graphe->aretes = (Liste **)myMalloc("ERREUR: impossible de creer le tableau de liste d'aretes du graphe\n", nbStations * sizeof(Liste *));
    for (uint32_t i = 0; i < nbStations; i++)
    {
        graphe->stations[i] = new_station();
        graphe->aretes[i] = new_liste();
    }
    graphe->nbStations = nbStations;
    graphe->nbAretes = nbAretes;
    return graphe;
}

Chemin *new_chemin()
{
    Chemin *chemin = (Chemin *)myMalloc("ERREUR: impossible de creer le chemin\n", sizeof(Chemin));
    chemin->origine = 0;
    chemin->destination = 0;
    return chemin;
}