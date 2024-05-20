#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "common.h"
#include "column_operations.h"

// Crée une nouvelle structure de dataframe
CDataframe *create_dataframe();
// Ajoute une colonne au dataframe
int add_column_to_dataframe(CDataframe *df, COLUMN_OPS *col);
// Supprime le dataframe et libère la mémoire
void delete_dataframe(CDataframe **df);
// Affiche le dataframe
void print_dataframe(CDataframe *df);
// Enregistre un dataframe dans un fichier CSV
int save_dataframe_to_csv(CDataframe *df, const char *filename);
// Charge un dataframe depuis un fichier CSV
CDataframe *load_dataframe_from_csv(const char *filename);
// Remplit le dataframe avec des entrées utilisateur
void fill_dataframe_with_user_input(CDataframe *df);
// Remplit le dataframe avec de la merde
void hard_fill_dataframe(CDataframe *df);
// Affiche tout le dataframe
void display_entire_dataframe(CDataframe *df);
// Affiche un nombre limité de lignes du dataframe
void display_partial_rows(CDataframe *df, int limit);
// Affiche un nombre limité de colonnes du dataframe
void display_partial_columns(CDataframe *df, int limit);
// Supprime une colonne du dataframe
void delete_column_from_dataframe(CDataframe *df, int index);
// Supprime une valeur spécifique dans une colonne
void delete_value_ops(COLUMN_OPS **col, int index);
// Supprime une ligne spécifique du dataframe
void delete_row_from_dataframe(CDataframe *df, int row_index);


#endif /* CDATAFRAME_H */
