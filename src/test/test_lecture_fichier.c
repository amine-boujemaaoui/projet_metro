#include "../../include/structures.h"

int main()
{
    printf("\ndebut chargement ...\n");
    Graphe *graphe = chargerGraphe("data/stations.csv", "data/aretes.csv");

    printf("Nom,Id\n");
    for (int count = 0; count < graphe->nbStations; count++)
        printf("%s,%d\n", graphe->stations[count]->nom, graphe->stations[count]->id);

    printf("Origine,Destination,Ligne\n");
    for (int count = 0; count < graphe->nbAretes; count++)
        printf("%d,%d,%s\n", graphe->aretes[count]->origine, graphe->aretes[count]->destination, graphe->aretes[count]->ligne);

    printf("\nfin chargement.\n");
    return EXIT_SUCCESS;
}