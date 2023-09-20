#include <stdio.h>
#include <stdlib.h>
#include <time.h>
enum Statut_tache{
    A_REALISER=1,EN_COURS_DE_REALISATION=2,FINALISEE=3//1.2.3 pour lentree d'utilisateur
};
//typedef struct{
//    int day;
//    int month;
//    int year;
//}Date;
typedef struct {
    int id;
    char titre[30];
    char description[60];
//    Date deadline;//day/month/year +(time)//struct date-->date deadline
//    enum Statut_tache statut;//retourne int +switch pour afficher "a realiser"
}Todo;
//fonction recherche par id
int search_by_id(int id_rech){
        Todo tache;

    FILE *fich;
    fich=fopen("test.txt","r");
    do{
        fscanf(fich,"%d;%99[^;];%99[^;]",&tache.id,tache.titre,tache.description);
        printf("%d;%s;%s",tache.id,tache.titre,tache.description);
        if(tache.id==id_rech){
            fclose(fich);
            return 1;
        }
    }while(!feof(fich));
    fclose(fich);
    return -1;
}
void add_tache(Todo tache){
    FILE *fich;
    fich=fopen("test.txt","a");
    if (fich == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
    }
        top:
    printf("\nEntrez id de la tache:");
    scanf("%d",&tache.id);
    while(search_by_id(tache.id)==1){
        printf("\nCe id existe deja!");
        goto top;
    }
    printf("\nEntrezle titre :");
    scanf(" %99[^\n]",tache.titre);

//    getchar();
//    fgets(tache.titre,sizeof(tache.titre),stdin);
    printf("\nEntrez la description:");
    scanf(" %99[^\n]",tache.description);
//    fgets(tache.description,sizeof(tache.description),stdin);
    fprintf(fich,"%d;%s;%s\n",tache.id,tache.titre,tache.description);
    fclose(fich);
return;
}
int main()
{
    Todo tache;

    int choix,ch_afchg,ch_modif,ch_rech,ch_statq;
    //Menu principal
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
    scanf("%d",&choix);
    switch(choix){
        case 0:
            break;
        case 1:
            add_tache(tache);
            printf("Ajout avec succes");
        case 2:
            printf("2");
            goto menu;
        case 3:
            menu_affichage:
            printf("1--Trier les taches par ordre alphabétique\n");
            printf("2--Trier les taches par deadline\n");
            printf("3--Afficher les taches dont le deadline est dans 3 jours ou moins\n");
            scanf("%d",&ch_afchg);
            switch(ch_afchg){
                case 1:
                    printf("3/1");
                    goto menu_affichage;
                case 2:
                    printf("3/2");
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
            printf("1--Modifier la description d\'une tache\n");
            printf("2--Modifier le statut d\’une tache\n");
            printf("3--Modifier le deadline d\’une tache\n");
            scanf("%d",&ch_modif);
            switch(ch_modif){
                case 1:
                    printf("4/1");
                    goto menu_modification;
                case 2:
                    printf("4/2");
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
            printf("5");
            goto menu;
        case 6:
            menu_recherche:
            printf("1--Rechercher une tâche par son Identifiant\n");
            printf("2--Rechercher une tâche par son Titre\n");
            scanf("%d",&ch_rech);
            switch(ch_rech){
                case 1:
                    printf("6/1");
                    goto menu_recherche;
                case 2:
                    printf("6/2");
                    goto menu_recherche;
                default:
                    printf("Entrer un choix valide\n");
                    goto menu_recherche;
            }
            goto menu;
        case 7:
            menu_statistiques:
            printf("1--Afficher le nombre total des taches\n");
            printf("2--Afficher le nombre de taches complètes et incompletes\n");
            printf("3--Afficher le nombre de jours restants jusqu'au délai de chaque tache\n");
            scanf("%d",&ch_statq);
            switch(ch_statq){
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
