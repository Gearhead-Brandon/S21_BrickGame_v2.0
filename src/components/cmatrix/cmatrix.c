/*!
    @file
    @brief Matrix library
*/
#include "cmatrix.h"

/*!
    @brief Create matrix
    @param rows Number of rows
    @param columns Number of columns
    @param matrix Pointer to matrix
*/
int CreateMatrix(int rows, int columns, int ***matrix) {
  int code = 1;

  if (rows > 0 && columns > 0) {
    *matrix = (int **)calloc(rows, sizeof(int *));

    for (int i = 0; i < rows; i++)
      (*matrix)[i] = (int *)calloc(columns, sizeof(int));

    code = 0;
  }

  return code;
}

/*!
    @brief Remove matrix
    @param matrix Pointer to matrix
    @param rows Number of rows
*/
void RemoveMatrix(int **matrix, int rows) {
  if (matrix) {
    for (int i = 0; i < rows; i++) free(matrix[i]);

    free(matrix);

    matrix = NULL;
  }
}