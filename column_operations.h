#ifndef COLUMN_OPERATIONS_H
#define COLUMN_OPERATIONS_H

#include "common.h"

//essentiels pour la manipulation efficace et sûre des colonnes dans un DataFrame,

// Crée une nouvelle structure de colonne avec le type spécifié
COLUMN_OPS *create_column_ops(COL_TYPE type);
// Insère une valeur dans la colonne
int insert_value_ops(COLUMN_OPS *col, void *value);
// Supprime une colonne et libère la mémoire
void delete_column_ops(COLUMN_OPS **col);
// Affiche les valeurs d'une colonne
void print_col_ops(COLUMN_OPS *col, int row);

#endif /* COLUMN_OPERATIONS_H */
