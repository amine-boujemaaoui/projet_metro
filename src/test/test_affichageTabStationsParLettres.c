#include "../../include/includes.h"
#define LETTRE 0

int main()
{
    Graphe *graphe = chargerGraphe("data/stationsEdited.csv", "data/aretes.csv");
    Chemin *chemin = init_chemin(graphe);
    printf("Origine: %s\nDestination: %s\n", graphe->stations[chemin->origine]->nom, graphe->stations[chemin->destination]->nom);
    return EXIT_SUCCESS;
}