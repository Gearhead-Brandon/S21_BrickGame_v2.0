/**
 * @file
 *  @brief Tetris backend part header
 */
#ifndef TETRIS_H
#define TETRIS_H

#include "../../../components/GameInfo/GameInfo.h"
#include "../../bg_enums.h"
#include "storage.h"

/// Structure of game
typedef struct {
  State state;  ///< Current state of the game

  int clicks;    ///< Number of clicks
  int blocking;  ///< Blocking figure shifting
  int key;       ///< Pressed key
  int last_key;  ///< Last pressed key
  int move;      ///< Figure moving flag

} TetrisGame;

/*!
        @brief Tetris backend initialization
*/
void TetrisGameInit();

/*!
    @brief Update current state
    @return Copied structure of game information
*/
GameInfo_t updateCurrentState();

/*!
    @brief Get last pressed key
    @return Last pressed key
*/
int getTetrisLastKey();

/*!
    @brief Get current state
    @return Current state
*/
State getTetrisState();

/*!
    @brief Initialize game information
*/
void TetrisGameInfoInit();

/*!
    @brief Delete game structure
*/
void DeleteGameInfo();

/*!
    @brief Control of the game logic
    @param action User action
    @param hold Flag of hold
*/
void userInput(UserAction_t action, bool hold);

/*!
    @brief Process user input
    @param action User action
    @param hold Hold action
*/
void actionProcessing(UserAction_t action, bool hold);

/*!
    @brief Processing status after user input
    @param action User action
*/
int StatusProcessing(UserAction_t action);

/*!
    @brief Processing shifting and state after moving
*/
void ShiftingProcessing();

/*!
    @brief Removing the current figure from the field
    @param axis Axis
    @param term Term

    Removing the current figure from the field and shifting it to a term.
    Also color field clearing
*/
void ResettingOldFigure(int axis, int term);

/*!
    @brief Checking for cell accessibility after shift
    @return Count of free cells
*/
int CheckingFreePosition();

/*!
    @brief Returning the figure back
    @param axis Axis
    @param term Term

    If the field spaces are already occupied, then return the figure back
*/
void ReturnFigureBack(int axis, int term);

/*!
    @brief Transfer figure to field and color to color field
*/
void TransferFigureToField();

/*!
    @brief Assigning symbol matrix elements to spaces
    @param field Field
    @param row1 First row
    @param row2 Last row
    @param col1 First column
    @param col2 Last column
*/
void ClearField(int **field, int row1, int row2, int col1, int col2);

/*!
    @brief Attaching stage
*/
void AttachingStage();

/*!
    @brief Shifting a piece down the field onto a cell
*/
void FigureDown();

/*!
    @brief Takes a new figure from figures.c

    Also color field filling and setting the next figure and her color
*/
void DropFigure();

/*!
    @brief Move horizontal
    @param side Left or right
*/
void MoveHorizontal(char *side);

/*!
    @brief Rotating a figure via the rotation matrix
*/
void Rotate();

/*!
    @brief Set next figure
    @param next Next figure
*/
void SetNextFigure(int next);

/*!
    @brief Get next figure
    @return Next figure
*/
int GetNextFigure();

/*!
    @brief Set current figure
    @param current Current figure
*/
void SetCurrentFigure(int next);

/*!
    @brief Get current figure
    @return Current figure
*/
int GetCurrentFigure();

/*!
    @brief Restarting the game after game over
*/
void Restart();

/*!
    @brief Checking the end of the game after attaching
*/
void GameOverCheck();

/*!
    @brief Removing filled lines

    Replenishment of points after the destruction of lines
    and shifting the field down a cell
*/
void RemovingFilledLines();

/*!
    @brief Shifting the field down a cell
*/
void FieldDown(int row);

/*!
    @brief Saving the high score to the file
    @param path Path to the file
*/
void SaveHighScore(const char *path);

/*!
    @brief Getting the high score from the file
    @param path Path to the file
*/
int GetHighScore(const char *path);

/*!
    @brief Increase in points from destroying lines

    Also updating the record and increasing the level with speed
*/
void ProcessingRemovedLines(int removed_lines);

/*!
    @brief Define tetris time
    @param level Level
*/
int defineTetrisTime(int level);

/*!
    @brief Set new pressed key
    @param new_key New pressed key
*/
void setKey(int new_key);

#endif