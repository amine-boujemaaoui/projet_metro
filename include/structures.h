#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "functions.h"

#define MINUTE_CONNEXION 1
#define MINUTE_CHANGEMENT_LIGNE 5

// Structure pour stocker les données des stations
typedef struct station
{
    uint32_t id;
    char nom[50];
    bool estVisite;
} Station;

// Structure pour stocker les données des arêtes (connexions directes)
typedef struct arete
{
    uint32_t origine;
    uint32_t destination;
    uint32_t poids;
    char ligne[50];
} Arete;

// Structure pour stocker les données du graphe
typedef struct graphe
{
    Station **stations;
    Arete **aretes;
    uint32_t nbStations;
    uint32_t nbAretes;
} Graphe;

// Structure qui represente un element de la liste doublement chaine
typedef struct maillon
{
    Station *stationPivot;
    Station *stationAccessible;
    uint32_t poids; // le poids pour ce dplacer de la station pivot a la station accesible
    Maillon *suivant; // pour ce deplacer en avant dans la liste
    Maillon *precedant; // pour ce deplacer en arriere dans la liste
} Maillon;

// Structure qui represente un element de la liste doublement chaine d'arete du tableau des aretes du graphe 
typedef struct maillonArete
{
    Arete *arete;
    Maillon *suivant;   // pour ce deplacer en avant dans la liste
    Maillon *precedant; // pour ce deplacer en arriere dans la liste
} MaillonArete;

// Structure de la file neccesaire à l'algorithme
typedef struct liste
{
    uint32_t taille;
    uint32_t poidsTotal; // durré total du chemain trouver
    Maillon *tete;
    Maillon *queue;
} Liste;

// Structure de la file neccesaire à l'algorithme
typedef struct listeArrete
{
    uint32_t taille;
    MaillonArete *tete;
    MaillonArete *queue;
} ListeArrete;

// Fonction pour creer et allouer une station
Station *new_station();
// Fonction pour creer et allouer une arete
Arete *new_arete();
// Fonction pour creer et allouer un maillon
Maillon *new_maillon();
// Fonction pour creer et allouer un maillon
MaillonArete *new_maillonArete();
// Fonction pour creer et allouer une liste
Liste *new_liste();
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
// Fonction pour creer et allouer un graphe
Graphe *new_graphe(uint32_t nbStations, uint32_t nbAretes);

#endif