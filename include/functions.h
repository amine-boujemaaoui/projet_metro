#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "structures.h"

/**
 * @brief Fonction pour allouer de la memoire de taille size et afficher un le message message en cas d'echec
 *
 * @param message le message d'erreur
 * @param size la taille a alouer par le malloc
 * @return void*
 */
void *myMalloc(char *message, uint64_t size);

/**
 * @brief Fonction pour creer et allouer une station
 *
 * @return Station*
 */
Station *new_station();

/**
 * @brief Fonction pour affecter les variables à une station
 *
 * @param station la station à initialiser
 * @param id l'id à affecter à la station
 * @param nom le nom a affecter a la station
 * @param estVisite definit si la station est visite
 */
void set_station(Station *station, uint32_t id, char *nom, bool estVisite);

/**
 * @brief Fonction pour creer et allouer une arete
 *
 * @return Arete*
 */
Arete *new_arete();

/**
 * @brief Fonction pour affecter les variables à une arete
 *
 * @param arete l'arrete à initialiser
 * @param origine l'origine à affecter à l'arete
 * @param destination la destination à affecter à l'arete
 * @param poids le poids à affecter à l'arete
 * @param ligne la ligne à affecter à l'arete
 */
void set_arete(Arete *arete, uint32_t origine, uint32_t destination, uint32_t poids, char *ligne);

/**
 * @brief Fonction pour creer et allouer un maillon
 *
 * @return Maillon*
 */
Maillon *new_maillon();

/**
 * @brief Fonction pour affecter les variables à maillon
 *
 * @param maillon le maillon initialiser
 * @param arete l'arete à affecter au maillon
 * @param stationPivot la stationpivot|station à affecter au maillon
 * @param stationAccessible la stationAccessible à affecter au maillon
 * @param suivant le maillon suivant dans la liste ou est present le maillon
 * @param precedant le maillon precedant dans la liste ou est present le maillon
 * @param poids
 */
void set_maillon(Maillon *maillon, Arete *arete, Station *stationPivot, Station *stationAccessible, Maillon *suivant, Maillon *precedant, uint32_t poids);

/**
 * @brief Fonction pour creer et allouer une liste
 *
 * @return Liste*
 */
Liste *new_liste();

/**
 * @brief Fonction pour creer et allouer un graphe
 *
 * @param nbStations le nombre de stations à charger
 * @param nbAretes le nombre de aretes à charger
 * @return Graphe*
 */
Graphe *new_graphe(uint32_t nbStations, uint32_t nbAretes);

/**
 * @brief Fonction pour ajouter le maillon m en tete de la liste l
 *
 * @param l la liste à laquel on ajoute un maillon
 * @param m le maillon que l'on ajoute en tete de la liste
 */
void add_tete(Liste *l, Maillon *m);

/**
 * @brief Fonction pour ajouter le maillon m en queue de la liste l
 *
 * @param l la liste à laquel on ajoute un maillon
 * @param m le maillon que l'on ajoute en queue de la liste
 */
void add_queue(Liste *l, Maillon *m);

/**
 * @brief Fonction pour ajouter le maillon m à la position pos de la liste l
 *
 * @param l la liste à laquel on ajoute un maillon
 * @param m le maillon que l'on ajoute en posotion pos de la liste
 * @param pos la position a laquel on ajoute le maillon
 */
void add_position(Liste *l, Maillon *m, uint32_t pos);

/**
 * @brief Fonction pour ajouter le maillon m à la liste l en gradant la liste trier dans l'ordre croissant de poid
 *
 * @param l la liste à laquel on ajoute un maillon
 * @param m le maillon que l'on ajoute en posotion pos de la liste
 */
void add_poidMin(Liste *l, Maillon *m);

/**
 * @brief Fonction pour retirer le maillon en tete de la liste l
 *
 * @param l la liste à laquel on retire le maillon en tete
 * @return Maillon*
 */
Maillon *rem_tete(Liste *l);

/**
 * @brief Fonction pour retirer le maillon en queue de la liste l
 *
 * @param l la liste à laquel on retire le maillon en queue
 * @return Maillon*
 */
Maillon *rem_queue(Liste *l);

/**
 * @brief Fonction pour retirer le maillon a la position pos de la liste l
 *
 * @param l la liste à laquel on retire le maillon
 * @param pos la position a laquel on retire le maillon
 * @return Maillon*
 */
Maillon *rem_position(Liste *l, uint32_t pos);

/**
 * @brief Fonction pour creer et allouer un tabStations
 *
 * @return TabStationsParLettres*
 */
TabStationsParLettres *new_tabStationsParLettres();

/**
 * @brief Fonction pour creer et allouer un chemain
 *
 * @return Chemain*
 */
Chemain *new_chemain();

/**
 * @brief Fonction pour initialiser un nouveau chemain par l'utilisateur
 *
 * @param graphe le graphe ou sont disponible les stations
 * @return Chemain*
 */
Chemain *init_chemain(Graphe *graphe);

/**
 * @brief Fonction pour lire les données des stations à partir d'un fichier
 *
 * @param nomFichierStations le fichier ou sont les stations
 * @param nomFichierAretes le fichier ou sont les aretes
 * @return Graphe*
 */
Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes);

/**
 * @brief Fonction pour afficher le tableau des station par lettre
 *
 * @param tabStationsParLettres le tableau des stations par lettre à afficher
 */
void afficher_tabStations(TabStationsParLettres *tabStationsParLettres);

/**
 * @brief Fonction pour afficher le tableau des station par lettre pour une lettre choisi
 *
 * @param tabStationsParLettres le tableau des stations par lettre à afficher
 * @param lettre la lettre choisi
 */
void afficher_tabStationsParLettre(TabStationsParLettres *tabStationsParLettres, char lettre);

#endif