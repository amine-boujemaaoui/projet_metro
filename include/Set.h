#ifndef __SET_H__
#define __SET_H__

#include "Struct.h"

/**
 * @brief Fonction pour affecter les variables à une station
 *
 * @param station La station à initialiser
 * @param id L'id à affecter à la station
 * @param nom Le nom a affecté à la station
 * @param estVisite Définis si la station est visitée
 */
void set_station(Station *station,
                 uint32_t id,
                 char *nom,
                 bool estVisite);

/**
 * @brief Fonction pour affecter les variables à une arête
 *
 * @param arete L'arête à initialiser
 * @param origine L'origine à affecter à l'arête
 * @param destination La destination à affecter à l'arête
 * @param poids Le poids à affecter à l'arête
 * @param ligne La ligne à affecter à l'arête
 */
void set_arete(Arete *arete,
               uint32_t origine,
               uint32_t destination,
               uint32_t poids,
               char *ligne);

/**
 * @brief Fonction pour affecter les variables à maillon
 *
 * @param maillon Le maillon initialisé
 * @param arete L'arête à affecter au maillon
 * @param stationPivot La stationPivot/station à affecter au maillon
 * @param stationAccessible La stationAccessible à affecter au maillon
 * @param suivant Le maillon suivant dans la liste ou est présent le maillon
 * @param precedant Le maillon précédant dans la liste ou est présent le maillon
 * @param poids Le poids pour arriver a cette station
 * @param lastLigne Le poids pour arriver a cette station
 */
void set_maillon(Maillon *maillon,
                 Arete *arete, Station *stationPivot,
                 Station *stationAccessible,
                 Maillon *suivant,
                 Maillon *precedant,
                 uint32_t poids,
                 char *lastLigne);

/**
 * @brief Va initialiser toutes les stations du graphe à non visiter.
 *
 * @param graphe Le graphe a initialisé
 */
void set_allNonVisite(Graphe *graphe);

#endif