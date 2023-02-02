#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "Struct.h"

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
 * @brief Fonction pour creer et allouer une arete
 *
 * @return Arete*
 */
Arete *new_arete();

/**
 * @brief Fonction pour creer et allouer un maillon
 *
 * @return Maillon*
 */
Maillon *new_maillon();

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
 * @brief Fonction pour creer et allouer un chemain
 *
 * @return Chemain*
 */
Chemain *new_chemain();

/**
 * @brief Fonction pour creer et allouer un tabStations
 *
 * @return TabStationsParLettres*
 */
TabStationsParLettres *new_tabStationsParLettres();

#endif