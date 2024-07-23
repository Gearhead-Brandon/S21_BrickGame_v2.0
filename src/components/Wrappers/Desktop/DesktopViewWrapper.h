/**
 * @file
 * @brief Header of wrapper for launch qt view
 */

#ifndef QTVIEW_H
#define QTVIEW_H

#ifdef __cplusplus

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "../../../gui/desktop/DesktopView.h"
#include "../../Controller/Controller.h"
#include "../../Interfaces/IView.h"

extern "C" {
#endif

#ifdef __cplusplus
}
#endif

namespace s21 {

/**
 * @brief Wrapper for launch desktop view
 * @details This class is used to launch the desktop view
 * @see IView
 * @see DesktopView
 */
class DesktopViewWrapper : public IView {
  //! @brief Controller pointer
  Controller &controller;

 public:
  /**
   * @brief Constructor
   * @param controller Controller reference
   * @see Controller
   */
  DesktopViewWrapper(Controller &controller);

  /**
   * @brief Launch desktop qt view
   */
  int startEventLoop() override;
};
}  // namespace s21

#endif