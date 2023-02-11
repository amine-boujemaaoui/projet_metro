#include "../../include/includes.h"

int main()
{
    double time_spent = 0.0;
    clock_t begin = clock();

    Graphe *graphe = chargerGraphe("../data/stationsEdited.csv", "../data/aretes.csv");
    djikstra(graphe);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Temps de calcule: %f seconds\n\n", time_spent);
            
    return EXIT_SUCCESS;
}