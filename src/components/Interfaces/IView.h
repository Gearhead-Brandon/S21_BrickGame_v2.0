/**
 * @file
 * @brief View interface
 */

#ifndef VIEW_H
#define VIEW_H

namespace s21 {

/**
 * @brief View interface as an abstract class
 */
class IView {
 public:
  /**
   * @brief Start event loop for view
   */
  virtual int startEventLoop() = 0;

  /**
   * @brief Virtual destructor
   */
  virtual ~IView() = default;
};
}  // namespace s21

#endif