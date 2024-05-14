ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "common.h" // Inclut le fichier d'en-tête commun pour les opérations sur les colonnes et les DataFrames

// Prototypes de fonctions pour les opérations sur les DataFrames
CDataframe *create_dataframe(); // Crée un nouveau DataFrame vide
int add_column_to_dataframe(CDataframe *df, COLUMN_OPS *col); // Ajoute une colonne à un DataFrame existant
void delete_dataframe(CDataframe **df); // Supprime un DataFrame et libère sa mémoire
void print_dataframe(CDataframe *df); // Affiche les données stockées dans un DataFrame
int save_dataframe_to_csv(CDataframe *df, const char *filename); // Sauvegarde les données d'un DataFrame dans un fichier CSV
CDataframe *load_dataframe_from_csv(const char *filename); // Charge les données d'un fichier CSV dans un DataFrame

#endif /* CDATAFRAME_H */