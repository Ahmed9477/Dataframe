//CDataframe
#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"

void display_menu() {
    printf("\nMenu:\n");
    printf("1. Afficher le Dataframe\n");
    printf("2. sauvegarder le Dataframe en excel\n");
    printf("3. charger un Dataframe par excel\n");
    printf("4. creer un dataframe vide\n");
    printf("5. remplir le dataframe\n");
    printf("6. Hard fill dataframe\n");
    printf("8. montre que certaine ligne\n");
    printf("9. montre certain collone\n");
    printf("10. suprimer une colonne\n");
    printf("11. suprimer une ligne\n");
    printf("12. Exit\n");
    printf("que veux tu faire: ");
}

int main() {
    // creation du dataframe
    CDataframe *df = NULL;
    int choice;

    do {
        display_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if (df != NULL) {
                    printf("Dataframe:\n");
                    print_dataframe(df);
                } else {
                    printf("Dataframe est vide.\n");
                }
                break;
            case 2:
                if (df != NULL) {
                    if (save_dataframe_to_csv(df, "dataframe.csv")) {
                        printf("Dataframe sauvegarder en fichier dataframe.csv\n");
                    } else {
                        printf("sauvergarde rater\n");
                    }
                } else {
                    printf("Dataframe est vide rien a sauvegarder\n");
                }
                break;
            case 3:
                delete_dataframe(&df);
                df = load_dataframe_from_csv("dataframe.csv");
                if (df != NULL) {
                    printf("Dataframe charger:\n");
                    print_dataframe(df);
                } else {
                    printf("charcherment rater\n");
                }
                break;
            case 4:
                delete_dataframe(&df);
                df = create_dataframe();
                printf("creation reussit d'un dataframe vide.\n");
                break;
            case 5:
                if (df != NULL) {
                    fill_dataframe_with_user_input(df);
                } else {
                    printf("Dataframe est vide. Cree un dataframe d'abord.\n");
                }
                break;
            case 6:
                if (df != NULL) {
                    hard_fill_dataframe(df);
                } else {
                    printf("Dataframe est vide. Cree un dataframe d'abord.\n");
                }
                break;
            case 8:
                if (df != NULL) {
                    int rows_limit;
                    printf("Entre la limite de ligne: ");
                    scanf("%d", &rows_limit);
                    display_partial_rows(df, rows_limit);
                } else {
                    printf("Dataframe est vide.\n");
                }
                break;
            case 9:
                if (df != NULL) {
                    int cols_limit;
                    printf("Entre la limite de colonne: ");
                    scanf("%d", &cols_limit);
                    display_partial_columns(df, cols_limit);
                } else {
                    printf("Dataframe est vide.\n");
                }
                break;
            case 10:
                if (df != NULL) {
                    int index;
                    printf("Entre l'index de la colonne a suprimer: ");
                    scanf("%d", &index);
                    delete_column_from_dataframe(df, index);
                } else {
                    printf("Dataframe est vide.\n");
                }
                break;
            case 11:
                if (df != NULL) {
                    int index;
                    printf("Entre l'index de la ligne à suprimer: ");
                    scanf("%d", &index);
                    delete_row_from_dataframe(df, index);
                } else {
                    printf("Dataframe est vide.\n");
                }
                break;
            case 12:
                printf("Exiting...\n");
                break;
            default:
                printf("choix invalide\n");
        }

    } while(choice != 12);

    // Cleanup
    delete_dataframe(&df);

    return 0;
}



