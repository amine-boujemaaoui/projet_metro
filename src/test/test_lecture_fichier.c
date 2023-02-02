#include "../../include/functions.h"
#define ID 20

int main()
{
    setlocale(LC_ALL, "fr_FR.utf-32");
    printf("\ndebut chargement ...\n\n");
    Graphe *graphe = chargerGraphe("data/stationsEdited.csv", "data/aretes.csv");
    printf("Nom,Id,estVisite\n=================\n");
    wprintf(L"%ls,%d,%s\n=================\n", graphe->stations[ID]->nom, graphe->stations[ID]->id, graphe->stations[ID]->estVisite ? "true" : "false");
    Maillon *aretes = graphe->aretes[ID]->tete;
    for (int count = 0; count < graphe->aretes[ID]->taille; count++)
    {
        printf("%d,%d,%s\n-----------------\n", aretes->arete->origine, aretes->arete->destination, aretes->arete->ligne);
        aretes = aretes->suivant;
    }
    printf("\nfin chargement.\n\n");
    return EXIT_SUCCESS;
}