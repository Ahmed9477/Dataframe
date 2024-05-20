#ifndef COMMON_H
#define COMMON_H

//Ces définitions structurées permettent de séparer clairement la définition des
//types de données et des structures de leur manipulation et affichage, rendant le code plus modulaire et maintenable.

// Définition des types de colonnes
typedef enum {
    UINT_TYPE,
    INT_TYPE,
    CHAR_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    STRUCT_TYPE
} COL_TYPE;

// Structure pour les opérations sur les colonnes
typedef struct column_ops {
    COL_TYPE type;
    void **data;
    int size;
} COLUMN_OPS;

// Structure pour le dataframe
typedef struct {
    COLUMN_OPS **columns;
    int num_columns;
} CDataframe;

#endif /* COMMON_H */
