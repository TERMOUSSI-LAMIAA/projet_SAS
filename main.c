#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

 void swap(Todo *todo1,Todo *todo2){
     Todo tmp = *todo1;
     *todo1 = *todo2;
     *todo2 = tmp;
 }



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
    printf("\nEntrez le titre :");
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
    printf("Ajout avec succes\n");
    nbr_tot_taches();
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
    printf("Entrer l\'id de la tache a modifier : ");
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
            printf("Entrer la nouvelle description : ");
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
    printf("Entrer l\'id de la tache a modifier: ");
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
                (tache.statut, "A REALISER");
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
void update_deadline(){
    Todo tache;
    FILE *fich, *F;
    int id_updt;
    char line[256];
    printf("Entrer l\'id de deadline a modifier: ");
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
     while (fgets(line, sizeof(line), fich) != NULL)
    {
        sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^\n]", &tache.id, tache.titre, tache.description,
               &tache.deadline.day, &tache.deadline.month, &tache.deadline.year, tache.statut);
        if (tache.id == id_updt)
        {
            printf("Entrer le nouveau deadline:");
            scanf("%d/%d/%d",&tache.deadline.day, &tache.deadline.month, &tache.deadline.year);
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
     printf("Entrer l\'id de la tache a supprimer: ");
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
     nbr_tot_taches();
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
void tri_alpha()///////!!!!!!!!!!
{
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
        for(int j=0;j<cpt -1-i;j++)
        {
            if (strcmp(taches[j].titre,taches[j+1].titre) > 0)
            {
               swap(&taches[j],&taches[j+1]);
            }
        }
    }
    printf("Taches triees par ordre alphabetique :\n");
    for (int i = 0; i < cpt; i++)
    {
        printf("%d;%s;%s;%d/%d/%d;%s\n", taches[i].id, taches[i].titre, taches[i].description,
        taches[i].deadline.day, taches[i].deadline.month, taches[i].deadline.year,taches[i].statut);
    }
}
// int compare_dates(const Todo a, const Todo b) {
//     if (a.deadline.year != b.deadline.year)
//         return a.deadline.year - b.deadline.year;
//     if (a.deadline.month != b.deadline.month)
//         return a.deadline.month - b.deadline.month;
//     return a.deadline.day - b.deadline.day;
// }
 //tri deadline

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
             for(int j=0;j<cpt -1-i;j++)//cpt-1-i
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
 int nbr_tot_taches(){
     FILE *fich;
     char line[100];
     int cpt=0;
     fich=fopen("test.txt","r");
     if (fich == NULL) {
         printf("Erreur lors de l'ouverture du fichier");
         return 1;
     }
     while(fgets(line,sizeof(line),fich)!=NULL){
        cpt++;
     }
    fclose(fich);
    return cpt;
 }
 void nbr_tach_com_incomp(){
     Todo tache;
     FILE *fich;
     char line[100];
     int cpt_comp=0,cpt_incomp=0;
     fich=fopen("test.txt","r");
     if (fich == NULL) {
         printf("Erreur lors de l'ouverture du fichier");
         return 1;
     }
     while(fgets(line,sizeof(line),fich)!=NULL){
            sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^\n]", &tache.id, tache.titre, tache.description, &tache.deadline.day,
            &tache.deadline.month, &tache.deadline.year, tache.statut);
             if(strcmp(tache.statut,"FINALISEE")==0){
                cpt_comp++;

            }else{
                  cpt_incomp++;
            }
    }
    fclose(fich);
    printf("le nombre de taches complete :%d\n",cpt_comp);
    printf("le nombre de taches incompletes :%d\n",cpt_incomp);

 }

int isDateWithin3Days(Date givenDate){
// get current date
time_t currentTime;
struct tm *timeInfo;
time(&currentTime);
// Add one to avoid count today
currentTime = currentTime + ( 24 * 3600);

time_t threeDaysFromNow = currentTime + (3 * 24 * 3600);
struct tm *cu_date;
cu_date = localtime(&currentTime);

// cast Date to tm
struct tm date_tm = {0};
date_tm.tm_year = givenDate.year - 1900;
date_tm.tm_mon = givenDate.month -1;
date_tm.tm_mday = givenDate.day;
date_tm.tm_hour = cu_date->tm_hour;
date_tm.tm_min = cu_date->tm_min;
date_tm.tm_sec = cu_date->tm_sec;
time_t toCheck = mktime(&date_tm);


/*

printf("\t t = %d/%d/%d\n",cu_date->tm_mday,cu_date->tm_mon,cu_date->tm_year+1900);

printf("\t c = %d/%d/%d\n",date_tm.tm_mday,date_tm.tm_mon,date_tm.tm_year+1900);

struct tm *date_3;
date_3 = localtime(&threeDaysFromNow);
printf("\t 3_t = %d/%d/%d\n\n",date_3->tm_mday,date_3->tm_mon,date_3->tm_year+1900);

printf("%d",toCheck < threeDaysFromNow  && toCheck > currentTime);

printf("\t%lld\n",currentTime);
printf("\t%lld\n",toCheck);
printf("\t%lld\n",threeDaysFromNow);*/
// return true if the given date is in 3days intrval from now
return toCheck <= threeDaysFromNow && toCheck >= currentTime;
}


void showTachesWithIn3Days(){
     Todo tache;
     FILE *fich;
     char line[100];
     fich=fopen("test.txt","r");
     if (fich == NULL) {
         printf("Erreur lors de l'ouverture du fichier");
         return 1;
     }
     printf("Taches with in 3 dayes :\n");
     while(fgets(line,sizeof(line),fich)!=NULL){
            sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^\n]", &tache.id, tache.titre, tache.description, &tache.deadline.day,
            &tache.deadline.month, &tache.deadline.year, tache.statut);
             if(isDateWithin3Days(tache.deadline)){
               printf("\t%s",line);
            }

    }
    fclose(fich);
}
void deadline_3days(){
    time_t current_time = time(NULL); //La fonction time(NULL) renvoie le nombre de secondes écoulées depuis le 1er janvier

                    printf("les tâches dont le deadline est dans 3 jours ou moins:\n");
         Todo tache;
     FILE *fich;
     char line[100];
     fich=fopen("test.txt","r");
     if (fich == NULL) {
         printf("Erreur lors de l'ouverture du fichier");
         return 1;
     }
     printf("Taches with in 3 dayes :\n");

     while(fgets(line,sizeof(line),fich)!=NULL){
            sscanf(line, "%d;%99[^;];%99[^;];%d/%d/%d;%99[^\n]", &tache.id, tache.titre, tache.description, &tache.deadline.day,
            &tache.deadline.month, &tache.deadline.year, tache.statut);

                        struct tm taskDeadline = {0};
                        taskDeadline.tm_year = tache.deadline.year - 1900;
                        taskDeadline.tm_mon = tache.deadline.month - 1;// La raison de la soustraction de 1 provient du fait que la structure\
                                                                    tm de la bibliothèque <time.h> utilise des mois allant de 0 à 11
                        taskDeadline.tm_mday = tache.deadline.day;
                        time_t taskTime = mktime(&taskDeadline);

                        // Calculate the difference in seconds
                        int differenceInSeconds = difftime(taskTime, current_time);

                        printf("%lld  - %lld =  %lld   c = %lld\n\n",taskTime, current_time,differenceInSeconds,3 * 24 * 3600);
                        // Check if the difference is within 3 days (3 days * 24 hours * 3600 seconds)
                        if (differenceInSeconds <= 3 * 24 * 3600 && differenceInSeconds > current_time) {
                            printf(" %s\n\n", line );
                        }


    }
    fclose(fich);


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
//        exit(0);

    case 1:
        add_tache();
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
        printf("\t1--Trier les taches par ordre alphabetique\n");
        printf("\t2--Trier les taches par deadline\n");
        printf("\t3--Afficher les taches dont le deadline est dans 3 jours ou moins\n");
        printf("\tEntrer votre choix:");
        scanf("%d", &ch_afchg);
        switch (ch_afchg)
        {
        case 1:
            tri_alpha();
            goto menu;
        case 2:
            tri_deadline();
            goto menu_affichage;
        case 3:
            deadline_3days();
            goto menu_affichage;
        default:
            printf("Entrer un choix valide\n");
            goto menu_affichage;
        }
        goto menu;
    case 4:
    menu_modification:
        printf("\t1--Modifier la description d\'une tache\n");
        printf("\t2--Modifier le statut d\'une tache\n");
        printf("\t3--Modifier le deadline d\'une tache\n");
        printf("\tEntrer votre choix: ");
        scanf("%d", &ch_modif);
        switch (ch_modif)
        {
        case 1:
            update_desc();
            goto menu;
        case 2:
            update_stat();
            goto menu;
        case 3:
            update_deadline();
            goto menu;
        default:
            printf("Entrer un choix valide\n");
            goto menu_modification;
        }
//        goto menu;
    case 5:
            delete_tache();
        goto menu;
    case 6:
    menu_recherche:
        printf("\t1--Rechercher une tache par son Identifiant\n");
        printf("\t2--Rechercher une tache par son Titre\n");
        printf("\tEntrer votre choix: ");
        scanf("%d", &ch_rech);
        switch (ch_rech)
        {
        case 1:
            rech_affichage_id();
            goto menu;
        case 2:
            rech_affichage_titre();
            goto menu;
        default:
            printf("Entrer un choix valide\n");
            goto menu_recherche;
        }
        goto menu;
    case 7:
    menu_statistiques:
        printf("\t1--Afficher le nombre total des taches\n");
        printf("\t2--Afficher le nombre de taches completes et incompletes\n");
        printf("\t3--Afficher le nombre de jours restants jusqu'au delai de chaque tache\n");
        printf("\tEntrer votre choix: ");
        scanf("%d", &ch_statq);
        switch (ch_statq)
        {
        case 1:
            printf("Nombre total de tache : %d\n",nbr_tot_taches());
            goto menu;
        case 2 :
            nbr_tach_com_incomp();
            goto menu;
        case 3:
            goto menu;
        default:
            printf("Entrer un choix valide\n");
            goto menu_statistiques;
        }
//        goto menu;!!
    default:
        printf("Entrer un choix valide\n");
        goto menu;
    }

    return 0;
}
