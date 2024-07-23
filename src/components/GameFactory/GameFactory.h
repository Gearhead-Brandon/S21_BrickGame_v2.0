/**
 * @file
 * @brief Header file for GameFactory
 */

#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include <iostream>
#include "../../brick_game/snake/inc/snakeModel.h"
#include "../Wrappers/Desktop/DesktopViewWrapper.h"
#include "../Wrappers/Cli/ConsoleView.h"
#include "../Wrappers/Tetris/TetrisModel.h"

namespace s21 {

/**
 * @brief Enumeration of game types
 */
enum class GameType : int {
  Tetris,  ///< Tetris game type
  Snake    ///< Snake game type
};

/**
 * @brief Enumeration of view types
 */
enum class ViewType : int {
  CLI,  ///< CLI view type
  Qt    ///< Qt view type
};

/**
 * @brief Factory class for creating game models and views
 */
class GameFactory {
 public:
  /**
   * @brief Create game model
   * @param type Game type
   * @return Game model pointer
   */
  IModel *createModel(GameType type);

  /**
   * @brief Create game view
   * @param type View type
   * @param c Controller
   * @return Game view pointer
   */
  IView *createView(ViewType type, s21::Controller &c);
};

/**
 * @brief Choose game type
 * @return Game type
 */
GameType getGameType();

/**
 * @brief Choose view type
 * @return View type
 */
ViewType getViewType();

}  // namespace s21

#endif