#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <locale.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define BUFFERZIZE 1000
#define SIZE_NAME_STATION 50
#define SIZE_NAME_LIGNE 5
#define MINUTE_CONNEXION 1
#define MINUTE_CHANGEMENT_LIGNE 5
#define NB_LETTRE 26

#define STATIONS "data/stationsEdited.csv"
#define ARETES "data/aretes.csv"

/**
 * @brief Structure pour stocker les données des stations
 *
 */
typedef struct station
{
    uint32_t id;
    char nom[SIZE_NAME_STATION];
    bool estVisite;
} Station;

/**
 * @brief Structure pour stocker les données des arêtes (connexions directes)
 *
 */
typedef struct arete
{
    uint32_t origine;
    uint32_t destination;
    uint32_t poids;
    char ligne[SIZE_NAME_LIGNE];
} Arete;

/**
 * @brief Structure qui représente un élément de la liste doublement chaîné
 *
 */
typedef struct maillon
{
    Arete *arete;
    Station *stationPivot;
    Station *stationAccessible;
    struct maillon *suivant;   // Pour se déplacer en avant dans la liste
    struct maillon *precedant; // Pour se déplacer en arrière dans la liste
    uint32_t poids;            // Le poids pour se déplacer de la station pivot a la station accessible.
    char lastLigne[SIZE_NAME_LIGNE];
} Maillon;

/**
 * @brief Structure de la file nécessaire à l'algorithme
 *
 */
typedef struct liste
{
    uint32_t taille;
    uint32_t poidsTotal; // Durée totale du chemin trouvé
    Maillon *tete;
    Maillon *queue;
} Liste;

/**
 * @brief Structure pour enregistrer une requête de l'utilisateur
 *
 */
typedef struct chemin
{
    uint32_t origine;
    uint32_t destination;
} Chemin;

/**
 * @brief Structure pour enregistrer sous forme ordonne par lettre les stations
 *
 */
typedef struct tabStationsParLettres
{
    Liste **tab;
} TabStationsParLettres;

/**
 * @brief Structure pour stocker les données du graphe
 *
 */
typedef struct graphe
{
    Station **stations;
    Liste **aretes;
    uint32_t nbStations;
    uint32_t nbAretes;
    TabStationsParLettres *tabStationsParLettres;
} Graphe;

#endif