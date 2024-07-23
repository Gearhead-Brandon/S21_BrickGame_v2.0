/**
 * @file
 * @brief Implementation of desktop view wrapper
 */

#include "DesktopViewWrapper.h"

namespace s21 {

/**
 * @brief Constructor
 * @param controller Controller reference
 * @see Controller
 */
DesktopViewWrapper::DesktopViewWrapper(Controller &controller)
    : controller(controller) {}

/**
 * @brief Launch desktop qt view
 */
int DesktopViewWrapper::startEventLoop() {
  int argc = 0;
  char **argv = nullptr;

  QApplication app(argc, argv);

  std::setlocale(LC_NUMERIC, "C");
  srand(time(0));

  DesktopView view(controller);

  view.setWindowTitle("BrickGame");

  view.show();

  return app.exec();
}
}  // namespace s21