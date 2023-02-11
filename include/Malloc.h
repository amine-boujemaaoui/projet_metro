#ifndef __MALLOC_H__
#define __MALLOC_H__

#include "Struct.h"

/**
 * @brief Fonction pour allouer de la mémoire de taille size et afficher un le message message en cas d'échec
 *
 * @param message Le message d'erreur
 * @param size La taille a alloué par le malloc
 * @return void*
 */
void *myMalloc(char *message,
               uint64_t size);

/**
 * @brief Fonction pour créer et allouer une station
 *
 * @return Station*
 */
Station *new_station();

/**
 * @brief Fonction pour créer et allouer une arête
 *
 * @return Arete*
 */
Arete *new_arete();

/**
 * @brief Fonction pour créer et allouer un maillon
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
 * @brief Fonction pour créer et allouer un graphe
 *
 * @param nbStations Le nombre de stations à charger
 * @param nbAretes Le nombre d'arêtes à charger
 * @return Graphe*
 */
Graphe *new_graphe(uint32_t nbStations,
                   uint32_t nbAretes);

/**
 * @brief Fonction pour créer et allouer un chemin
 *
 * @return Chemin*
 */
Chemin *new_chemin();

/**
 * @brief Fonction pour créer et allouer un tabStations
 *
 * @return TabStationsParLettres*
 */
TabStationsParLettres *new_tabStationsParLettres();

#endif