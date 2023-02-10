#include "../../include/Struct.h"
#include "../../include/Liste.h"
#include "../../include/Malloc.h"
#include "../../include/Set.h"

TabStationsParLettres *new_tabStationsParLettres()
{
    TabStationsParLettres *tabStationsParLettres = (TabStationsParLettres *)myMalloc("\033[0;31mERREUR: impossible de creer le tableau des station pas lettre\033[0m\n", sizeof(TabStationsParLettres));
    tabStationsParLettres->tab = (Liste **)myMalloc("\033[0;31mERREUR: impossible de creer le tableau de liste de station du tabStationsParLettres\033[0m\n", NB_LETTRE * sizeof(Liste *));
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
        printf("\033[0;31mImpossible d'ouvrir le fichier %s\n", nomFichierStations);
        exit(1);
    }
    if (nomFichierAretes == NULL)
    {
        printf("\033[0;31mImpossible d'ouvrir le fichier %s\n", nomFichierAretes);
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
    printf("\033[0;32m+--------+--------------------+\033[0m\n\033[0;32m|\033[0m Lettre \033[0;32m|\033[0m Liste des stations \033[0;32m|\033[0m\n\033[0;32m+--------+--------------------+\033[0m\n");
    for (uint8_t i = 0; i < NB_LETTRE; i++)
    {
        printf("\033[0;32m|\033[0m %c     \033[0;32m|\033[0m ", 'A' + i);
        Maillon *station = tabStationsParLettres->tab[i]->tete;
        while (station != NULL)
        {
            printf("%s, ", station->stationPivot->nom);
            station = station->suivant;
        }
        printf("\033[0;32m|\033[0m\n");
    }
    printf("\033[0;32m+--------+--------------------+\033[0m\n");
}

void afficher_tabStationsParLettre(TabStationsParLettres *tabStationsParLettres, char lettre)
{
    printf("\033[0;32m+-----+--------------------------------------------------+\033[0m\n\033[0;32m|\033[0m ID  \033[0;32m|\033[0m Liste des stations                               \033[0;32m|\033[0m\n\033[0;32m+-----+--------------------------------------------------+\033[0m\n");
    Maillon *station = tabStationsParLettres->tab[lettre - 'A']->tete;
    while (station != NULL)
    {
        printf("\033[0;32m|\033[0m %-3d \033[0;32m|\033[0m %-48s \033[0;32m|\033[0m\n", station->stationPivot->id, station->stationPivot->nom);
        station = station->suivant;
    }
    printf("\033[0;32m+-----+--------------------------------------------------+\033[0m\n");
}

Chemin *init_chemin(Graphe *graphe)
{
    char buffer[BUFFERZIZE];
    Chemin *chemin = new_chemin();
    bool departValide = false, arriverValide = false;
    char lettreOrigine, lettreDestination;
    uint32_t origine, destination;
    Maillon *maillon;
    printf("Entrez la premiere lettre de la station de depart: ");
    scanf(" %c", &lettreOrigine);
    while ((lettreOrigine - 'A' > NB_LETTRE || lettreOrigine - 'A' < 0 || graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->taille == 0) &&
           (lettreOrigine - 'a' > NB_LETTRE || lettreOrigine - 'a' < 0 || graphe->tabStationsParLettres->tab[lettreOrigine - 'a']->taille == 0))
    {
        printf("\033[0;31mIl n'y a aucune station commencant par cette lettre !\033[0m\n");
        printf("Entrez la premiere letre de la station de depart: ");
        scanf(" %c", &lettreOrigine);
    }
    lettreOrigine = toupper(lettreOrigine);
    afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreOrigine);
    fgets(buffer, BUFFERZIZE, stdin);
    printf("Entrez l'identifiant de la station de depart: ");
    scanf(" %d", &origine);
    fgets(buffer, BUFFERZIZE, stdin);
    while (origine < 0 || origine > graphe->nbStations)
    {
        origine = 0;
        fgets(buffer, BUFFERZIZE, stdin);
        printf("\033[0;31mCet id n'existe pas !\033[0m\n");
        printf("Entrez l'identifiant de la station de depart: \n");
        scanf(" %d", &origine);
        fgets(buffer, BUFFERZIZE, stdin);
    }
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
            printf("\033[0;31mCe n'est pas une station de cette liste !\033[0m\n");
            printf("Entrez l'identifiant de la station de depart: ");
            scanf(" %d", &origine);
            fgets(buffer, BUFFERZIZE, stdin);
            maillon = graphe->tabStationsParLettres->tab[lettreOrigine - 'A']->tete;
        }
    }
    printf("Entrez la premiere lettre de la station d'arriver: ");
    scanf(" %c", &lettreDestination);
    while ((lettreDestination - 'A' > NB_LETTRE || lettreDestination - 'A' < 0 || graphe->tabStationsParLettres->tab[lettreDestination - 'A']->taille == 0) &&
           (lettreDestination - 'a' > NB_LETTRE || lettreDestination - 'a' < 0 || graphe->tabStationsParLettres->tab[lettreDestination - 'a']->taille == 0))
    {
        printf("\033[0;31mIl n'y a aucune station commencant par cette lettre !\033[0m\n");
        printf("Entrez la premiere letre de la station d'arriver: ");
        scanf(" %c", &lettreDestination);
    }
    lettreDestination = toupper(lettreDestination);
    afficher_tabStationsParLettre(graphe->tabStationsParLettres, lettreDestination);
    printf("Entrez l'identifiant de la station de destination: ");
    scanf(" %d", &destination);
    fgets(buffer, BUFFERZIZE, stdin);
    while (destination < 0 || destination > graphe->nbStations)
    {
        fgets(buffer, BUFFERZIZE, stdin);
        printf("Cet id n'existe pas %d!\n", destination);
        printf("Entrez l'identifiant de la station de destination: ");
        scanf(" %d", &destination);
        fgets(buffer, BUFFERZIZE, stdin);
    }
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
            printf("Ce n'est pas une station de cette liste!\n");
            printf("Entrez l'identifiant de la station de destination: ");
            scanf(" %d", &destination);
            fgets(buffer, BUFFERZIZE, stdin);
            maillon = graphe->tabStationsParLettres->tab[lettreDestination - 'A']->tete;
        }
    }
    printf("\n");
    chemin->origine = origine;
    chemin->destination = destination;
    return chemin;
}

void afficher_chemin(Liste *listePivots, Chemin *chemin)
{
    Maillon *last, *save, *affichage;
    Liste *listeOrdonner = new_liste();
    affichage = listePivots->tete;
    last = affichage;
    save = new_maillon();
    set_maillon(save, last->arete, last->stationPivot, last->stationAccessible, NULL, NULL, last->poids, last->lastLigne);
    add_tete(listeOrdonner, save);
    affichage = affichage->suivant;
    while (affichage != NULL && affichage->stationPivot->id)
    {
        if (last->stationPivot->id == chemin->origine)
            affichage = NULL;
        else
        {
            while ((affichage != NULL) && (last->stationAccessible->id != affichage->stationPivot->id))
                affichage = affichage->suivant;
            last = affichage;
            save = new_maillon();
            set_maillon(save, last->arete, last->stationPivot, last->stationAccessible, NULL, NULL, last->poids, last->lastLigne);
            add_tete(listeOrdonner, save);
            affichage = listePivots->tete;
        }
    }
    affichage = listeOrdonner->tete;
    affichage = affichage->suivant;
    while (affichage != NULL)
    {
        printf("(ligne %s)%s\n", affichage->lastLigne, affichage->stationAccessible->nom);
        printf("      |\n      V\n");
        affichage = affichage->suivant;
        if (affichage->suivant == NULL)
        {
            printf("(ligne %s)%s\n\n", affichage->lastLigne, affichage->stationPivot->nom);
            printf("Temps de trajet total: %d minutes\n\n", affichage->poids);
            affichage = NULL;
        }
        
    }
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
                    poids += MINUTE_CHANGEMENT_LIGNE;
                m = new_maillon();
                set_maillon(m, NULL, graphe->stations[a->arete->destination], listePivots->tete->stationPivot, NULL, NULL, listePivots->poidsTotal + poids, a->arete->ligne);
                add_poidMin(stationsVoisines, m);
            }
            a = a->suivant;
        }
        r = rem_tete(stationsVoisines);
        while (isin(listePivots, r->stationPivot->id) && stationsVoisines->taille != 0)
        {
            free(r);
            r = rem_tete(stationsVoisines);
        }
        listePivots->poidsTotal = r->poids;
        add_tete(listePivots, r);
        listePivots->tete->stationPivot->estVisite = true;
        count++;
    }
    afficher_chemin(listePivots, chemin);
}