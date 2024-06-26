//CDataframe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"



// Crée une nouvelle structure de dataframe
CDataframe *create_dataframe() {
    CDataframe *df = (CDataframe *)malloc(sizeof(CDataframe));
    if (df == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    df->columns = NULL;
    df->num_columns = 0;
    return df;
}

// Ajoute une colonne au dataframe
int add_column_to_dataframe(CDataframe *df, COLUMN_OPS *col) {
    if (df == NULL || col == NULL) return 0;
    int new_size = df->num_columns + 1;
    COLUMN_OPS **new_columns = realloc(df->columns, new_size * sizeof(COLUMN_OPS *));
    if (new_columns == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(1);
    }
    df->columns = new_columns;
    df->columns[df->num_columns++] = col;
    return 1;
}
// Supprime le dataframe et libère la mémoire
void delete_dataframe(CDataframe **df) {
    if (*df == NULL) return;
    for (int i = 0; i < (*df)->num_columns; i++) {
        delete_column_ops(&((*df)->columns[i]));
    }
    free((*df)->columns);
    free(*df);
    *df = NULL;
}
// Affiche le dataframe
void print_dataframe(CDataframe *df) {
    if (df == NULL || df->columns == NULL) return;
    for (int i = 0; i < df->num_columns; i++) {
        printf("Column %d:\n", i + 1);
        print_col_ops(df->columns[i], -1); // Imprime toutes les lignes
    }
}

// Charge un dataframe depuis un fichier CSV
CDataframe *load_dataframe_from_csv(const char *filename) {
    if (filename == NULL) return NULL;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for reading\n");
        return NULL;
    }

    CDataframe *df = create_dataframe();
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            COLUMN_OPS *col = create_column_ops(STRING_TYPE);
            insert_value_ops(col, token);
            add_column_to_dataframe(df, col);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    return df;
}

// Enregistre un dataframe dans un fichier CSV
int save_dataframe_to_csv(CDataframe *df, const char *filename) {
    if (df == NULL || filename == NULL) return 0;
    FILE *file = fopen(filename, "a"); // Ouvre le fichier en mode ajout
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 0;
    }

    int max_rows = 0;
    for (int i = 0; i < df->num_columns; i++) {
        if (df->columns[i]->size > max_rows) {
            max_rows = df->columns[i]->size;
        }
    }
    for (int row = 0; row < max_rows; row++) {
        for (int col = 0; col < df->num_columns; col++) {
            COLUMN_OPS *current_col = df->columns[col];
            if (row < current_col->size) {
                switch (current_col->type) {
                    case INT_TYPE:
                        fprintf(file, "%d", *((int *)current_col->data[row]));
                        break;
                    case STRING_TYPE:
                        fprintf(file, "%s", (char *)current_col->data[row]);
                        break;
                    case FLOAT_TYPE:
                        fprintf(file, "%.4f", *((float *)current_col->data[row]));
                        break;
                    default:
                        fprintf(stderr, "Invalid column type\n");
                        fclose(file);
                        return 0;
                }
            }
            if (col < df->num_columns - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 1;
}
// Remplit le dataframe avec des entrées utilisateur
void fill_dataframe_with_user_input(CDataframe *df) {
    if (df == NULL) return;
    int num_cols;
    printf("Enter number of columns: ");
    scanf("%d", &num_cols);
    for (int i = 0; i < num_cols; i++) {
        int size;
        printf("Enter size of column %d: ", i + 1);
        scanf("%d", &size);
        COLUMN_OPS *col = create_column_ops(STRING_TYPE);
        for (int j = 0; j < size; j++) {
            char *value = (char *)malloc(100 * sizeof(char));
            printf("Enter value for column %d, row %d (Integer, String, or Float): ", i + 1, j + 1);
            scanf("%s", value);
            insert_value_ops(col, value);
        }
        add_column_to_dataframe(df, col);
    }
}
// Remplit le dataframe avec des valeurs prédéfinies
void hard_fill_dataframe(CDataframe *df) {
    if (df == NULL) return;
    COLUMN_OPS *col1 = create_column_ops(INT_TYPE);
    insert_value_ops(col1, &(int){52});
    insert_value_ops(col1, &(int){44});
    insert_value_ops(col1, &(int){15});
    add_column_to_dataframe(df, col1);

    COLUMN_OPS *col2 = create_column_ops(STRING_TYPE);
    insert_value_ops(col2, "Lima");
    insert_value_ops(col2, "Bravo");
    insert_value_ops(col2, "Zulu");
    add_column_to_dataframe(df, col2);

    COLUMN_OPS *col3 = create_column_ops(FLOAT_TYPE);
    insert_value_ops(col3, &(float){1.158});
    insert_value_ops(col3, &(float){9.135});
    insert_value_ops(col3, &(float){6.588});
    add_column_to_dataframe(df, col3);
}
// Affiche tout le dataframe
void display_entire_dataframe(CDataframe *df) {
    if (df == NULL || df->columns == NULL) return;
    printf("Entire Dataframe:\n");
    print_dataframe(df);
}
// Affiche un nombre limité de lignes du dataframe
void display_partial_rows(CDataframe *df, int limit) {
    if (df == NULL || limit <= 0) {
        printf("Invalid dataframe or limit.\n");
        return;
    }
    printf("Partial Dataframe (first %d rows):\n", limit);
    for (int i = 0; i < df->num_columns; i++) {
        printf("Column %d:\n", i + 1);
        print_col_ops(df->columns[i], limit);
    }
}
// Affiche un nombre limité de colonnes du dataframe
void display_partial_columns(CDataframe *df, int limit) {
    if (df == NULL || limit <= 0 || limit > df->num_columns) {
        printf("Invalid dataframe or limit.\n");
        return;
    }

    printf("Partial Dataframe (first %d columns):\n", limit);
    for (int i = 0; i < limit; i++) {
        printf("Column %d:\n", i + 1);
        print_col_ops(df->columns[i], -1); // Imprime toutes les lignes
    }
}
// Supprime une colonne du dataframe
void delete_column_from_dataframe(CDataframe *df, int index) {
    if (df == NULL || index < 0 || index >= df->num_columns) {
        printf("Invalid dataframe or index.\n");
        return;
    }

    delete_column_ops(&(df->columns[index]));

    // Décale les colonnes restantes pour combler le vide
    for (int i = index; i < df->num_columns - 1; i++) {
        df->columns[i] = df->columns[i + 1];
    }

    // Réduit le nombre de colonnes
    df->num_columns--;

    // Redimensionne le tableau des colonnes
    COLUMN_OPS **new_columns = realloc(df->columns, df->num_columns * sizeof(COLUMN_OPS *));
    if (new_columns == NULL && df->num_columns > 0) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(1);
    }
    df->columns = new_columns;
}

void delete_value_ops(COLUMN_OPS **col, int index) {
    if (*col == NULL || index < 0 || index >= (*col)->size) return;

    // libere la value de linde
    switch ((*col)->type) {
        case INT_TYPE:
            // pas de dynamique input
            break;
        case STRING_TYPE:
            free((*col)->data[index]);
            break;
        case FLOAT_TYPE:
            // No float
            break;
        default:
            fprintf(stderr, "Invalid column type\n");
            exit(1);
    }

    // pousse les valeurs a gauche
    for (int i = index; i < (*col)->size - 1; i++) {
        switch ((*col)->type) {
            case INT_TYPE:
                *((int *)((*col)->data[i])) = *((int *)((*col)->data[i + 1]));
                break;
            case STRING_TYPE:
                (*col)->data[i] = strdup((*col)->data[i + 1]);
                break;
            case FLOAT_TYPE:
                *((float *)((*col)->data[i])) = *((float *)((*col)->data[i + 1]));
                break;
            default:
                fprintf(stderr, "Invalid column type\n");
                exit(1);
        }
    }


    (*col)->size--;
}

void delete_row_from_dataframe(CDataframe *df, int row_index) {
    if (df == NULL || row_index < 0) return;

    for (int i = 0; i < df->num_columns; i++) {
        if (row_index >= df->columns[i]->size) {

            continue;
        }

        delete_value_ops(&(df->columns[i]), row_index);
    }
}


