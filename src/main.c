#include "../include/includes.h"
#define LETTRE 0

int main()
{
    char buffer[BUFFERZIZE], c;
    bool end = false;
    while (!end)
    {
        djikstra("../data/stationsEdited.csv", "../data/aretes.csv");
        printf("Voulez-vous afficher un nouveau chemin \033[0;30m[y\\n]\033[0m? ");
        scanf(" %c", &c);
        fgets(buffer, BUFFERZIZE, stdin);
        if (c == 'n') end = true;
    }
            
    return EXIT_SUCCESS;
}