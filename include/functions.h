#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// fonction d'allocation mémoire et affichage de message d'erreur en cas d'echec
void *myMalloc(uint64_t size, char *message);
// Fonction pour lire les données des stations à partir d'un fichier
Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes);