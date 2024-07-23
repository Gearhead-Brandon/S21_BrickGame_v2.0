/**
 * @file
 * @brief Implementation of GameFactory
 */

#include "GameFactory.h"

namespace s21 {

/**
 * @brief Create game model
 * @param type Game type
 * @return Game model pointer
 */
IModel *GameFactory::createModel(GameType type) {
  if (type == GameType::Snake)
    return new SnakeModel();
  else if (type == GameType::Tetris)
    return new TetrisModel();

  return nullptr;
}

/**
 * @brief Create game view
 * @param type View type
 * @param c Controller
 * @return Game view pointer
 */
IView *GameFactory::createView(ViewType type, Controller &c) {
  if (type == ViewType::CLI)
    return new ConsoleView(c);
  else if (type == ViewType::Qt)
    return new DesktopViewWrapper(c);

  return nullptr;
}

/**
 * @brief Choose game type
 * @return Game type
 */
GameType getGameType() {
  std::cout << std::endl;
  std::cout << "======================" << std::endl;
  std::cout << "|| G A M E  M E N U ||" << std::endl;
  std::cout << "======================" << std::endl;
  std::cout << "     Choose game" << std::endl;
  std::cout << "      1. Tetris" << std::endl;
  std::cout << "      2. Snake" << std::endl;

  int type = 0;

  std::cin >> type;

  if (type == 1)
    return GameType::Tetris;
  else if (type == 2)
    return GameType::Snake;
  else
    std::exit(0);

  return GameType::Tetris;
}

/**
 * @brief Choose view type
 * @return View type
 */
ViewType getViewType() {
  std::cout << std::endl;
  std::cout << "     Choose view" << std::endl;
  std::cout << "       1. CLI" << std::endl;
  std::cout << "      2. Desktop" << std::endl;

  int type = 0;

  std::cin >> type;

  if (type == 1)
    return ViewType::CLI;
  else if (type == 2)
    return ViewType::Qt;
  else
    std::exit(0);

  return ViewType::CLI;
}
}  // namespace s21