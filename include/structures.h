#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define SIZE_NAME_STATION 50
#define SIZE_NAME_LIGNE 5
#define MINUTE_CONNEXION 1
#define MINUTE_CHANGEMENT_LIGNE 5

// Structure pour stocker les données des stations
typedef struct station
{
    uint32_t id;
    char nom[SIZE_NAME_STATION];
    bool estVisite;
} Station;

// Structure pour stocker les données des arêtes (connexions directes)
typedef struct arete
{
    uint32_t origine;
    uint32_t destination;
    uint32_t poids;
    char ligne[SIZE_NAME_LIGNE];
} Arete;

// Structure qui represente un element de la liste doublement chaine
typedef struct maillon
{
    Arete *arete;
    Station *stationPivot;
    Station *stationAccessible;
    struct maillon *suivant;   // pour ce deplacer en avant dans la liste
    struct maillon *precedant; // pour ce deplacer en arriere dans la liste
    uint32_t poids;            // le poids pour ce dplacer de la station pivot a la station accesible
} Maillon;

// Structure de la file neccesaire à l'algorithme
typedef struct liste
{
    uint32_t taille;
    uint32_t poidsTotal; // durré total du chemain trouver
    Maillon *tete;
    Maillon *queue;
} Liste;

// Structure pour stocker les données du graphe
typedef struct graphe
{
    Station **stations;
    Liste **aretes;
    uint32_t nbStations;
    uint32_t nbAretes;
} Graphe;

// Fonction pour allouer de la memoire de taille size et afficher un le message message en cas d'echec
void *myMalloc(char *message, uint64_t size);
// Fonction pour creer et allouer une station
Station *new_station();
// Fonction pour instancier les variables d'une station
void set_station(Station *station, uint32_t id, char *nom, bool estVisite);
// Fonction pour creer et allouer une arete
Arete *new_arete();
// Fonction pour instancier les variables d'une arete
void set_arete(Arete *arete, uint32_t origine, uint32_t destination, uint32_t poids, char *ligne);
// Fonction pour creer et allouer un maillon
Maillon *new_maillon();
// Fonction pour instancier les variables d'un maillon
void set_maillon(Maillon *maillon, Arete *arete, Station *stationPivot, Station *stationAccessible, Maillon *suivant, Maillon *precedant, uint32_t poids);
// Fonction pour creer et allouer une liste
Liste *new_liste();
// Fonction pour creer et allouer un graphe
Graphe *new_graphe(uint32_t nbStations, uint32_t nbAretes);
// Fonction pour ajouter le maillon m en tete de la liste l
void add_tete(Liste *l, Maillon *m);
// Fonction pour ajouter le maillon m en queue de la liste l
void add_queue(Liste *l, Maillon *m);
// Fonction pour ajouter le maillon m à la position pos de la liste l
void add_position(Liste *l, Maillon *m, uint32_t pos);
// Fonction pour ajouter le maillon m à la liste l en gradant la liste trier dans l'ordre croissant de poid
void add_poidMin(Liste *l, Maillon *m);
// Fonction pour retirer le maillon en tete de la liste l
Maillon *rem_tete(Liste *l);
// Fonction pour retirer le maillon en queue de la liste l
Maillon *rem_queue(Liste *l);
// Fonction pour retirer le maillon a la position pos de la liste l
Maillon *rem_position(Liste *l, uint32_t pos);

#endif