/**
 * @file
 * @brief Model interface
 */

#ifndef MODEL_H
#define MODEL_H

#ifdef __cplusplus

extern "C" {
#endif

#include "../../brick_game/bg_enums.h"
#include "../../components/GameInfo/GameInfo.h"

#ifdef __cplusplus
}
#endif

namespace s21 {
/**
 * @brief Model interface as an abstract class
 */
class IModel {
 public:
  /**
   * @brief Virtual destructor
   */
  virtual ~IModel() = default;

  /**
   * @brief User input accepts a user action as input
   * @param action User action
   * @param hold Hold action
   * @see UserAction_t
   *
   * @details Is the entry point into the game logic
   */
  virtual void userInput(UserAction_t action, bool hold) = 0;

  /**
   * @brief Update current state of the game
   * @return Copied structure of game information
   * @see GameInfo_t
   *
   * @details The view uses a structure for rendering
   */
  virtual GameInfo_t updateCurrentState() = 0;

  /**
   * @brief Set key for cuurent input
   * @param key Input key
   */
  virtual void setKey(int key) = 0;

  /**
   * @brief Get last input key
   * @return Last key
   */
  virtual int getLastKey() = 0;

  /**
   * @brief Get current state of the game
   * @return Current state
   * @see State
   */
  virtual State getState() = 0;
};
}  // namespace s21

#endif