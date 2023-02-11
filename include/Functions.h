#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Struct.h"

/**
 * @brief Fonction pour initialiser un nouveau chemin par l'utilisateur
 *
 * @param graphe Le graphe ou sont disponible les stations
 * @return Chemin*
 */
Chemin *init_chemin(Graphe *graphe);

/**
 * @brief Fonction pour lire les données des stations à partir d'un fichier
 * @param nomFichierStations Le fichier ou sont les stations
 * @param nomFichierAretes Le fichier ou sont les arêtes
 * @return Graphe*
 */
Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes);

/**
 * @brief Fonction pour afficher le tableau des stations par lettre
 *
 * @param tabStationsParLettres Le tableau des stations par lettre à afficher
 */
void afficher_tabStations(TabStationsParLettres *tabStationsParLettres);

/**
 * @brief Fonction pour afficher le tableau des stations par lettre pour une lettre choisi
 *
 * @param tabStationsParLettres Le tableau des stations par lettre à afficher
 * @param lettre la lettre choisi
 */
void afficher_tabStationsParLettre(TabStationsParLettres *tabStationsParLettres,
                                   char lettre);

/**
 * @brief La fonction principale qui implémente l'algorithme de Dijkstra
 * @param graphe Le graphe sur lequel on applique l'algorithme
 */
void dijkstra(Graphe *graphe);

/**
 * @brief Affiche le chemin à prendre et les lignes utilisées
 *
 * @param listePivots La liste des pivots
 * @param chemin La destination et l'origine
 */
void afficher_chemin(Liste *listePivots, Chemin *chemin);

#endif
