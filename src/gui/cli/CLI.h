/*!
    @file
    @brief Console Interface
*/
#ifndef FRONTEND_H
#define FRONTEND_H

#include <wchar.h>

#include "../../brick_game/bg_enums.h"
#include "../../components/GameInfo/GameInfo.h"
#include "ncurses.h"

#define MVADDCH(y, x, c) mvaddch(2 + (y), 2 + (x), c)

/*!
    @brief Initialize ncurses and colors for ncurses
*/
void ncursesInit();

/*!
    @brief Initialize colors for ncurses
*/
void InitColors();

/*!
    @brief Print rectangle
    @param top_y Top coordinate
    @param bottom_y Bottom coordinate
    @param left_x Left coordinate
    @param right_x Right coordinate
*/
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

/*!
    @brief Drawing high score
    @param high_score High score
*/
void DrawingHighScore(int high_score);

/*!
    @brief Drawing field borders
*/
void DrawingGameFieldBorders(const int **field);

/*!
    @brief Console Interface output
    @param gameInfo Game info
    @param code Rendering code
    @return 0 if success
*/
int render(GameInfo_t *gameInfo, int code);

void DrawingWinBanner();

/*!
    @brief Drawing game over
*/
void DrawingGameOver();

/*!
    @brief Clear game over from interface
*/
void DeleteGameOver();

/*!
    @brief Drawing start banner
*/
void DrawingStartBanner();

/*!
    @brief Clear start banner from interface
*/
void DeleteStartBanner();

/*!
    @brief Drawing pause
*/
void DrawPause();

/*!
    @brief Clear pause from interface
*/
void DeletePause();

/*!
    @brief Drawing next figure field
*/
void DrawingNextFigureField();

/*!
    @brief Drawing next figure
    @param next Next figure
    @param color Color
*/
void DrawingNextFigure(const int **next);

/*!
    @brief Drawing score
    @param score Score
*/
void DrawingScore(int score);

/*!
    @brief Drawing level
    @param level Level
*/
void DrawingLevel(int level);

/*!
    @brief Print color string
    @param x X coordinate
    @param y Y coordinate
    @param string String
    @param color Color
*/
void PrintColorStr(int x, int y, const char *string, int color);

/*!
    @brief Print color wchar_t symbol
    @param x X coordinate
    @param y Y coordinate
    @param wc wchar_t symbol
    @param color Color
*/
void PrintColorWc(int x, int y, wchar_t symbol, int color);

/*!
    @brief Print game field
    @param field Field
*/
void PrintGameField(const int **field);

/*!
    @brief Get color
    @param symbol Symbol of the figure
*/
int GetColor(int symbol);

#endif
