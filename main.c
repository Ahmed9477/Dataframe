#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"

// Fonction pour afficher le menu des options
void display_menu() {
    printf("\nMenu:\n");
    printf("1. Afficher le Dataframe\n");
    printf("2. Sauvegarder le Dataframe en CSV\n");
    printf("3. Charger un Dataframe à partir d'un CSV\n");
    printf("4. Créer un Dataframe vide\n");
    printf("5. Remplir le Dataframe avec des entrées utilisateur\n");
    printf("6. Remplir le Dataframe avec des données prédéfinies\n");
    printf("7. Afficher certaines lignes\n");
    printf("8. Afficher certaines colonnes\n");
    printf("9. Supprimer une colonne\n");
    printf("10. Supprimer une ligne\n");
    printf("11. Quitter\n");
    printf("Que voulez-vous faire : ");
}

int main() {
    // Pointeur vers le dataframe, initialement nul
    CDataframe *df = NULL;
    int choice;

    do {
        display_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                // Afficher le dataframe
                if (df != NULL) {
                    printf("Dataframe:\n");
                    print_dataframe(df);
                } else {
                    printf("Le Dataframe est vide.\n");
                }
                break;
            case 2:
                // Sauvegarder le dataframe en fichier CSV
                if (df != NULL) {
                    if (save_dataframe_to_csv(df, "dataframe.csv")) {
                        printf("Dataframe sauvegardé dans le fichier dataframe.csv\n");
                    } else {
                        printf("Échec de la sauvegarde\n");
                    }
                } else {
                    printf("Le Dataframe est vide, rien à sauvegarder\n");
                }
                break;
            case 3:
                // Charger un dataframe à partir d'un fichier CSV
                delete_dataframe(&df);
                df = load_dataframe_from_csv("dataframe.csv");
                if (df != NULL) {
                    printf("Dataframe chargé:\n");
                    print_dataframe(df);
                } else {
                    printf("Échec du chargement\n");
                }
                break;
            case 4:
                // Créer un dataframe vide
                delete_dataframe(&df);
                df = create_dataframe();
                printf("Création réussie d'un dataframe vide.\n");
                break;
            case 5:
                // Remplir le dataframe avec des entrées utilisateur
                if (df != NULL) {
                    fill_dataframe_with_user_input(df);
                } else {
                    printf("Le Dataframe est vide. Créez un dataframe d'abord.\n");
                }
                break;
            case 6:
                // Remplir le dataframe avec des données prédéfinies
                if (df != NULL) {
                    hard_fill_dataframe(df);
                } else {
                    printf("Le Dataframe est vide. Créez un dataframe d'abord.\n");
                }
                break;
            case 7:
                // Afficher un nombre limité de lignes
                if (df != NULL) {
                    int rows_limit;
                    printf("Entrez la limite de lignes : ");
                    scanf("%d", &rows_limit);
                    display_partial_rows(df, rows_limit);
                } else {
                    printf("Le Dataframe est vide.\n");
                }
                break;
            case 8:
                // Afficher un nombre limité de colonnes
                if (df != NULL) {
                    int cols_limit;
                    printf("Entrez la limite de colonnes : ");
                    scanf("%d", &cols_limit);
                    display_partial_columns(df, cols_limit);
                } else {
                    printf("Le Dataframe est vide.\n");
                }
                break;
            case 9:
                // Supprimer une colonne du dataframe
                if (df != NULL) {
                    int index;
                    printf("Entrez l'index de la colonne à supprimer : ");
                    scanf("%d", &index);
                    delete_column_from_dataframe(df, index);
                } else {
                    printf("Le Dataframe est vide.\n");
                }
                break;
            case 10:
                // Supprimer une ligne du dataframe
                if (df != NULL) {
                    int index;
                    printf("Entrez l'index de la ligne à supprimer : ");
                    scanf("%d", &index);
                    delete_row_from_dataframe(df, index);
                } else {
                    printf("Le Dataframe est vide.\n");
                }
                break;
            case 11:
                // Quitter le programme
                printf("Quitter...\n");
                break;
            default:
                printf("Choix invalide\n");
        }

    } while(choice != 11);

    // Libérer la mémoire allouée pour le dataframe
    delete_dataframe(&df);

    return 0;
}


