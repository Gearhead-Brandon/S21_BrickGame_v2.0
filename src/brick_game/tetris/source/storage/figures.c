/*!
    @file
    @brief Tetris figures storage
*/
#include "../../inc/storage.h"

static int figures[14][5] = {

    {0, 1, 1, 1, 1},  // ####
    {0, 0, 0, 0, 0},  //

    {0, 0, 1, 0, 0},  //  #
    {0, 1, 1, 1, 0},  // ###

    {0, 1, 0, 0, 0},  // #
    {0, 1, 1, 1, 0},  // ###

    {0, 0, 0, 1, 0},  //   #
    {0, 1, 1, 1, 0},  // ###

    {0, 1, 1, 0, 0},  // ##
    {0, 1, 1, 0, 0},  // ##

    {0, 1, 1, 0, 0},  // ##
    {0, 0, 1, 1, 0},  //  ##

    {0, 0, 1, 1, 0},  //  ##
    {0, 1, 1, 0, 0}   // ##

};

/*!
    @brief Get index of the figure
    @param x X coordinate
    @param y Y coordinate
    @return presence of the figure
*/
int getFigureIndex(int x, int y) { return figures[x][y]; }