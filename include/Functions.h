#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Struct.h"

/**
 * @brief Fonction pour initialiser un nouveau chemin par l'utilisateur
 *
 * @param graphe le graphe ou sont disponible les stations
 * @return Chemin*
 */
Chemin *init_chemin(Graphe *graphe);

/**
 * @brief Fonction pour lire les données des stations à partir d'un fichier
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
void afficher_tabStationsParLettre(TabStationsParLettres *tabStationsParLettres,
                                   char lettre);

/**
 * @brief La fonction principale qui implemente l'algo djikstra
 *
 * @param nomFichierStations le fichier ou sont les stations qui font office de sommet
 * @param nomFichierAretes le fichier ou sont les aretes
 */
void djikstra(Graphe *graphe);

/**
 * @brief affiche le chemin a prendre et les lignes a utiliser
 * 
 * @param listePivots la liste des pivots
 * @param chemin la destination et l'origine
 */
void afficher_chemin(Liste *listePivots, Chemin *chemin);

#endif
