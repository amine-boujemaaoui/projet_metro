#include "../../include/structures.h"

// Fonction pour allouer de la memoire de taille size et afficher un le message message en cas d'echec
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

// Fonction pour creer et allouer une station
Station *new_station()
{
    Station *station = (Station *)myMalloc("ERREUR: impossible de creer la station\n", sizeof(Station));
    station->id = 0;
    station->estVisite = false;
    return station;
}

// Fonction pour creer et allouer une arete
Arete *new_arete()
{
    Arete *arete = (Arete *)myMalloc("ERREUR: impossible de creer l'arete\n", sizeof(Arete));
    arete->origine = 0;
    arete->destination = 0;
    arete->poids = 0;
    return arete;
}

// Fonction pour creer et allouer un maillon
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

// Fonction pour creer et allouer une liste
Liste *new_liste()
{
    Liste *liste = (Liste *)myMalloc("ERREUR: impossible de creer la liste\n", sizeof(Liste));
    liste->tete = NULL;
    liste->queue = NULL;
    liste->taille = 0;
    liste->poidsTotal = 0;
    return liste;
}

// Fonction pour creer et allouer un graphe
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

// Fonction pour instancier les variables d'une station
void set_station(Station *station, uint32_t id, char *nom, bool estVisite)
{
    station->id = id;
    station->estVisite = estVisite;
    strcpy(station->nom, nom);
}

// Fonction pour instancier les variables d'une arete
void set_arete(Arete *arete, uint32_t origine, uint32_t destination, uint32_t poids, char *ligne)
{
    arete->origine = origine;
    arete->destination = destination;
    arete->poids = poids;
    strcpy(arete->ligne, ligne);
}

// Fonction pour instancier les variables d'un maillon
void set_maillon(Maillon *maillon, Arete *arete, Station *stationPivot, Station *stationAccessible, Maillon *suivant, Maillon *precedant, uint32_t poids)
{
    maillon->arete = arete;
    maillon->stationPivot = stationPivot;
    maillon->stationAccessible = stationAccessible;
    maillon->suivant = suivant;
    maillon->precedant = precedant;
    maillon->poids = poids;
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
