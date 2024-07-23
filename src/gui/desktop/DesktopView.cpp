/**
 * @file
 * @brief Implementation of desktop view
 */

#include "DesktopView.h"

namespace s21 {

/**
 * @brief Constructor
 * @param controller_ Controller reference
 */
DesktopView::DesktopView(Controller &controller)
    : QMainWindow(nullptr),
      wid_(new QWidget()),
      controller_(controller),
      timer_(new QTimer()),
      gameLayout_(new QHBoxLayout()),
      infoTable_(new QVBoxLayout()),
      gameScene_(new QGraphicsScene()),
      gameView_(new QGraphicsView(gameScene_)),
      nextScene_(new QGraphicsScene()),
      nextView_(new QGraphicsView(nextScene_)),
      gameField_(nullptr),
      nextField_(nullptr),
      Score_(new QLabel()),
      Level_(new QLabel()),
      HighScore_(new QLabel()),
      textNext_(new QGraphicsTextItem()),
      startBanner_(new QGraphicsTextItem()),
      gameOverBanner_(new QGraphicsTextItem()),
      pauseBanner_(new QGraphicsTextItem()),
      winBanner_(new QGraphicsTextItem()),
      heightGameField_(0) {
  setStyleSheet("background-color: white;");

  setCentralWidget(wid_);
  wid_->setLayout(gameLayout_);

  setFocus();

  connect(timer_, &QTimer::timeout, this, &DesktopView::pseudoKeyPressEvent);

  GameInfo_t gameInfo = controller_.updateCurrentState();
  initLayout(gameInfo.field, gameInfo.next);

  pseudoKeyPressEvent();
}

/**
 * @brief Pseudo key press event sender
 * @details This function is used to send fake key press event
 *          to key press event
 */
void DesktopView::pseudoKeyPressEvent() {
  QKeyEvent event(QEvent::KeyPress, -1, Qt::NoModifier, QString());

  keyPressEvent(&event);
}

/**
 * @brief Key press event handler
 * @param event Key event
 */
void DesktopView::keyPressEvent(QKeyEvent *event) {
  timer_->stop();

  UserAction_t action = Start;
  bool hold = false;

  controller_.getInput(&action, &hold, event->key());
  controller_.userInput(action, hold);

  if (action == UserAction_t::Terminate) quit();

  GameInfo_t gameInfo = controller_.updateCurrentState();

  render(gameInfo, controller_.getStateCode());

  timer_->setInterval(gameInfo.speed);
  timer_->start();
}

/**
 * @brief Initialize layout
 * @param gameField Game field matrix
 * @param next Next field presence
 */
void DesktopView::initLayout(int **field, bool next) {
  int height = field[0][0] - 1;
  int width = field[1][0] - 2;

  createGameField(height, width);

  createInfoTable(next);

  gameLayout_->addWidget(gameView_);
  gameLayout_->addLayout(infoTable_);
}

/**
 * @brief Create game field
 * @param height Height of the game field
 * @param width Width of the game field
 */
void DesktopView::createGameField(int height, int width) {
  heightGameField_ = height;

  newMatrix(gameField_, height, width);
  initFieldMatrix(gameField_, gameScene_, height, width, 40);

  startBanner_->setPos(25, 350);
  startBanner_->setHtml(
      "<p style='color: #ff0000; font-weight: bold; "
      "font-size: 35px;'>Press Enter to start!</p>");
  startBanner_->setVisible(false);
  gameScene_->addItem(startBanner_);

  gameOverBanner_->setPos(40, 300);
  gameOverBanner_->setHtml(
      "<p style='color: #ff0000; font-weight: bold; font-size: "
      "35px;'>\U0001F525 Game Over \U0001F525</p>");
  gameOverBanner_->setVisible(false);
  gameScene_->addItem(gameOverBanner_);

  pauseBanner_->setPos(75, 350);
  pauseBanner_->setHtml(
      "<p style='color: #ff0000; font-weight: bold; "
      "font-size: 55px;'>Pause  ⏸️</p>");
  pauseBanner_->setVisible(false);
  gameScene_->addItem(pauseBanner_);

  winBanner_->setPos(75, 300);
  winBanner_->setHtml(
      "<p style='color: #eb401a; font-weight: bold; font-size: "
      "55px;'>You Win!</p>");
  winBanner_->setVisible(false);
  gameScene_->addItem(winBanner_);

  gameView_->setBackgroundBrush(Qt::black);
  gameView_->setFixedSize(width * 40 + 10, height * 40 + 10);
}

/**
 * @brief Create next field
 */
void DesktopView::createNextField() {
  int height = 5, width = 6, size = 40;

  newMatrix(nextField_, height, width);
  initFieldMatrix(nextField_, nextScene_, height, width, size);

  textNext_->setPos(20, 10);
  textNext_->setHtml(
      "<p style='color: #ef64e4; font-weight: bold; font-size: "
      "35px;'>Next</p>");

  nextScene_->addItem(textNext_);

  nextView_->setBackgroundBrush(Qt::black);
  nextView_->setFixedSize(width * size + 10, height * size + 10);
}

/**
 * @brief Create info table
 * @param next Next field presence
 */
void DesktopView::createInfoTable(bool next) {
  infoTable_->setSpacing(40);

  if (next) {
    createNextField();
    infoTable_->addWidget(nextView_);
  }

  initLabels();

  infoTable_->addWidget(HighScore_);
  infoTable_->addWidget(Score_);
  infoTable_->addWidget(Level_);

  infoTable_->addStretch();

  infoTable_->setContentsMargins(20, 0, 0, 0);
}

/**
 * @brief Initialize labels
 */
void DesktopView::initLabels() {
  HighScore_->setText("HighScore  0");
  Score_->setText("Score  0");
  Level_->setText("Level 0");

  HighScore_->setStyleSheet(
      "color: #9314ff; font-weight: bold; font-size: "
      "25px; border: 5px solid black;");
  Score_->setStyleSheet(
      "color: #0057ff; font-weight: bold; font-size: 25px; "
      "border: 5px solid black;");
  Level_->setStyleSheet(
      "color: #ff033e; font-weight: bold; font-size: 25px; "
      "border: 5px solid black;");

  HighScore_->setAlignment(Qt::AlignLeft);
  HighScore_->setContentsMargins(10, 30, 40, 30);

  Score_->setAlignment(Qt::AlignLeft);
  Score_->setContentsMargins(10, 30, 0, 30);

  Level_->setAlignment(Qt::AlignLeft);
  Level_->setContentsMargins(10, 30, 0, 30);
}

/**
 * @brief Draw banner
 * @param banner Banner
 * @details Set visibility of the banner to true
 */
void DesktopView::drawBanner(QGraphicsTextItem *banner) {
  banner->setVisible(true);
}

/**
 * @brief Hide banner
 * @param banner Banner
 * @details Set visibility of the banner to false
 */
void DesktopView::hideBanner(QGraphicsTextItem *banner) {
  banner->setVisible(false);
}

/**
 * @brief Initialize field matrix
 * @param matrix Matrix
 * @param scene Scene
 * @param height Height
 * @param width Width
 * @param step Step size
 * @details step is used to determine the size of the cells
 */
void DesktopView::initFieldMatrix(QGraphicsRectItem **matrix,
                                  QGraphicsScene *scene, int height, int width,
                                  int step) {
  int pos_x = 0, pos_y = 0;

  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++) {
      matrix[i][j].setRect(pos_x, pos_y, step, step);

      scene->addItem(matrix[i] + j);

      matrix[i][j].setBrush(Qt::white);
      matrix[i][j].setPen(Qt::NoPen);

      pos_x += step;

      if (j == width - 1) {
        pos_x = 0;
        pos_y += step;
      }
    }
}

/**
 * @brief Quit game
 */
void DesktopView::quit() { QApplication::quit(); }

/**
 * @brief Check if the symbol is a figure
 * @param symbol Symbol
 */
int DesktopView::isFigure(int symbol) {
  return symbol >= FigureSym ? symbol - FigureSym : 0;
}

/**
 * @brief Get color by symbol
 * @param symbol Symbol
 */
QColor DesktopView::getColor(int symbol) {
  switch (symbol) {
    case 0:
      return QColor(2, 93, 255);  // blue
    case 1:
      return QColor(255, 3, 62);  // red
    case 2:
      return QColor(214, 0, 110);  // pink
    case 3:
      return QColor(25, 230, 90);  // green
    case 4:
      return QColor(27, 230, 176);  // azure
    case 5:
      return QColor(153, 17, 153);  // magenta
    case 6:
      return QColor(0, 255, 255);  // cyan
    case 7:
      return QColor(99, 93, 99);  // gray
  }

  return Qt::black;
}

/**
 * @brief Update game field matrix
 * @param field Game field
 */
void DesktopView::updateGameField(int **field) {
  int color = 0, symbol;
  int height = field[0][0] - 1;
  int width = field[1][0] - 1;

  for (int i = 0; i < height; i++) {
    for (int j = 1; j < width; j++) {
      symbol = field[i][j];

      color = isFigure(symbol);

      if (symbol >= FigureSym) {
        gameField_[i][j - 1].setBrush(getColor(color));
        gameField_[i][j - 1].setPen(QPen());
      } else {
        gameField_[i][j - 1].setBrush(Qt::white);
        gameField_[i][j - 1].setPen(Qt::NoPen);
      }
    }
  }
}

/**
 * @brief Set label text
 * @param label Label
 * @param base Base text
 * @param value Value
 */
void DesktopView::updateLabelDetails(QLabel *label, const char *base,
                                     int value) {
  label->setText(base + QString::number(value));
}

/**
 * @brief Update next field matrix
 * @param next Next field
 */
void DesktopView::updateNextField(int **field) {
  int color = field[0][5];

  for (int i = 0, shift = 2; i < 2; i++)
    for (int j = 0; j < 4; j++) {
      int sym = field[i + 2][j];

      if (!sym) {
        nextField_[i + shift][j + 1].setBrush(Qt::white);
        nextField_[i + shift][j + 1].setPen(Qt::NoPen);
      } else {
        nextField_[i + shift][j + 1].setBrush(getColor(color));
        nextField_[i + shift][j + 1].setPen(QPen());
      }
    }
}

/**
 * @brief Render gameinfo structure
 * @param gameInfo Game info structure
 * @param code State code
 * @see GameInfo_t
 */
void DesktopView::render(const GameInfo_t &gameInfo, int code) {
  hideBanner(startBanner_);
  hideBanner(gameOverBanner_);

  if (gameInfo.field) updateGameField(gameInfo.field);

  if (code == 1 || code == 2 || code == 3) {
    if (code == 3) {
      drawBanner(winBanner_);
      QTimer::singleShot(1500, this, &DesktopView::quit);
      return;
    }

    if (code == 2) drawBanner(gameOverBanner_);

    drawBanner(startBanner_);
  } else {
    hideBanner(startBanner_);
    hideBanner(gameOverBanner_);
  }

  if (gameInfo.pause)
    drawBanner(pauseBanner_);
  else
    hideBanner(pauseBanner_);

  if (gameInfo.next) updateNextField(gameInfo.next);

  if (gameInfo.high_score != -1)
    updateLabelDetails(HighScore_, "HighScore  ", gameInfo.high_score);

  if (gameInfo.score != -1)
    updateLabelDetails(Score_, "Score  ", gameInfo.score);

  if (gameInfo.level != -1)
    updateLabelDetails(Level_, "Level  ", gameInfo.level);
}

/**
 * @brief Mouse press event handler
 * @param event Mouse event
 */
void DesktopView::mousePressEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  setFocus();
}

/**
 * @brief Create new matrix for field
 * @param matrix Matrix
 * @param height Height
 * @param width Width
 */
void DesktopView::newMatrix(QGraphicsRectItem **&matrix, int height,
                            int width) {
  matrix = new QGraphicsRectItem *[height];

  for (int i = 0; i < height; ++i) matrix[i] = new QGraphicsRectItem[width];
}

/**
 * @brief Remove field matrix
 * @param matrix Matrix
 * @param height Height
 */
void DesktopView::removeFieldMatrix(QGraphicsRectItem **matrix, int height) {
  for (int i = 0; i < height; ++i) delete[] matrix[i];

  delete[] matrix;
}

/**
 * @brief Destructor
 */
DesktopView::~DesktopView() {
  delete HighScore_;
  delete Score_;
  delete Level_;

  delete textNext_;

  removeFieldMatrix(gameField_, heightGameField_);

  if (nextField_) removeFieldMatrix(nextField_, 5);

  delete nextView_;
  delete nextScene_;

  delete infoTable_;

  delete gameView_;
  delete gameScene_;

  delete gameLayout_;

  delete wid_;
}
}  // namespace s21