#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "common.h"

// Function prototypes for dataframe operations
CDataframe *create_dataframe();
int add_column_to_dataframe(CDataframe *df, COLUMN_OPS *col);
void delete_dataframe(CDataframe **df);
void print_dataframe(CDataframe *df);
int save_dataframe_to_csv(CDataframe *df, const char *filename);
CDataframe *load_dataframe_from_csv(const char *filename);

#endif /* CDATAFRAME_H */
