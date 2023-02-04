#ifndef __SET_H__
#define __SET_H__

#include "Struct.h"

/**
 * @brief Fonction pour affecter les variables à une station
 *
 * @param station la station à initialiser
 * @param id l'id à affecter à la station
 * @param nom le nom a affecter a la station
 * @param estVisite definit si la station est visite
 */
void set_station(Station *station,
                 uint32_t id,
                 char *nom,
                 bool estVisite);

/**
 * @brief Fonction pour affecter les variables à une arete
 *
 * @param arete l'arrete à initialiser
 * @param origine l'origine à affecter à l'arete
 * @param destination la destination à affecter à l'arete
 * @param poids le poids à affecter à l'arete
 * @param ligne la ligne à affecter à l'arete
 */
void set_arete(Arete *arete,
               uint32_t origine,
               uint32_t destination,
               uint32_t poids,
               char *ligne);

/**
 * @brief Fonction pour affecter les variables à maillon
 *
 * @param maillon le maillon initialiser
 * @param arete l'arete à affecter au maillon
 * @param stationPivot la stationpivot|station à affecter au maillon
 * @param stationAccessible la stationAccessible à affecter au maillon
 * @param suivant le maillon suivant dans la liste ou est present le maillon
 * @param precedant le maillon precedant dans la liste ou est present le maillon
 * @param poids le poids pour arriver a cette station
 * @param lastLigne le poids pour arriver a cette station
 */
void set_maillon(Maillon *maillon,
                 Arete *arete, Station *stationPivot,
                 Station *stationAccessible,
                 Maillon *suivant,
                 Maillon *precedant,
                 uint32_t poids,
                 char *lastLigne);

#endif