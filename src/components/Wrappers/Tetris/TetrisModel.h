/**
 * @file
 * @brief Shell model based on Tetris
 */

#ifndef TETRISMODEL_H
#define TETRISMODEL_H

#ifdef __cplusplus

#include "../../Interfaces/IModel.h"

extern "C" {
#endif

#include "../../../brick_game/tetris/inc/tetris.h"

#ifdef __cplusplus
}
#endif

namespace s21 {

/**
 * @brief Wrapper for Tetris model
 * @see IModel
 */
class TetrisModel : public IModel {
 public:
  /**
   * @brief Constructor
   */
  TetrisModel();

  /**
   * @brief Destructor
   */
  ~TetrisModel() override;

  /**
   * @brief User input accepts a user action as input
   * @param action User action
   * @param hold Hold action
   * @see UserAction_t
   *
   * @details Is the entry point into the game logic
   */
  void userInput(UserAction_t action, bool hold) override;

  /**
   * @brief Update current state of the game
   * @return Copied structure of game information
   * @see GameInfo_t
   *
   * @details The view uses a structure for rendering
   */
  GameInfo_t updateCurrentState() override;

  /**
   * @brief Set key for cuurent input
   * @param key Input key
   */
  void setKey(int key) override;

  /**
   * @brief Get last input key
   * @return Last key
   */
  int getLastKey() override;

  /**
   * @brief Get current state of the game
   * @return Current state
   * @see State
   */
  State getState() override;
};
}  // namespace s21

#endif