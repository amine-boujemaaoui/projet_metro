#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Struct.h"

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