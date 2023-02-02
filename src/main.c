#include "../include/includes.h"
#define LETTRE 0

int main()
{
    Graphe *graphe = chargerGraphe("../data/stationsEdited.csv", "../data/aretes.csv");
    Chemain *chemain = init_chemain(graphe);
    printf("Origine: %s\nDestination: %s\n", graphe->stations[chemain->origine]->nom, graphe->stations[chemain->destination]->nom);
    return EXIT_SUCCESS;
}