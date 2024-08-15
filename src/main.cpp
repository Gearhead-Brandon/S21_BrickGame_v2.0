/**
 * @file
 * @brief Main file
 */

#include "brick_game.h"

using namespace s21;

int main() {
  GameType gameType = getGameType();
  ViewType viewType = getViewType();

  GameFactory factory;

  IModel *model = factory.createModel(gameType);

  Controller controller(model);

  IView *view = factory.createView(viewType, controller);

  view->startEventLoop();

  delete view;

  return 0;
}