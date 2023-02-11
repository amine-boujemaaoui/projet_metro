#include "../../include/includes.h"

void add_tete(Liste *l, Maillon *m)
{
    m->suivant = l->tete;
    m->precedant = NULL;
    if (l->taille == 0)
        l->queue = m;
    else
        l->tete->precedant = m;
    l->tete = m;
    l->taille++;
}

void add_queue(Liste *l, Maillon *m)
{
    m->suivant = NULL;
    m->precedant = l->queue;
    if (l->taille > 0)
        l->queue->suivant = m;
    else
        l->tete = m;
    l->queue = m;
    l->taille++;
}

void add_position(Liste *l, Maillon *m, uint32_t pos)
{
    Maillon *precedant, *suivant;
    if (pos > l->taille)
    {
        printf("\033[0;31mERREUR : tentative d'ajout à une position en dehors de la liste !\033[0m\n");
        exit(EXIT_FAILURE);
    }
    else if (pos == 0)
        add_tete(l, m);
    else if (pos == l->taille)
        add_queue(l, m);
    else
    {
        precedant = l->tete;
        for (uint32_t i = 0; i < pos - 1; i++)
            precedant = precedant->suivant;
        suivant = precedant->suivant;
        precedant->suivant = m;
        m->suivant = suivant;
        suivant->precedant = m;
        m->precedant = precedant;
        l->taille++;
    }
}

void add_poidMin(Liste *l, Maillon *m)
{
    uint32_t pos = 0;
    Maillon *maillon = l->tete;
    if (maillon == NULL)
    {
        pos = 0;
    }
    else
    {
        while (maillon != NULL && m->poids > maillon->poids)
        {
            maillon = maillon->suivant;
            pos++;
        }
    }
    add_position(l, m, pos);
}

Maillon *rem_tete(Liste *l)
{
    if (l->taille == 0)
    {
        printf("\033[0;31mERREUR : tentative de soustraction d'un élément en tête d'une liste vide !\033[0m\n");
        exit(EXIT_FAILURE);
    }

    Maillon *maillon = l->tete;
    l->tete = l->tete->suivant;
    l->taille--;
    if (l->taille == 0)
        l->queue = NULL;
    else
        l->tete->precedant = NULL;
    return maillon;
}

Maillon *rem_queue(Liste *l)
{
    Maillon *maillon = l->queue;
    l->queue = l->queue->precedant;
    l->taille--;
    if (l->taille == 0)
        l->tete = NULL;
    else
        l->queue->suivant = NULL;
    return maillon;
}

Maillon *rem_position(Liste *l, uint32_t pos)
{
    Maillon *maillon, *precedant, *suivant;
    if (pos >= l->taille)
    {
        printf("\033[0;31mERREUR : tentative de suppression à une position en dehors de la liste !\033[0m\n");
        exit(EXIT_FAILURE);
    }
    else if (pos == 0)
        return rem_tete(l);
    else if (pos == l->taille - 1)
        return rem_queue(l);
    else
    {
        maillon = l->tete;
        for (uint32_t i = 0; i < pos; i++)
            maillon = maillon->suivant;
        precedant = maillon->precedant;
        suivant = maillon->suivant;
        precedant->suivant = suivant;
        suivant->precedant = precedant;
        l->taille--;
        return maillon;
    }
}

bool isin(Liste *l, uint32_t id)
{
    if (l->taille == 0)
    {
        return false;
    }
    else
    {
        Maillon *maillon = l->tete;
        while (maillon != NULL)
        {
            if (id == maillon->stationPivot->id)
                return true;
            maillon = maillon->suivant;
        }
        return false;
    }
}