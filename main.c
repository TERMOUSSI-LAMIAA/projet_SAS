#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// enum Statut_tache{
//     A_REALISER=1,EN_COURS_DE_REALISATION=2,FINALISEE=3//1.2.3 pour lentree d'utilisateur
// };
typedef struct
{
    int day, month, year;
} Date;
typedef struct
{
    int id;
    char titre[100];
    char description[100];
    Date deadline;    // day/month/year +(time)//struct date-->date deadline
    char statut[100]; // retourne int +switch pour afficher "a realiser"
} Todo;
// fonction recherche par id
int search_by_id(int id_rech)
{
    Todo tache;
    char line[256]; // 255
    FILE *fich;
    fich = fopen("test.txt", "r");
    while (fgets(line, sizeof(line), fich) != NULL)
    {
        sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^;]", &tache.id, tache.titre, tache.description, &tache.deadline.day,
               &tache.deadline.month, &tache.deadline.year, tache.statut);
        if (tache.id == id_rech)
        {

            fclose(fich);
            return 1;
        }
    }
    fclose(fich);
    return -1;
}
void add_tache()
{
    Todo tache;
    FILE *fich;
    int stat;
top:
    printf("\nEntrez id de la tache:");
    scanf("%d", &tache.id);
    if (search_by_id(tache.id) == 1)
    {
        printf("\nCe id existe deja!");
        goto top;
    }
    fich = fopen("test.txt", "a");
    if (fich == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
    }
    printf("\nEntrezle titre :");
    scanf(" %99[^\n]", tache.titre);
    printf("\nEntrez la description:");
    scanf(" %99[^\n]", tache.description);
    printf("\nEntrez deadline:");
    scanf("%d/%d/%d", &tache.deadline.day, &tache.deadline.month, &tache.deadline.year);
    printf("Entrez le statut de la tache.\n");
    printf("\t\t1--A REALISER\n");
    printf("\t\t2--EN COURS DE REALISATION\n");
    printf("\t\t3--FINALISEE\n");
    printf("\nEntrez le statut:");
    scanf("%d", &stat);
    // menu de statut
    switch (stat)
    {
    case 1:
        strcpy(tache.statut, "A REALISE");
        break;
    case 2:
        strcpy(tache.statut, "EN COURS DE REALISATION");
        break;
    case 3:
        strcpy(tache.statut, "FINALISEE");
        break;
    default:
        printf("Statut inconnu");
        break;
    }

    fprintf(fich, "%d;%s;%s;%d/%d/%d;%s\n", tache.id, tache.titre, tache.description, tache.deadline.day,
            tache.deadline.month, tache.deadline.year, tache.statut);
    fclose(fich);
}
void affichage_taches()
{
    FILE *fich;
    char line[100];
    fich = fopen("test.txt", "r");
    if (fich == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
    }
    while (fgets(line, sizeof(line), fich) != NULL)
    {
        printf("%s", line);
    }
    fclose(fich);
}
void update_desc()
{
    Todo tache;
    int id_updt;
    printf("Entrer l\'id de la tache a modifier");
    scanf("%d", &id_updt);
    if (search_by_id(id_updt) == -1)
    {
        printf("id introuvable\n");
        return;
    }
    FILE *fich, *F;
    char line[256];
    fich = fopen("test.txt", "r");
    F = fopen("temptest.txt", "w");
    if (fich == NULL || F == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return; // return !
    }
    while (fgets(line, sizeof(line), fich) != NULL)
    {
        sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^\n]", &tache.id, tache.titre, tache.description,
               &tache.deadline.day, &tache.deadline.month, &tache.deadline.year, tache.statut);
        if (tache.id == id_updt)
        {
            printf("Entrer la nouvelle description:");
            scanf(" %99[^\n]", tache.description);
        }
        fprintf(F, "%d;%s;%s;%d/%d/%d;%s\n", tache.id, tache.titre, tache.description,
                tache.deadline.day, tache.deadline.month, tache.deadline.year, tache.statut);
    }

    fclose(fich);
    fclose(F);
    if (remove("test.txt") != 0)
    {
        printf("Erreur de modification\n");
        return;
    }
    if (rename("temptest.txt", "test.txt") != 0)
    {
        printf("Erreur de modification\n");
        return;
    }
    printf("Modification effectue avec succes\n");
}
void update_stat()
{
    Todo tache;
    FILE *fich, *F;
    char line[256];
    int id_updt, stat;
    printf("Entrer l\'id de la tache a modifier:\n\t");
    scanf("%d", &id_updt);
    if (search_by_id(id_updt) == -1)
    {
        printf("id introuvable\n");
        return;
    }
    fich = fopen("test.txt", "r");
    F = fopen("temptest.txt", "w");
    if (fich == NULL || F == NULL)
    {
        printf("Impossible d'ouvrir le fichier.\n");
        return; // return pour sortir
    }

    show_status_menu:
    printf("Entrez le statut de la tache.\n");
    printf("\t\t1--A REALISER\n");
    printf("\t\t2--EN COURS DE REALISATION\n");
    printf("\t\t3--FINALISEE\n");
    printf("Entrer le nouveau statut:\n\t\t");
    scanf("%d", &stat);

    if(stat <1 || stat> 3 ){
        printf("Statut inconnu\n");
        goto show_status_menu;
    }

    while (fgets(line, sizeof(line), fich) != NULL)
    {
        sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^\n]", &tache.id, tache.titre, tache.description,
               &tache.deadline.day, &tache.deadline.month, &tache.deadline.year, tache.statut);
        if (tache.id == id_updt)
        {
            switch (stat)
            {
            case 1:
                strcpy(tache.statut, "A REALISER");
                break;
            case 2:
                strcpy(tache.statut, "EN COURS DE REALISATION");
                break;
            case 3:
                strcpy(tache.statut, "FINALISEE");
                break;
            default:
                break;
            }
        }
        fprintf(F, "%d;%s;%s;%d/%d/%d;%s\n", tache.id, tache.titre, tache.description,
                tache.deadline.day, tache.deadline.month, tache.deadline.year, tache.statut);
    }
    fclose(fich);
    fclose(F);
    if (remove("test.txt") != 0)
    {
        printf("Erreur de modification");
        return;
    }
    if (rename("temptest.txt", "test.txt") != 0)
    {
        printf("Erreur de modification");
        return;
    }
    printf("Modification effectue avec succes\n");
}
 void delete_tache(){
     Todo tache;
     int id_delete;
     printf("Entrer l\'id de la tache a supprimer");
     scanf("%d",&id_delete);
     if(search_by_id(id_delete)==-1){
          printf("id introuvable\n");
          return;
     }
     char line[256];
     FILE *fich,*F;
     fich=fopen("test.txt","r");
     F=fopen("temptest.txt","a");
     while(fgets(line,sizeof(line),fich)!= NULL){
         sscanf(line,"%d;%99[^;];%99[^;];%d/%d/%d;%99[^\n]",&tache.id,tache.titre,tache.description,
             &tache.deadline.day,&tache.deadline.month,&tache.deadline.year,tache.statut);
         if(tache.id!=id_delete){
             fprintf(F,"%d;%s;%s;%d/%d/%d;%s\n",tache.id,tache.titre,tache.description,
                 tache.deadline.day,tache.deadline.month,tache.deadline.year,tache.statut);
         }
     }

     fclose(fich);
     fclose(F);
     if(remove("test.txt") != 0){
         printf("Erreur de suppression");
         return;
     }
     if(rename("temptest.txt", "test.txt")!=0){
         printf("Erreur de suppression");
         return;
     }
     printf("Supression effectue avec succes\n");
 }
void rech_affichage_id()
{
    Todo tache;
    FILE *fich;
    int id_srch, cpt = 0;
    char line[256];
    fich = fopen("test.txt", "r");
    printf("Entrer l\id de la tache recherche: ");
    scanf("%d", &id_srch);
    if (fich == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
    }
    while (fgets(line, sizeof(line), fich) != NULL)
    {
        sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^;]", &tache.id, tache.titre, tache.description, &tache.deadline.day,
               &tache.deadline.month, &tache.deadline.year, tache.statut);
        if (tache.id == id_srch)
        {
            printf("%s", line);
            cpt = 1; // id existe
        }
    }
    if (cpt == 0)
    {
        printf("Id non existant\n");
    }
    fclose(fich);
}
void rech_affichage_titre()
{
    Todo tache;
    FILE *fich;
    char tit_srch[100];
    int cpt = 0;
    char line[100];
    fich = fopen("test.txt", "r");
    printf("Entrer le titre de la tache recherche: ");
    scanf("%s", tit_srch);
    if (fich == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
    }
    while (fgets(line, sizeof(line), fich) != NULL)
    {
        sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^;]", &tache.id, tache.titre, tache.description, &tache.deadline.day,
               &tache.deadline.month, &tache.deadline.year, tache.statut);
        if (strcmp(tache.titre, tit_srch) == 0)
        {
            printf("%s", line);
            cpt = 1; // id existe
        }
    }
    if (cpt == 0)
    {
        printf("titre non existant\n");
    }
    fclose(fich);
}
void tri_alpha()
{
    Todo tache;
    FILE *fich;
    char line[100];
    fich = fopen("test.txt", "r");
    if (fich == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    char titles[100][100];
    int nbr_tit = 0;
    while (fgets(line, sizeof(line), fich) != NULL)
    {
        sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^;]", &tache.id, tache.titre, tache.description, &tache.deadline.day,
               &tache.deadline.month, &tache.deadline.year, tache.statut);
        strcpy(titles[nbr_tit], tache.titre);
        nbr_tit++;
    }
    for (int i = 0; i < nbr_tit - 1; i++)
    { // nbr_tit-1
        for (int j = i + 1; j < nbr_tit; j++)
        {
            if (strcmp(titles[i], titles[j]) > 0)
            {
                char temp[100];
                strcpy(temp, titles[i]);
                strcpy(titles[i], titles[j]);
                strcpy(titles[j], temp);
            }
        }
    }
    printf("T�ches tri�es par ordre alphab�tique :\n");
    for (int i = 0; i < nbr_tit; i++)
    {
        printf("%s\n", titles[i]);
    }
    fclose(fich);
}
 int compare_dates(const Todo a, const Todo b) {
     if (a.deadline.year != b.deadline.year)
         return a.deadline.year - b.deadline.year;
     if (a.deadline.month != b.deadline.month)
         return a.deadline.month - b.deadline.month;
     return a.deadline.day - b.deadline.day;
 }
 void swap(Todo *todo1,Todo *todo2){
     Todo tmp = *todo1;
     *todo1 = *todo2;
     *todo2 = tmp;
 }

  void tri_deadline(){
     FILE *fich;
     char line[100];
     int cpt=0;
     Todo taches[100];

     fich=fopen("test.txt","r");
     if (fich == NULL) {
         printf("Erreur lors de l'ouverture du fichier");
         return 1;
     }
     while(fgets(line,sizeof(line),fich)!=NULL){
          sscanf(line,"%d;%99[^;];%99[^;];%d/%d/%d;%99[^\n]",&taches[cpt].id,taches[cpt].titre,taches[cpt].description,&taches[cpt].deadline.day,
                &taches[cpt].deadline.month,&taches[cpt].deadline.year,taches[cpt].statut);
          cpt++;
     }
     fclose(fich);

    for(int i=0;i<cpt-1;i++){//cpt-1
             for(int j=0;j<cpt -i -1;j++)
                 if((taches[j].deadline.year>taches[j +1].deadline.year) || \
                (taches[j].deadline.year==taches[j +1].deadline.year  && taches[j].deadline.month>taches[j +1].deadline.month) ||\
                (taches[j].deadline.year==taches[j +1].deadline.year  &&\
                 taches[j].deadline.month==taches[j +1].deadline.month && taches[j].deadline.day>taches[j +1].deadline.day)){
                    swap(&taches[j],&taches[j+1]);
                  }
    }

    for (int i = 0; i < cpt; i++) {
         printf("%d;%s;%s;%d/%d/%d;%s\n", taches[i].id, taches[i].titre, taches[i].description,
                taches[i].deadline.day, taches[i].deadline.month, taches[i].deadline.year,
                taches[i].statut);
     }
 }
int main()
{
    int choix, ch_afchg, ch_modif, ch_rech, ch_statq;
    int ch_continuer = 1;
// Menu principal
menu:
    printf("**********Gestion de Taches ToDo*************\n");
    printf("1--Ajouter une nouvelle tache\n");
    printf("2--Ajouter plusieurs nouvelles taches\n");
    printf("3--Afficher la liste de toutes les taches\n");
    printf("4--Modifier une tache\n");
    printf("5--Supprimer une tache par identifiant\n");
    printf("6--Rechercher les taches\n");
    printf("7--Statistiques\n");
    printf("0--Quitter\n");
    printf("Entrer votre choix:");
    scanf("%d", &choix);
    switch (choix)
    {
    case 0:
        break;
    case 1:
        add_tache();
        printf("Ajout avec succes\n");
        goto menu;
    case 2:
        add_tache();
        do
        {
            printf("Entrer 1 pour continuer / 0 pour sortir : ");
            scanf("%d", &ch_continuer);
            if (ch_continuer == 1)
            {
                add_tache();
                printf("Ajout avec succes\n");
            }
            else if (ch_continuer != 0)
            {
                printf("Entrez une valeur valide !\n");
            }
        } while (ch_continuer != 0);
        goto menu;
    case 3:
        affichage_taches();
    menu_affichage:
        printf("1--Trier les taches par ordre alphab�tique\n");
        printf("2--Trier les taches par deadline\n");
        printf("3--Afficher les taches dont le deadline est dans 3 jours ou moins\n");
        scanf("%d", &ch_afchg);
        switch (ch_afchg)
        {
        case 1:
            tri_alpha();
            goto menu_affichage;
        case 2:
            tri_deadline();
            goto menu_affichage;
        case 3:
            printf("3/3");
            goto menu_affichage;
        default:
            printf("Entrer un choix valide\n");
            goto menu_affichage;
        }
        goto menu;
    case 4:
    menu_modification:
        printf("\t1--Modifier la description d\'une tache\n");
        printf("\t2--Modifier le statut d\�une tache\n");
        printf("\t3--Modifier le deadline d\�une tache\n");
        printf("\tEntrer votre choix:\n\t");
        scanf("%d", &ch_modif);
        switch (ch_modif)
        {
        case 1:
            update_desc();
            goto menu_modification;
        case 2:
            update_stat();
            goto menu_modification;
        case 3:
            printf("4/3");
            goto menu_modification;
        default:
            printf("Entrer un choix valide\n");
            goto menu_modification;
        }
        goto menu;
    case 5:
                    delete_tache();
        goto menu;
    case 6:
    menu_recherche:
        printf("1--Rechercher une t�che par son Identifiant\n");
        printf("2--Rechercher une t�che par son Titre\n");
        scanf("%d", &ch_rech);
        switch (ch_rech)
        {
        case 1:
            rech_affichage_id();
            goto menu_recherche;
        case 2:
            rech_affichage_titre();
            goto menu_recherche;
        default:
            printf("Entrer un choix valide\n");
            goto menu_recherche;
        }
        goto menu;
    case 7:
    menu_statistiques:
        printf("1--Afficher le nombre total des taches\n");
        printf("2--Afficher le nombre de taches compl�tes et incompletes\n");
        printf("3--Afficher le nombre de jours restants jusqu'au d�lai de chaque tache\n");
        scanf("%d", &ch_statq);
        switch (ch_statq)
        {
        case 1:
            printf("7/1");
            goto menu_statistiques;
        case 2:
            printf("7/2");
            goto menu_statistiques;
        case 3:
            printf("7/3");
            goto menu_statistiques;
        default:
            printf("Entrer un choix valide\n");
            goto menu_statistiques;
        }
        goto menu;
    default:
        printf("Entrer un choix valide\n");
        goto menu;
    }

    return 0;
}
