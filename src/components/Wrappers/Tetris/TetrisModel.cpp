/**
 * @file
 * @brief Implementation of wrapper for Tetris model
 */

#include "TetrisModel.h"

namespace s21 {

/**
 * @brief Constructor
 */
TetrisModel::TetrisModel() {
  ::TetrisGameInit();
  ::TetrisGameInfoInit();
}

/**
 * @brief Destructor
 */
TetrisModel::~TetrisModel() { ::DeleteGameInfo(); }

/**
 * @brief User input accepts a user action as input
 * @param action User action
 * @param hold Hold action
 * @see UserAction_t
 *
 * @details Is the entry point into the game logic
 */
void TetrisModel::userInput(UserAction_t action, bool hold) {
  ::userInput(action, hold);
}

/**
 * @brief Update current state of the game
 * @return Copied structure of game information
 * @see GameInfo_t
 *
 * @details The view uses a structure for rendering
 */
GameInfo_t TetrisModel::updateCurrentState() { return ::updateCurrentState(); }

/**
 * @brief Set key for cuurent input
 * @param key Input key
 */
void TetrisModel::setKey(int key) { ::setKey(key); }

/**
 * @brief Get last input key
 * @return Last key
 */
int TetrisModel::getLastKey() { return ::getTetrisLastKey(); }

/**
 * @brief Get current state of the game
 * @return Current state
 * @see State
 */
State TetrisModel::getState() { return ::getTetrisState(); }
}  // namespace s21