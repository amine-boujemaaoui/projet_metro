#include "../../include/functions.h"

void *myMalloc(uint64_t size, char *message)
{
    void *pointeur = malloc(size);
    if (pointeur == NULL)
    {
        printf("%s\n", message);
        exit(EXIT_FAILURE);
    }
    else
        return pointeur;
}