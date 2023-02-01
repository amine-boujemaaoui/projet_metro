#include "../../include/structures.h"

// Fonction pour creer et allouer une station
Station *new_station()
{
    Station *station = (Station *)malloc(sizeof(Station));
    if (station == NULL)
    {
        printf("ERREUR: impossible de creer la station\n");
        exit(EXIT_FAILURE);
    }
    return station;
}

// Fonction pour creer et allouer une arete
Arete *new_arete()
{
    Arete *arete = (Arete *)malloc(sizeof(Arete));
    if (arete == NULL)
    {
        printf("ERREUR: impossible de creer l'arete\n");
        exit(EXIT_FAILURE);
    }
    return arete;
}

// Fonction pour creer et allouer un maillon
Maillon *new_maillon()
{
    Maillon *maillon = (Maillon *)malloc(sizeof(Maillon));
    if (maillon == NULL)
    {
        printf("ERREUR: impossible de creer le maillon\n");
        exit(EXIT_FAILURE);
    }
    maillon->stationPivot = NULL;
    maillon->stationAccessible = NULL;
    maillon->poids = 0;
    maillon->suivant = NULL;
    maillon->precedant = NULL;
    return maillon;
}

// Fonction pour creer et allouer une liste
Liste *new_liste()
{
    Liste *liste = (Liste *)malloc(sizeof(Liste));
    if (liste == NULL)
    {
        printf("ERREUR: impossible de creer la liste\n");
        exit(EXIT_FAILURE);
    }
    liste->tete = NULL;
    liste->queue = NULL;
    liste->taille = 0;
    liste->poidsTotal = 0;
    return liste;
}

// Fonction pour ajouter le maillon m en tete de la liste l
void add_tete(Liste *l, Maillon *m)
{
    m->suivant = l->tete;
    m->precedant = NULL;
    if (l->taille == 0)
        l->queue = m;
    else
        l->tete->precedant = m;
    l->tete = m;
    l->taille++;
}

// Fonction pour ajouter le maillon m en queue de la liste l
void add_queue(Liste *l, Maillon *m)
{
    m->suivant = NULL;
    m->precedant = l->queue;
    if (l->taille > 0)
        l->queue->suivant = m;
    else
        l->tete = m;
    l->queue = m;
    l->taille++;
}

// Fonction pour ajouter le maillon m à la position pos de la liste l
void add_position(Liste *l, Maillon *m, uint32_t pos)
{
    Maillon *precedant, *suivant;
    if (pos > l->taille)
    {
        printf("ERREUR: tentative d'ajout à une position en dehors de la liste\n");
        exit(EXIT_FAILURE);
    }
    else if (pos == 0)
        add_tete(l, m);
    else if (pos == l->taille)
        add_queue(l, m);
    else
    {
        precedant = l->tete;
        for (uint32_t i = 0; i < pos - 1; i++)
            precedant = precedant->suivant;
        suivant = precedant->suivant;
        precedant->suivant = m;
        m->suivant = suivant;
        suivant->precedant = m;
        m->precedant = precedant;
        l->taille++;
    }
}

// Fonction pour ajouter le maillon m à la liste l en gradant la liste trier dans l'ordre croissant de poid
void add_poidMin(Liste *l, Maillon *m)
{
    uint32_t pos = 0;
    Maillon *maillon = l->tete;
    while (m->poids > maillon->poids && maillon->suivant != NULL)
    {
        maillon = maillon->suivant;
        pos++;
    }
    add_position(l, m, pos);
}

// Fonction pour retirer le maillon en tete de la liste l
Maillon *rem_tete(Liste *l)
{
    Maillon *maillon = l->tete;
    l->tete = l->tete->suivant;
    l->taille--;
    if (l->taille == 0)
        l->queue = NULL;
    else
        l->tete->precedant = NULL;
    return maillon;
}

// Fonction pour retirer le maillon en queue de la liste l
Maillon *rem_queue(Liste *l)
{
    Maillon *maillon = l->queue;
    l->queue = l->queue->precedant;
    l->taille--;
    if (l->taille == 0)
        l->tete = NULL;
    else
        l->queue->suivant = NULL;
    return maillon;
}

// Fonction pour retirer le maillon a la position pos de la liste l
Maillon *rem_position(Liste *l, uint32_t pos)
{
    Maillon *maillon, *precedant, *suivant;
    if (pos >= l->taille)
    {
        printf("ERREUR: tentative de suppression à une position en dehors de la liste\n");
        exit(EXIT_FAILURE);
    }
    else if (pos == 0)
        return rem_tete(l);
    else if (pos == l->taille - 1)
        return rem_queue(l);
    else
    {
        maillon = l->tete;
        for (uint32_t i = 0; i < pos; i++)
            maillon = maillon->suivant;
        precedant = maillon->precedant;
        suivant = maillon->suivant;
        precedant->suivant = suivant;
        suivant->precedant = precedant;
        l->taille--;
        return maillon;
    }
}

// Fonction pour creer et allouer un graphe
Graphe *new_graphe(uint32_t nbStations, uint32_t nbAretes)
{
    Graphe *graphe = (Graphe *)malloc(sizeof(Graphe));
    if (graphe == NULL)
    {
        printf("ERREUR: impossible de creer le graphe\n");
        exit(EXIT_FAILURE);
    }
    graphe->stations = (Station **)malloc(nbStations * sizeof(Station *));
    if (graphe->stations == NULL)
    {
        printf("ERREUR: impossible de creer les stations du graphe\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < nbStations; i++)
        graphe->stations[i] = new_station();
    graphe->aretes = (Arete **)malloc(nbAretes * sizeof(Arete *));
    if (graphe->aretes == NULL)
    {
        printf("ERREUR: impossible de creer les aretes du graphe\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < nbAretes; i++)
    {
        graphe->aretes[i] = new_arete();
    }
    graphe->nbStations = nbStations;
    graphe->nbAretes = nbAretes;
    return graphe;
}