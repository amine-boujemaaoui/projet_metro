#include "../../include/includes.h"

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
    printf("\n+-----+--------------------------------------------------+\n");
    printf("| ID  | Liste des stations                               |\n");
    printf("+-----+--------------------------------------------------+\n");
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
    if (graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->taille == 0)
    {
        while (graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->taille == 0)
        {
            printf("Il n'y a aucune station commencant par cette lettre!\n");
            printf("Entrez la premiere letre de la station de depart: ");
            scanf(" %c", &lettreOrigine);
            lettreOrigine = toupper(lettreOrigine);
        }
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
            afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreOrigine);
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
        while (maillon != NULL)
        {
            if (maillon->stationPivot->id == destination)
                arriverValide = true;
            maillon = maillon->suivant;
        }
        if (!arriverValide)
        {
            printf("l'id %d n'est pas une station de cette liste!\n", destination);
            afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreDestination);
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
    // bool fini = false;
    uint32_t poids = 0;
    Maillon *m, *a, *p, *r;
    m = new_maillon();
    set_maillon(m, NULL, graphe->stations[chemin->origine], NULL, NULL, NULL, 0, "DEFAULT");
    add_tete(listePivots, m);
    listePivots->tete->stationPivot->estVisite = true;
    // printf("%d-%s %s T=%d\n", listePivots->tete->stationPivot->id, listePivots->tete->stationPivot->nom, listePivots->tete->lastLigne, listePivots->poidsTotal);
    uint32_t count = 0;
    while (count < graphe->nbStations)
    {
        p = listePivots->tete;
        a = graphe->aretes[p->stationPivot->id]->tete;
        printf("DEBUT FOR\n");
        for (uint32_t i = 0; i < graphe->aretes[p->stationPivot->id]->taille; i++)
        {
            printf("== %s\n", graphe->stations[a->arete->destination]->estVisite ? "true" : "false");
            if (!graphe->stations[a->arete->destination]->estVisite)
            {
                poids = MINUTE_CONNEXION;
                if ((p->lastLigne != a->arete->ligne) || (strcmp(p->lastLigne, "DEFAULT") != 0))
                    poids += MINUTE_CHANGEMENT_LIGNE;
                m = new_maillon();
                printf("%d-%s %d-%s %d %s T=%d\n", p->stationPivot->id, p->stationPivot->nom, graphe->stations[a->arete->destination]->id, graphe->stations[a->arete->destination]->nom, poids, a->arete->ligne, listePivots->poidsTotal);
                set_maillon(m, NULL, p->stationPivot, graphe->stations[a->arete->destination], NULL, NULL, poids, a->arete->ligne);
                add_poidMin(stationsVoisines, m);
                printf("(%s)%d-%s\n", stationsVoisines->tete->lastLigne, stationsVoisines->tete->stationPivot->id, stationsVoisines->tete->stationPivot->nom);
                a = a->suivant;
                listePivots->poidsTotal += poids;
            }
        }
        printf("FIN FOR\n\n");
        r = rem_tete(stationsVoisines);
        Maillon *temp = stationsVoisines->tete;
        for (u_int32_t i = 0; i < 20; i++)
        {
            printf("%s \n", temp->stationPivot->nom);
            temp = temp->suivant;
        }

        add_tete(listePivots, r);
        listePivots->tete->stationPivot->estVisite = true;
        count++;
        // printf("%s \n", listePivots->tete->stationPivot->nom);
        printf("========== %d ==========\n\n\n", count);
    }
    Maillon *affichage = listePivots->queue;
    // for (uint32_t j = 0; j < listePivots->taille; j++)
    // {
    //     while (affichage->precedant != NULL)
    //     {
    //         printf("(%s)%s -> ", affichage->lastLigne, affichage->stationPivot->nom);
    //     }
    // }
    printf("\n");
}

int main()
{
    djikstra("../data/stationsEdited.csv", "../data/aretes.csv");
    return EXIT_SUCCESS;
}