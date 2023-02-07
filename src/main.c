#include "../include/includes.h"
#define LETTRE 0

int main()
{
    bool end = false;
    while (!end)
    {
        char c;
        djikstra("../data/stationsEdited.csv", "../data/aretes.csv");
        printf("Voulez-vous afficher un nouveau chemain [y\\n]?\n");
        scanf(" %c", &c);
        switch (c)
        {
        case 'y':
            djikstra("../data/stationsEdited.csv", "../data/aretes.csv");
            printf("Voulez-vous afficher un nouveau chemain \033[0;30m[y\\n]\033[0m?");
            scanf(" %c", &c);
            break;

        case 'n':
            end = true;
            break;

        default:
            end = true;
            break;
        }
    }
    return EXIT_SUCCESS;
}