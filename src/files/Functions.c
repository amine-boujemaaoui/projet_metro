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
        set_maillon(maillon, NULL, graphe->stations[id], NULL, NULL, NULL, 0);
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
        set_maillon(maillon, arete, NULL, NULL, NULL, NULL, 0);
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
    printf("| ID  + Liste des stations                               |\n");
    printf("+-----+--------------------------------------------------+\n");
    Maillon *station = tabStationsParLettres->tab[lettre - 'A']->tete;
    while (station != NULL)
    {
        printf("| %-3d | %-48s |\n", station->stationPivot->id, station->stationPivot->nom);
        station = station->suivant;
    }
    printf("+-----+--------------------------------------------------+\n");
}

Chemain *init_chemain(Graphe *graphe)
{
    Chemain *chemain = new_chemain();
    bool departValide = false, arriverValide = false;
    char lettreOrigine, lettreDestination;
    uint32_t origine, destination;
    Maillon *maillon;
    system("cls");
    printf("Entrez la premiere letre de la station de depart: ");
    scanf("%c", &lettreOrigine);
    fflush(stdin);
    lettreOrigine = toupper(lettreOrigine);
    if (graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->taille == 0)
    {
        while (graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->taille == 0)
        {
            fflush(stdin);
            system("cls");
            printf("Il n'y a aucune station commencant par cette lettre!\n");
            printf("Entrez la premiere letre de la station de depart: ");
            scanf("%c", &lettreOrigine);
            lettreOrigine = toupper(lettreOrigine);
        }
    }
    fflush(stdin);
    system("cls");
    afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreOrigine);
    printf("Entrez l'identifiant de la station de depart: ");
    scanf("%d", &origine);
    fflush(stdin);
    system("cls");
    maillon = graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->tete;
    while (!departValide)
    {
        while (maillon != NULL)
        {
            if (maillon->stationPivot->id == origine)
                departValide = true;
            maillon = maillon->suivant;
        }
        if (!departValide)
        {
            fflush(stdin);
            system("cls");
            printf("l'id %d n'est pas une station de cette liste!\n", origine);
            afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreOrigine);
            printf("Entrez l'identifiant de la station de depart: ");
            scanf("%d", &origine);
            maillon = graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->tete;
        }
    }
    fflush(stdin);
    system("cls");
    printf("Entrez la premiere letre de la station d'arriver: ");
    scanf("%c", &lettreDestination);
    lettreDestination = toupper(lettreDestination);
    if (graphe->tabStationsParLettres->tab[lettreDestination - 'A']->taille == 0)
    {
        while (graphe->tabStationsParLettres->tab[lettreDestination - 'A']->taille == 0)
        {
            fflush(stdin);
            system("cls");
            printf("Il n'y a aucune station commencent par cette lettre!\n");
            printf("Entrez la premiere letre de la station d'arriver: ");
            scanf("%c", &lettreDestination);
            lettreDestination = toupper(lettreDestination);
        }
    }
    fflush(stdin);
    afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreDestination);
    printf("Entrez l'identifiant de la station d'arriver: ");
    scanf("%d", &destination);
    fflush(stdin);
    system("cls");
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
            fflush(stdin);
            system("cls");
            printf("l'id %d n'est pas une station de cette liste!\n", destination);
            afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreDestination);
            printf("Entrez l'identifiant de la station de depart: ");
            scanf("%d", &destination);
            maillon = graphe->tabStationsParLettres->tab[lettreDestination - 'A']->tete;
        }
    }
    chemain->origine = origine;
    chemain->destination = destination;
    return chemain;
}

void djikstra(char *nomFichierStations, char *nomFichierAretes)
{
    Graphe *graphe = chargerGraphe(nomFichierStations, nomFichierAretes);
    Chemain *chemain = init_chemain(graphe);
}