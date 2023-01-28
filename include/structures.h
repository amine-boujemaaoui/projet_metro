#ifndef __STRUCTURES._H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <stdlib.h>

#define MINUTE_CONNEXION 1
#define MINUTE_CHANGEMENT_LIGNE 5

// Structure pour stocker les données des stations
typedef struct station
{
    int id;
    char *nom;
} Station;

// Structure pour stocker les données des arêtes (connexions directes)
typedef struct arete
{
    int origine;
    int destination;
    char *ligne;
    int poids;
} Arete;

// Structure pour stocker les données du graphe
typedef struct graphe
{
    int nbStations;
    Station *stations;
    int nbAretes;
    Arete *aretes;
} Graphe;

Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes);

#endif