/**
 * @file
 * @brief Implementation of console view
 */

#include "ConsoleView.h"

#include <time.h>

#include <locale>

namespace s21 {

/**
 * @brief Constructor
 * @param controller_ Controller reference
 * @see Controller
 */
ConsoleView::ConsoleView(Controller &controller) : controller_(controller) {}

/**
 * @brief Render the game
 * @param gameInfo Game information
 * @param code Rendering code
 */
int ConsoleView::render(GameInfo_t &gameInfo, int code) {
  return ::render(&gameInfo, code);
}

/**
 * @brief Start game event loop
 */
int ConsoleView::startEventLoop() {
  setlocale(LC_ALL, "");
  srand(time(0));

  ncursesInit();

  UserAction_t action = Start;

  bool hold = false;

  int code = 1;

  while (code) {
    int key = getch();

    controller_.getInput(&action, &hold, key);
    controller_.userInput(action, hold);

    if (action == Terminate) {
      endwin();
      break;
    }

    GameInfo_t gameInfo = controller_.updateCurrentState();

    code = render(gameInfo, controller_.getStateCode());

    timeout(gameInfo.speed);
  }

  return 0;
}
}  // namespace s21