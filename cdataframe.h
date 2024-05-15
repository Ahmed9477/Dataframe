#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "common.h"
#include "column_operations.h"

// Crée un nouveau dataframe vide
CDataframe *create_dataframe();

// Ajoute une colonne au dataframe spécifié
int add_column_to_dataframe(CDataframe *df, COLUMN_OPS *col);

// Supprime le dataframe et libère la mémoire
void delete_dataframe(CDataframe **df);

// Affiche le dataframe dans la console
void print_dataframe(CDataframe *df);

// Sauvegarde le dataframe dans un fichier CSV
int save_dataframe_to_csv(CDataframe *df, const char *filename);

// Charge un dataframe à partir d'un fichier CSV
CDataframe *load_dataframe_from_csv(const char *filename);

// Remplit le dataframe avec des entrées fournies par l'utilisateur
void fill_dataframe_with_user_input(CDataframe *df);

// Remplit le dataframe avec des données prédéfinies (remplissage "dur")
void hard_fill_dataframe(CDataframe *df);

// Affiche l'intégralité du dataframe
void display_entire_dataframe(CDataframe *df);

// Affiche un nombre limité de lignes du dataframe
void display_partial_rows(CDataframe *df, int limit);

// Affiche un nombre limité de colonnes du dataframe
void display_partial_columns(CDataframe *df, int limit);

#endif /* CDATAFRAME_H */
