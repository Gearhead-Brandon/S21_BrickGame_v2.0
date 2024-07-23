/**
 * @file
 * @brief Header of controller
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef __cplusplus

#include "../Interfaces/IModel.h"

extern "C" {
#endif

#include "../../brick_game/bg_enums.h"
#include "../../components/GameInfo/GameInfo.h"

#ifdef __cplusplus
}
#endif

namespace s21 {

/**
 * @brief Controller class
 * @details This class is used to separate the model from the view
 */
class Controller {
  //! @brief Model pointer
  IModel* model;

 public:
  /**
   * @brief Constructor
   * @param model Model pointer
   * @see IModel
   */
  Controller(IModel* model);

  /**
   * @brief User input accepts a user action as input
   * @param action User action
   * @param hold Hold action
   * @see UserAction_t
   *
   * @details Is the entry point into the game logic
   */
  void userInput(UserAction_t action, bool hold);

  /**!
   * @brief Get user input
   * @param action User action
   * @param hold Hold action
   * @param new_key New key
   * @see UserAction_t
   */
  void getInput(UserAction_t* action, bool* hold, int new_key);

  /**
   * @brief Get state code
   * @return State code
   *
   * @details The view uses a state code for rendering
   */
  int getStateCode();

  /**
   * @brief Update current state of the game
   * @return Copied structure of game information
   * @see GameInfo_t
   *
   * @details The view uses a structure for rendering
   */
  GameInfo_t updateCurrentState();

  /**
   * @brief Destructor
   */
  ~Controller();
};
}  // namespace s21

#endif