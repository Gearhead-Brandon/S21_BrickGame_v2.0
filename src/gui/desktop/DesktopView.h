/**
 * @file
 * @brief Header file for desktop view
 */

#ifndef DESKTOPVIEW_H
#define DESKTOPVIEW_H

#ifdef __cplusplus

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <iostream>

#include "../../components/Controller/Controller.h"

extern "C" {
#endif

#include "../../brick_game/bg_enums.h"
#include "../../components/GameInfo/GameInfo.h"

#ifdef __cplusplus
}
#endif

namespace s21 {

/**
 * @brief Class for desktop view
 * @details This class is used to display the game on the desktop
 * @see QMainWindow
 */
class DesktopView : public QMainWindow {
  Q_OBJECT

  //! @brief Central widget
  QWidget *wid_;

  //! @brief Controller
  Controller &controller_;

  //! @brief Timer
  QTimer *timer_;

  //! @brief Game layout
  QHBoxLayout *gameLayout_;

  //! @brief Info table layout
  QVBoxLayout *infoTable_;

  //! @brief Game scene for game field
  QGraphicsScene *gameScene_;

  //! @brief Game view for game field rendering
  QGraphicsView *gameView_;

  //! @brief Next scene for next field
  QGraphicsScene *nextScene_;

  //! @brief Next view for next field rendering
  QGraphicsView *nextView_;

  //! @brief Game field matrix
  QGraphicsRectItem **gameField_;

  //! @brief Next field matrix
  QGraphicsRectItem **nextField_;

  //! @brief Score label
  QLabel *Score_;

  //! @brief Level label
  QLabel *Level_;

  //! @brief High score label
  QLabel *HighScore_;

  //! @brief Text label for next field
  QGraphicsTextItem *textNext_;

  //! @brief Start banner label
  QGraphicsTextItem *startBanner_;

  //! @brief Game over banner label
  QGraphicsTextItem *gameOverBanner_;

  //! @brief Pause banner label
  QGraphicsTextItem *pauseBanner_;

  //! @brief Win banner label
  QGraphicsTextItem *winBanner_;

  //! @brief Height of the game field matrix
  int heightGameField_;

 public:
  /**
   * @brief Constructor
   * @param controller_ Controller reference
   */
  DesktopView(Controller &controller);

  /**
   * @brief Destructor
   */
  ~DesktopView() override;

 private:
  /**
   * @brief Key press event handler
   * @param event Key event
   */
  void keyPressEvent(QKeyEvent *event) override;

  /**
   * @brief Pseudo key press event sender
   * @details This function is used to send fake key press event
   *          to key press event
   */
  void pseudoKeyPressEvent();

  /**
   * @brief Mouse press event handler
   * @param event Mouse event
   */
  void mousePressEvent(QMouseEvent *event) override;

  /**
   * @brief Initialize layout
   * @param gameField Game field matrix
   * @param next Next field presence
   */
  void initLayout(int **gameField, bool next);

  /**
   * @brief Initialize labels
   */
  void initLabels();

  /**
   * @brief Quit game
   */
  void quit();

  /**
   * @brief Render gameinfo structure
   * @param gameInfo Game info structure
   * @param code State code
   * @see GameInfo_t
   */
  void render(const GameInfo_t &gameInfo, int code);

  /**
   * @brief Create game field
   * @param height Height of the game field
   * @param width Width of the game field
   */
  void createGameField(int height, int width);

  /**
   * @brief Create next field
   */
  void createNextField();

  /**
   * @brief Create info table
   * @param next Next field presence
   */
  void createInfoTable(bool next);

  /**
   * @brief Update next field matrix
   * @param next Next field
   */
  void updateNextField(int **next);

  /**
   * @brief Draw banner
   * @param banner Banner
   * @details Set visibility of the banner to true
   */
  void drawBanner(QGraphicsTextItem *banner);

  /**
   * @brief Hide banner
   * @param banner Banner
   * @details Set visibility of the banner to false
   */
  void hideBanner(QGraphicsTextItem *banner);

  /**
   * @brief Update game field matrix
   * @param field Game field
   */
  void updateGameField(int **field);

  /**
   * @brief Set label text
   * @param label Label
   * @param base Base text
   * @param value Value
   */
  void updateLabelDetails(QLabel *label, const char *base, int value);

  /**
   * @brief Check if the symbol is a figure
   * @param symbol Symbol
   */
  int isFigure(int symbol);

  /**
   * @brief Get color by symbol
   * @param symbol Symbol
   */
  QColor getColor(int symbol);

  /**
   * @brief Create new matrix for field
   * @param matrix Matrix
   * @param height Height
   * @param width Width
   */
  void newMatrix(QGraphicsRectItem **&matrix, int height, int width);

  /**
   * @brief Remove field matrix
   * @param matrix Matrix
   * @param height Height
   */
  void removeFieldMatrix(QGraphicsRectItem **matrix, int height);

  /**
   * @brief Initialize field matrix
   * @param matrix Matrix
   * @param scene Scene
   * @param height Height
   * @param width Width
   * @param step Step size
   * @details step is used to determine the size of the cells
   */
  void initFieldMatrix(QGraphicsRectItem **, QGraphicsScene *, int height,
                       int width, int step);
};
}  // namespace s21

#endif