/*!
    @file
    @brief Matrix library
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

/*!
    @brief Create matrix
    @param rows Number of rows
    @param columns Number of columns
    @param matrix Pointer to matrix
*/
int CreateMatrix(int rows, int columns, int ***matrix);

/*!
    @brief Remove matrix
    @param matrix Pointer to matrix
    @param rows Number of rows
*/
void RemoveMatrix(int **matrix, int rows);

#endif