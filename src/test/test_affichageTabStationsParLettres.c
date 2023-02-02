#include "../../include/functions.h"
#define LETTRE 0

int main()
{
    Graphe *graphe = chargerGraphe("data/stationsEdited.csv", "data/aretes.csv");
    Chemain *chemain = init_chemain(graphe);
    printf("Origine: %d\nDestination: %d\n", chemain->origine, chemain->destination);
    return EXIT_SUCCESS;
}