//CDataframe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column_operations.h"

// Crée une nouvelle structure de colonne avec le type spécifié
COLUMN_OPS *create_column_ops(COL_TYPE type) {
    COLUMN_OPS *col = (COLUMN_OPS *)malloc(sizeof(COLUMN_OPS));
    if (col == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    col->type = type;
    col->data = NULL;
    col->size = 0;
    return col;
}

// Insère une valeur dans la colonne
int insert_value_ops(COLUMN_OPS *col, void *value) {
    if (col == NULL || value == NULL) return 0; // Colonne ou valeur invalide
    int new_size = col->size + 1;
    void **new_data = realloc(col->data, new_size * sizeof(void *));
    if (new_data == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(1);
    }
    col->data = new_data;
    char *new_value = malloc(strlen((char *)value) + 1); // Allouer de la mémoire pour la chaîne
    if (new_value == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strcpy(new_value, (char *)value); // Copier la chaîne
    col->data[col->size++] = new_value;
    return 1; // Valeur ajoutée avec succès
}

// Supprime une colonne et libère la mémoire
void delete_column_ops(COLUMN_OPS **col) {
    if (*col == NULL) return;
    free((*col)->data);
    free(*col);
    *col = NULL;
}


// Affiche les valeurs d'une colonne
void print_col_ops(COLUMN_OPS *col, int row) {
    if (col == NULL || col->data == NULL) return;
    if (row >= 0 && row < col->size) {
        switch (col->type) {
            case UINT_TYPE:
                printf("%u\n", *((unsigned int *)col->data[row]));
                break;
            case INT_TYPE:
                printf("%d\n", *((int *)col->data[row]));
                break;
            case CHAR_TYPE:
                printf("%c\n", *((char *)col->data[row]));
                break;
            case FLOAT_TYPE:
                printf("%f\n", *((float *)col->data[row]));
                break;
            case DOUBLE_TYPE:
                printf("%lf\n", *((double *)col->data[row]));
                break;
            case STRING_TYPE:
                printf("%s\n", (char *)col->data[row]);
                break;
            case STRUCT_TYPE:
                // Gérer l'affichage des types struct
                break;
            default:
                fprintf(stderr, "Invalid column type\n");
                break;
        }
    } else {
        for (int i = 0; i < col->size; i++) {
            switch (col->type) {
                case UINT_TYPE:
                    printf("%u\n", *((unsigned int *)col->data[i]));
                    break;
                case INT_TYPE:
                    printf("%d\n", *((int *)col->data[i]));
                    break;
                case CHAR_TYPE:
                    printf("%c\n", *((char *)col->data[i]));
                    break;
                case FLOAT_TYPE:
                    printf("%f\n", *((float *)col->data[i]));
                    break;
                case DOUBLE_TYPE:
                    printf("%lf\n", *((double *)col->data[i]));
                    break;
                case STRING_TYPE:
                    printf("%s\n", (char *)col->data[i]);
                    break;
                case STRUCT_TYPE:
                    // Gérer l'affichage des types struct
                    break;
                default:
                    fprintf(stderr, "Invalid column type\n");
                    break;
            }
        }
    }
}
