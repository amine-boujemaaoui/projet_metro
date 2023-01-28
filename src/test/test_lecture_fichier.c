#include "../../include/structures.h"

int main()
{
    printf("\ndebut chargement ...\n");
    Graphe *graphe = chargerGraphe("data/stations.csv", "data/aretes.csv");
    /*
    for (int count = 0; count < graphe->nbStations; count++)
    {
        printf("%d|id:%d|nom:%s|\n", count, graphe->stations[count]->id, graphe->stations[count]->nom);
    }
    printf("\nfin chargement.\n");
    */
    return EXIT_SUCCESS;
}