#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
enum Statut_tache{
    A_REALISER=1,EN_COURS_DE_REALISATION=2,FINALISEE=3//1.2.3 pour lentree d'utilisateur
};
typedef struct{
    int day,month,year;
}Date;
typedef struct {
    int id;
    char titre[100];
    char description[100];
    Date deadline;//day/month/year +(time)//struct date-->date deadline
//    enum Statut_tache statut;//retourne int +switch pour afficher "a realiser"
}Todo;
//fonction recherche par id
int search_by_id(int id_rech){
    Todo tache;
    char line[256];
    FILE *fich;
    fich=fopen("test.txt","r");
    while(fgets(line,sizeof(line),fich)!= NULL){
        sscanf(line,"%d;%99[^;];%99[^;]",&tache.id,tache.titre,tache.description,&tache.deadline.day,
               &tache.deadline.month,&tache.deadline.year);
        if(tache.id==id_rech){

            fclose(fich);
            return 1;
        }
    }
    fclose(fich);
    return -1;
}
void add_tache(Todo tache){
    FILE *fich;

        top:
    printf("\nEntrez id de la tache:");
    scanf("%d",&tache.id);
    if(search_by_id(tache.id)==1){
        printf("\nCe id existe deja!");
        goto top;
    }
    fich=fopen("test.txt","a");
    if (fich == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
    }
    printf("\nEntrezle titre :");
    scanf(" %99[^\n]",tache.titre);
//    getchar();
//    fgets(tache.titre,sizeof(tache.titre),stdin);
    printf("\nEntrez la description:");
    scanf(" %99[^\n]",tache.description);
    printf("\nEntrez deadline:");
    scanf("%d/%d/%d",&tache.deadline.day,&tache.deadline.month,&tache.deadline.year);
//    fgets(tache.description,sizeof(tache.description),stdin);
    fprintf(fich,"%d;%s;%s;%d/%d/%d\n",tache.id,tache.titre,tache.description,tache.deadline.day,
            tache.deadline.month,tache.deadline.year);
    fclose(fich);
return;
}
void affichage_taches(Todo tache){
    FILE *fich;
    char line[100];
    fich=fopen("test.txt","r");
    if(fich==NULL){
        printf("Erreur lors de l'ouverture du fichier");
    }
    while(fgets(line,sizeof(line),fich)!= NULL){
        printf("%s",line);
    }
    fclose(fich);
}
//void update_desc(Todo tache){
//    FILE *fich,*F;
//    char line[256];  //line[100]
//    int id_updt;
//    printf("Entrer l\'id de la tache a modifier");
//    scanf("%d",&id_updt);
//    fich=fopen("test.txt","r");
//    F=fopen("temptest.txt","w");
//    if (fich == NULL || F == NULL) {
//        printf("Impossible d'ouvrir le fichier.\n");
//        return; //return !
//    }
//    while(fgets(line,sizeof(line),fich)!= NULL){
//        sscanf(line,"%d;%99[^;];%99[^;]",&tache.id,tache.titre,tache.description,
//               &tache.deadline.day,&tache.deadline.month,&tache.deadline.year);
//        if(tache.id==id_updt){
////            tache.id=id_updt;
//            printf("Entrer la nouvelle description:");
//            scanf(" %99[^\n]",tache.description);
//
//        }
//
//        fprintf(F,"%d;%s;%s;%d/%d/%d\n",tache.id,tache.titre,tache.description,
//                    tache.deadline.day,tache.deadline.month,tache.deadline.year);
//    }
//    fclose(fich);
//    fclose(F);
////    remove("test.txt");
////    rename("temptest.txt", "test.txt");
//}
void delete_tache(Todo tache){
    char line[256];
    FILE *fich,*F;
    fich=fopen("test.txt","r");
    F=fopen("temptest.txt","a");
    int id_delete;
    printf("Entrer l\'id de la tache a supprimer");
    scanf("%d",&id_delete);
    while(fgets(line,sizeof(line),fich)!= NULL){
        sscanf(line,"%d;%99[^;];%99[^;]",&tache.id,tache.titre,tache.description,
              &tache.deadline.day,&tache.deadline.month,&tache.deadline.year);
        if(tache.id!=id_delete){
            fprintf(F,"%d;%s;%s;%d/%d/%d\n",tache.id,tache.titre,tache.description,
                   tache.deadline.day,tache.deadline.month,tache.deadline.year);
        }
    }
    fclose(fich);
    fclose(F);
    printf("Supression effectue avec succes\n");
}
void rech_affichage_id(Todo tache){
    FILE *fich;
    int id_srch,cpt=0;
    char line[100];
    fich=fopen("test.txt","r");
    printf("Entrer l\id de la tache recherche: ");
    scanf("%d",&id_srch);
    if(fich==NULL){
        printf("Erreur lors de l'ouverture du fichier");
    }
    while(fgets(line,sizeof(line),fich)!= NULL){
        sscanf(line,"%d;%99[^;];%99[^;]",&tache.id,tache.titre,tache.description,&tache.deadline.day,
               &tache.deadline.month,&tache.deadline.year);
        if(tache.id==id_srch){
            printf("%s",line);
            cpt=1;//id existe
        }
    }
    if(cpt==0){
        printf("Id non existant\n");
    }
    fclose(fich);
}
void rech_affichage_titre(Todo tache){
    FILE *fich;
    char tit_srch[100];
    int cpt=0;
    char line[100];
    fich=fopen("test.txt","r");
    printf("Entrer le titre de la tache recherche: ");
    scanf("%s",tit_srch);
    if(fich==NULL){
        printf("Erreur lors de l'ouverture du fichier");
    }
    while(fgets(line,sizeof(line),fich)!= NULL){
        sscanf(line,"%d;%99[^;];%99[^;]",&tache.id,tache.titre,tache.description,&tache.deadline.day,
               &tache.deadline.month,&tache.deadline.year);
        if(strcmp(tache.titre, tit_srch)==0){
            printf("%s",line);
            cpt=1;//id existe
        }
    }
    if(cpt==0){
        printf("titre non existant\n");
    }
    fclose(fich);
}
int main()
{
    Todo tache;

    int choix,ch_afchg,ch_modif,ch_rech,ch_statq;
    int ch_continuer = 1;
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
            printf("Ajout avec succes\n");
            goto menu;
        case 2:
             add_tache(tache);
             do {
                printf("Entrer 1 pour continuer / 0 pour sortir : ");
                scanf("%d", &ch_continuer);
                if (ch_continuer == 1) {
                    add_tache(tache);
                    printf("Ajout avec succes\n");
                }
                else if (ch_continuer != 0) {
                    printf("Entrez une valeur valide !\n");
                }
            }while (ch_continuer != 0);
            goto menu;
        case 3:
            affichage_taches(tache);
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
//                    update_desc(tache);
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
            delete_tache(tache);
            goto menu;
        case 6:
            menu_recherche:
            printf("1--Rechercher une tâche par son Identifiant\n");
            printf("2--Rechercher une tâche par son Titre\n");
            scanf("%d",&ch_rech);
            switch(ch_rech){
                case 1:
                    rech_affichage_id(tache);
                    goto menu_recherche;
                case 2:
                    rech_affichage_titre(tache);
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
