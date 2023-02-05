#include "../../include/Struct.h"
#include "../../include/Liste.h"
#include "../../include/Malloc.h"
#include "../../include/Set.h"

TabStationsParLettres *new_tabStationsParLettres()
{
    TabStationsParLettres *tabStationsParLettres = (TabStationsParLettres *)myMalloc("ERREUR: impossible de creer le tableau des station pas lettre\n", sizeof(TabStationsParLettres));
    tabStationsParLettres->tab = (Liste **)myMalloc("ERREUR: impossible de creer le tableau de liste de station du tabStationsParLettres\n", NB_LETTRE * sizeof(Liste *));
    for (uint8_t i = 0; i < NB_LETTRE; i++)
    {
        tabStationsParLettres->tab[i] = new_liste();
    }
    return tabStationsParLettres;
}

void afficher_tabStationsParLettres(TabStationsParLettres *tabStationsParLettres)
{
    for (uint8_t i = 0; i < NB_LETTRE; i++)
    {
        Maillon *stations = tabStationsParLettres->tab[i]->tete;
        printf("| %c |", 'A' + i);
        while (stations->suivant != NULL)
        {
            printf(" %s,", stations->stationPivot->nom);
            stations = stations->suivant;
        }
        printf("\n\n");
    }
}

Graphe *chargerGraphe(char *nomFichierStations, char *nomFichierAretes)
{
    FILE *fichierStations = fopen(nomFichierStations, "r");
    FILE *fichierAretes = fopen(nomFichierAretes, "r");
    TabStationsParLettres *tabStationsParLettres = new_tabStationsParLettres();
    char tmpChar[SIZE_NAME_STATION];
    uint32_t tmpInt, tmpInt2;
    if (fichierStations == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichierStations);
        exit(1);
    }
    if (nomFichierAretes == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", nomFichierAretes);
        exit(1);
    }
    // On compte le nombre de station dans le fichier nomFichierAretes
    uint32_t nbStations = 0;
    fscanf(fichierStations, "%[^,],%[^\n]", tmpChar, tmpChar); // on passe l'entete du fichier
    while (fscanf(fichierStations, "%[^,],%d\n", tmpChar, &tmpInt) != EOF)
        nbStations++;
    rewind(fichierStations);
    // On compte le nombre d'arrete dans le fichier nomFichierAretes
    uint32_t nbAretes = 0;
    fscanf(fichierAretes, "%[^,],%[^,],%[^\n]", tmpChar, tmpChar, tmpChar); // on passe l'entete du fichier
    while (fscanf(fichierAretes, "%d,%d,%[^\n]", &tmpInt, &tmpInt2, tmpChar) != EOF)
        nbAretes++;
    rewind(fichierAretes);
    Graphe *graphe = new_graphe(nbStations + 1, nbAretes);
    // On charge les stations dans le graphe
    uint32_t count = 0;
    char nom[SIZE_NAME_STATION];
    uint32_t id;
    fscanf(fichierStations, "%[^,],%[^\n]\n", tmpChar, tmpChar); // on passe l'entete du fichier
    while (fscanf(fichierStations, "%[^,],%d\n", nom, &id) != EOF)
    {
        set_station(graphe->stations[id], id, nom, false);
        Maillon *maillon = new_maillon();
        set_maillon(maillon, NULL, graphe->stations[id], NULL, NULL, NULL, 0, "DEFAULT");
        add_queue(tabStationsParLettres->tab[nom[0] - 'A'], maillon);
        count++;
    }
    graphe->tabStationsParLettres = tabStationsParLettres;
    // On charge les aretes dans le graphe
    count = 0;
    fscanf(fichierAretes, "%[^,],%[^,],%[^\n]", tmpChar, tmpChar, tmpChar); // on passe l'entete du fichier
    uint32_t origine, destination;
    char ligne[SIZE_NAME_LIGNE];
    while (fscanf(fichierAretes, "%d,%d,%[^\n]", &origine, &destination, ligne) != EOF)
    {
        Arete *arete = new_arete();
        set_arete(arete, origine, destination, MINUTE_CONNEXION, ligne);
        Maillon *maillon = new_maillon();
        set_maillon(maillon, arete, NULL, NULL, NULL, NULL, 0, "DEFAULT");
        add_queue(graphe->aretes[origine], maillon);
        count++;
    }
    fclose(fichierStations);
    fclose(fichierAretes);
    return graphe;
}

void afficher_tabStations(TabStationsParLettres *tabStationsParLettres)
{
    printf("+--------+--------------------+\n| Lettre | Liste des stations |\n+--------+--------------------+\n");
    for (uint8_t i = 0; i < NB_LETTRE; i++)
    {
        printf("| %c     | ", 'A' + i);
        Maillon *station = tabStationsParLettres->tab[i]->tete;
        while (station != NULL)
        {
            printf("%s, ", station->stationPivot->nom);
            station = station->suivant;
        }
        printf("|\n");
    }
    printf("+--------+--------------------+\n");
}

void afficher_tabStationsParLettre(TabStationsParLettres *tabStationsParLettres, char lettre)
{
    printf("+-----+--------------------------------------------------+\n| ID  | Liste des stations                               |\n+-----+--------------------------------------------------+\n");
    Maillon *station = tabStationsParLettres->tab[lettre - 'A']->tete;
    while (station != NULL)
    {
        printf("| %-3d | %-48s |\n", station->stationPivot->id, station->stationPivot->nom);
        station = station->suivant;
    }
    printf("+-----+--------------------------------------------------+\n");
}

Chemin *init_chemin(Graphe *graphe)
{
    Chemin *chemin = new_chemin();
    bool departValide = false, arriverValide = false;
    char lettreOrigine, lettreDestination;
    uint32_t origine, destination;
    Maillon *maillon;
    printf("Entrez la premiere letre de la station de depart: ");
    scanf(" %c", &lettreOrigine);
    lettreOrigine = toupper(lettreOrigine);
    while (graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->taille == 0)
    {
        printf("Il n'y a aucune station commencant par cette lettre!\nEntrez la premiere letre de la station de depart: ");
        scanf(" %c", &lettreOrigine);
        lettreOrigine = toupper(lettreOrigine);
    }
    afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreOrigine);
    printf("Entrez l'identifiant de la station de depart: ");
    scanf(" %d", &origine);
    maillon = graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->tete;
    while (!departValide)
    {
        while (maillon != NULL && !departValide)
        {
            if (maillon->stationPivot->id == origine)
                departValide = true;
            maillon = maillon->suivant;
        }
        if (!departValide)
        {
            printf("l'id %d n'est pas une station de cette liste!\n", origine);
            // afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreOrigine);
            printf("Entrez l'identifiant de la station de depart: ");
            scanf(" %d", &origine);
            maillon = graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->tete;
        }
    }
    printf("Entrez la premiere letre de la station d'arriver: ");
    scanf(" %c", &lettreDestination);
    lettreDestination = toupper(lettreDestination);
    if (graphe->tabStationsParLettres->tab[lettreDestination - 'A']->taille == 0)
    {
        while (graphe->tabStationsParLettres->tab[lettreDestination - 'A']->taille == 0)
        {
            printf("Il n'y a aucune station commencent par cette lettre!\n");
            printf("Entrez la premiere letre de la station d'arriver: ");
            scanf(" %c", &lettreDestination);
            lettreDestination = toupper(lettreDestination);
        }
    }
    afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreDestination);
    printf("Entrez l'identifiant de la station d'arriver: ");
    scanf(" %d", &destination);
    maillon = graphe->tabStationsParLettres->tab[lettreDestination - 'A']->tete;
    while (!arriverValide)
    {
        while (maillon != NULL && !arriverValide)
        {
            if (maillon->stationPivot->id == destination)
                arriverValide = true;
            maillon = maillon->suivant;
        }
        if (!arriverValide)
        {
            printf("l'id %d n'est pas une station de cette liste!\n", destination);
            // afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreDestination);
            printf("Entrez l'identifiant de la station de depart: ");
            scanf(" %d", &destination);
            maillon = graphe->tabStationsParLettres->tab[lettreDestination - 'A']->tete;
        }
    }
    chemin->origine = origine;
    chemin->destination = destination;
    return chemin;
}

void djikstra(char *nomFichierStations, char *nomFichierAretes)
{
    Graphe *graphe = chargerGraphe(nomFichierStations, nomFichierAretes);
    Chemin *chemin = init_chemin(graphe);
    Liste *listePivots = new_liste();
    Liste *stationsVoisines = new_liste();
    uint32_t poids = 0;
    Maillon *m, *a, *r;
    m = new_maillon();
    set_maillon(m,
                NULL,
                graphe->stations[chemin->origine],
                NULL,
                NULL,
                NULL,
                0,
                "DEFAULT");
    add_tete(listePivots, m);
    listePivots->tete->stationPivot->estVisite = true;
    uint32_t count = 0;
    while (count < graphe->nbStations && listePivots->tete->stationPivot->id != chemin->destination)
    {
        a = graphe->aretes[listePivots->tete->stationPivot->id]->tete;
        while (a != NULL)
        {
            if (!graphe->stations[a->arete->destination]->estVisite)
            {
                poids = MINUTE_CONNEXION;
                if ((strcmp(listePivots->tete->lastLigne, a->arete->ligne) != 0) && (strcmp(listePivots->tete->lastLigne, "DEFAULT") != 0))
                {
                    poids += MINUTE_CHANGEMENT_LIGNE;
                }
                m = new_maillon();
                set_maillon(m, NULL, graphe->stations[a->arete->destination], listePivots->tete->stationPivot, NULL, NULL, listePivots->poidsTotal + poids, a->arete->ligne);
                add_poidMin(stationsVoisines, m);
                // printf("+ (%d,%d)(%s)[%d]", m->stationAccessible->id, m->stationPivot->id, m->lastLigne, m->poids);
            }
            a = a->suivant;
        }
        // Maillon *tempSV = stationsVoisines->tete;
        // printf("\nSV:");
        // while (tempSV != NULL)
        // {
        //     printf("(%d,%d)(%s)[%d] -> ", tempSV->stationAccessible->id ,tempSV->stationPivot->id, tempSV->lastLigne, tempSV->poids);
        //     tempSV = tempSV->suivant;
        // }
        // Maillon *tempLP = listePivots->tete;
        // printf("\nLP:");
        // while (tempLP != NULL)
        // {
        //     printf("%d(%s)[%d] -> ",  tempLP->stationPivot->id, tempLP->lastLigne, tempLP->poids);
        //     tempLP = tempLP->suivant;
        // }
        // printf("\nStation voisine a retier: %d(%s)[%d]\n", stationsVoisines->tete->stationPivot->id, stationsVoisines->tete->lastLigne, stationsVoisines->tete->poids);
        r = rem_tete(stationsVoisines);
        // printf("Pivot deja prsent? %s\n", isin(listePivots, r->stationPivot->id) ? "true" : "false");
        while (isin(listePivots, r->stationPivot->id) && stationsVoisines->taille != 0)
        {
            free(r);
            r = rem_tete(stationsVoisines);
        }
        // printf("maillon retirer: (%s)[%d]%d\n", r->lastLigne, r->poids, r->stationPivot->id);
        listePivots->poidsTotal = r->poids;
        add_tete(listePivots, r);
        listePivots->tete->stationPivot->estVisite = true;
        count++;
    }
    Maillon *tempLP = listePivots->tete;
    printf("\nLP:");
    uint32_t sa = 0;
    while (tempLP != NULL)
    {
        if (tempLP->stationAccessible == NULL)
        {
            sa = 0;
        }
        else
        {
            sa = tempLP->stationAccessible->id;
        }

        printf("(%d,%d)(%s)[%d] -> ", sa, tempLP->stationPivot->id, tempLP->lastLigne, tempLP->poids);
        tempLP = tempLP->suivant;
    }
    Maillon *affichage, *last;
    affichage = listePivots->tete;
    last = affichage;
    affichage = affichage->suivant;
    while (affichage != NULL)
    {
        if (last->stationPivot->id == chemin->origine)
        {
            affichage = NULL;
        }
        else
        {
            printf("\n(%d,%d)(%s)[%d]\n", last->stationAccessible->id, last->stationPivot->id, last->lastLigne, last->poids);
            while ((affichage != NULL) && (last->stationAccessible->id != affichage->stationPivot->id))
            {
                // printf("(%d,%d) - (%d,%d)\n", last->stationAccessible->id, last->stationPivot->id, affichage->stationAccessible->id, affichage->stationPivot->id);
                affichage = affichage->suivant;
            }
            last = affichage;
            affichage = listePivots->tete;
        }
    }
}