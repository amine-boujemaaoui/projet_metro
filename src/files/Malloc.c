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
    Station *station = (Station *)myMalloc("\033[0;31mERREUR : impossible de créer la station !\033[0m\n", sizeof(Station));
    station->id = 0;
    station->estVisite = false;
    return station;
}

Arete *new_arete()
{
    Arete *arete = (Arete *)myMalloc("\033[0;31mERREUR : impossible de créer l'arête !\033[0m\n", sizeof(Arete));
    arete->origine = 0;
    arete->destination = 0;
    arete->poids = 0;
    return arete;
}

Maillon *new_maillon()
{
    Maillon *maillon = (Maillon *)myMalloc("\033[0;31mERREUR : impossible de créer le maillon !\033[0m\n", sizeof(Maillon));
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
    Liste *liste = (Liste *)myMalloc("\033[0;31mERREUR : impossible de créer la liste !\033[0m\n", sizeof(Liste));
    liste->tete = NULL;
    liste->queue = NULL;
    liste->taille = 0;
    liste->poidsTotal = 0;
    return liste;
}

Graphe *new_graphe(uint32_t nbStations, uint32_t nbAretes)
{
    Graphe *graphe = (Graphe *)myMalloc("\033[0;31mERREUR : impossible de créer le graphe !\033[0m\n", sizeof(Graphe));
    graphe->stations = (Station **)myMalloc("\033[0;31mERREUR : impossible de créer les stations du graphe !\033[0m\n", nbStations * sizeof(Station *));
    graphe->aretes = (Liste **)myMalloc("\033[0;31mERREUR : impossible de créer le tableau de liste d'arêtes du graphe !\033[0m\n", nbStations * sizeof(Liste *));
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
    Chemin *chemin = (Chemin *)myMalloc("\033[0;31mERREUR : impossible de créer le chemin !\033[0;31m\n", sizeof(Chemin));
    chemin->origine = 0;
    chemin->destination = 0;
    return chemin;
}