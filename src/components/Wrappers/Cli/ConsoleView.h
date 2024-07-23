/**
 * @file
 * @brief Header of console view
 */

#ifndef CLIVIEW_H
#define CLIVIEW_H

#ifdef __cplusplus

#include "../../Controller/Controller.h"
#include "../../Interfaces/IView.h"

extern "C" {
#endif

#include "../../../gui/cli/CLI.h"

#ifdef __cplusplus
}
#endif

namespace s21 {

/**
 * @brief Class for console view
 * @details This class is used to display the game on the console
 * @see IView
 */
class ConsoleView : public IView {
  //! @brief Controller pointer
  Controller& controller_;

 public:
  /**
   * @brief Constructor
   * @param controller_ Controller reference
   * @see Controller
   */
  ConsoleView(Controller& controller_);

  /**
   * @brief Start game event loop
   */
  int startEventLoop() override;

  /**
   * @brief Render the game
   * @param gameInfo Game information
   * @param code Rendering code
   */
  int render(GameInfo_t& gameInfo, int code);
};
}  // namespace s21

#endif