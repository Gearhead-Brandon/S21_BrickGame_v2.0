/**
 * @file
 * @brief Implementation of controller
 */

#include "Controller.h"

int getInput(UserAction_t *action, bool *hold, int last_key, int new_key);

namespace s21 {

/**
 * @brief Constructor
 * @param model Model pointer
 * @see IModel
 */
Controller::Controller(IModel *model) : model(model) {}

/**
 * @brief Destructor
 */
Controller::~Controller() { delete model; }

/**
 * @brief Update current state of the game
 * @return Copied structure of game information
 * @see GameInfo_t
 *
 * @details The view uses a structure for rendering
 */
GameInfo_t Controller::updateCurrentState() {
  return model->updateCurrentState();
}

/**!
 * @brief Get user input
 * @param action User action
 * @param hold Hold action
 * @param new_key New key
 * @see UserAction_t
 */
void Controller::getInput(UserAction_t *action, bool *hold, int input_key) {
  int key = ::getInput(action, hold, model->getLastKey(), input_key);
  model->setKey(key);
}

/**
 * @brief User input accepts a user action as input
 * @param action User action
 * @param hold Hold action
 * @see UserAction_t
 *
 * @details Is the entry point into the game logic
 */
void Controller::userInput(UserAction_t action, bool hold) {
  model->userInput(action, hold);
}

/**
 * @brief Get state code
 * @return State code
 *
 * @details The view uses a state code for rendering
 */
int Controller::getStateCode() {
  State state = model->getState();

  if (state == Launch)
    return 1;
  else if (state == GameOver)
    return 2;
  else if (state == Win)
    return 3;

  return 0;
}
}  // namespace s21