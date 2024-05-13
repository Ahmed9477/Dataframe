#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframe.h"

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

void delete_dataframe(CDataframe **df) {
    if (*df == NULL) return;
    for (int i = 0; i < (*df)->num_columns; i++) {
        delete_column_ops(&((*df)->columns[i]));
    }
    free((*df)->columns);
    free(*df);
    *df = NULL;
}

void print_dataframe(CDataframe *df) {
    if (df == NULL || df->columns == NULL) return;
    for (int i = 0; i < df->num_columns; i++) {
        printf("Column %d:\n", i + 1);
        print_col_ops(df->columns[i]);
    }
}

int save_dataframe_to_csv(CDataframe *df, const char *filename) {
    if (df == NULL || filename == NULL) return 0;
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 0;
    }
    for (int i = 0; i < df->num_columns; i++) {
        COLUMN_OPS *col = df->columns[i];
        for (int j = 0; j < col->size; j++) {
            switch (col->type) {
                case UINT_TYPE:
                    fprintf(file, "%u", *((unsigned int *)col->data[j]));
                    break;
                case INT_TYPE:
                    fprintf(file, "%d", *((int *)col->data[j]));
                    break;
                case CHAR_TYPE:
                    fprintf(file, "%c", *((char *)col->data[j]));
                    break;
                case FLOAT_TYPE:
                    fprintf(file, "%f", *((float *)col->data[j]));
                    break;
                case DOUBLE_TYPE:
                    fprintf(file, "%lf", *((double *)col->data[j]));
                    break;
                case STRING_TYPE:
                    fprintf(file, "%s", (char *)col->data[j]);
                    break;
                case STRUCT_TYPE:
                    // Handle printing of struct type
                    break;
                default:
                    fprintf(stderr, "Invalid column type\n");
                    fclose(file);
                    return 0;
            }
            if (j < col->size - 1) fprintf(file, ",");
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 1;
}

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
            // Create a new column and insert value
            COLUMN_OPS *col = create_column_ops(STRING_TYPE);
            insert_value_ops(col, token);
            // Add column to dataframe
            add_column_to_dataframe(df, col);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    return df;
}
