#include "../../include/includes.h"

void set_station(Station *station, uint32_t id, char *nom, bool estVisite)
{
    station->id = id;
    station->estVisite = estVisite;
    strcpy(station->nom, nom);
}

void set_arete(Arete *arete, uint32_t origine, uint32_t destination, uint32_t poids, char *ligne)
{
    arete->origine = origine;
    arete->destination = destination;
    arete->poids = poids;
    strcpy(arete->ligne, ligne);
}

void set_maillon(Maillon *maillon, Arete *arete, Station *stationPivot, Station *stationAccessible, Maillon *suivant, Maillon *precedant, uint32_t poids)
{
    maillon->arete = arete;
    maillon->stationPivot = stationPivot;
    maillon->stationAccessible = stationAccessible;
    maillon->suivant = suivant;
    maillon->precedant = precedant;
    maillon->poids = poids;
}