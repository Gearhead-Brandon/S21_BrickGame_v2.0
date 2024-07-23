/**
 * @file
 * @brief User input processing
 */
#include "Input.h"

/**
 * @brief Input processing for the user action
 * @param action User action
 * @param hold Hold action
 * @param last_key Last key
 * @param new_key New key
 * @return New key
 */
int getInput(UserAction_t *action, bool *hold, int last_key, int new_key) {
  if (new_key == ArrowUp || new_key == Qt::Key_Up)
    *action = Up;
  else if (new_key == ArrowLeft || new_key == Qt::Key_Left)
    *action = Left;
  else if (new_key == ArrowRight || new_key == Qt::Key_Right)
    *action = Right;
  else if (new_key == ArrowDown || new_key == Qt::Key_Down)
    *action = Down;
  else if (new_key == QUIT || new_key == Qt::Key_Q) {
    *action = Terminate;
    new_key = QUIT;
  } else if (new_key == PAUSE || new_key == Qt::Key_P) {
    *action = Pause;
    new_key = PAUSE;
  } else if (new_key == ACTION)
    *action = Action;
  else {
    *action = Start;
    if (new_key == Qt::Key_Enter || new_key == Qt::Key_Return) new_key = ENTER;
  }

  if (new_key != -1) {
    if (new_key == last_key) *hold = true;
  } else
    *hold = false;

  return new_key;
}