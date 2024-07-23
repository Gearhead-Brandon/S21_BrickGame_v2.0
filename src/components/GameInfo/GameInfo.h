/**
 * @file
 * @brief Brick game library game information
 */

#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <stdbool.h>

/**
 * @brief Enumeration of user actions
 */
typedef enum {

  Start,      ///< Normal gameplay
  Pause,      ///< Pause the game
  Terminate,  ///< Quit from game
  Left,       ///< Move left
  Right,      ///< Move right
  Up,         ///< Move up (Not used in Tetris)
  Down,       ///< Move down
  Action      ///< Some action (Rotation in Tetris)

} UserAction_t;

/**
 * @brief Structure of game information
 */
typedef struct {
  int **field;     ///< Field of the game
  int **next;      ///< Next figure
  int score;       ///< Score
  int high_score;  ///< High score
  int level;       ///< Level
  int speed;       ///< Speed
  int pause;       ///< Pause

} GameInfo_t;

#endif