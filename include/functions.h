#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "structures.h"

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
// Fonction pour creer et allouer un tabStations
TabStationsParLettres *new_tabStationsParLettres();
// Fonction pour creer et allouer un chemain
Chemain *new_chemain();
// Fonction pour initialiser un nouveau chemain par l'utilisateur
Chemain *init_chemain(Graphe *graphe);
// Fonction pour lire les données des stations à partir d'un fichier
Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes);
// Fonction pour afficher le tableau des station par lettre
void afficher_tabStations(TabStationsParLettres *tabStationsParLettres);
// Fonction pour afficher le tableau des station par lettre
void afficher_tabStationsParLettre(TabStationsParLettres *tabStationsParLettres, char lettre);

#endif