#include "../inc/snakeModel.h"

namespace s21 {

/**
 * @brief Snake constructor
 * @param count Size of the snake
 */
SnakeModel::Snake::Snake(int count)
    : snake_(count), direction_(Direction::Right) {
  snake_.reserve(201);

  for (int i = 0; i < count; ++i) {
    snake_[i].y = 7;
    snake_[i].x = 5 - i;
  }
}

/**
 * @brief Snake destructor
 */
SnakeModel::Snake::~Snake() {}

/**
 * @brief Bringing the snake to its initial state
 */
void SnakeModel::Snake::reset() {
  int count = 4;

  snake_.resize(count);

  for (int i = 0; i < count; ++i) {
    snake_[i].y = 7;
    snake_[i].x = 5 - i;
  }

  direction_ = Direction::Right;
}

/**
 * @brief Setting the direction of the snake
 * @param direction Direction
 */
void SnakeModel::Snake::setDirection(Direction direction) {
  switch (direction) {
    case Direction::Right:
      if (direction_ != Direction::Left) direction_ = direction;
      break;
    case Direction::Left:
      if (direction_ != Direction::Right) direction_ = direction;
      break;
    case Direction::Up:
      if (direction_ != Direction::Down) direction_ = direction;
      break;
    case Direction::Down:
      if (direction_ != Direction::Up) direction_ = direction;
      break;
  }
}

/**
 * @brief Getting the coordinates of the snake segment
 * @return Coordinates
 */
const Point &SnakeModel::Snake::operator[](int index) const {
  return snake_[index];
}

/**
 * @brief Getting the size of the snake
 * @return Size of the snake
 */
int SnakeModel::Snake::size() const { return snake_.size(); }

/**
 * @brief Moving the snake one step
 */
void SnakeModel::Snake::move() {
  for (int i = snake_.size() - 1; i > 0; --i) snake_[i] = snake_[i - 1];

  switch (direction_) {
    case Direction::Right:
      snake_[0].x += 1;
      break;
    case Direction::Left:
      snake_[0].x -= 1;
      break;
    case Direction::Up:
      snake_[0].y -= 1;
      break;
    case Direction::Down:
      snake_[0].y += 1;
      break;
  }
}

/**
 * @brief Adding a segment to the snake tail
 */
void SnakeModel::Snake::addSegment() {
  snake_.push_back(snake_[snake_.size() - 2]);
}

/**
 * @brief SnakeModel constructor
 */
SnakeModel::SnakeModel()
    : state_(State::Launch),
      gameField_{newMatrix(static_cast<int>(Field::height),
                           static_cast<int>(Field::width))},
      gameInfo_{gameInfoInit()},
      score_(0),
      high_score_(getHighScore("records/records")),
      level_(1),
      snake_(4),
      apple_({4, 7}),
      key_(0),
      lastKey_(0),
      gameOver_(false) {
  int heightField = static_cast<int>(Field::height);
  int widthField = static_cast<int>(Field::width);

  for (int i = 0; i < heightField; ++i)
    for (int j = 0; j < widthField; ++j) {
      if (((j == 0 || j == 11) || i == heightField - 1))
        gameField_[i][j] = '\0';
      else
        gameField_[i][j] = ' ';
    }

  gameField_[0][0] = heightField;
  gameField_[1][0] = widthField;

  gameInfo_.high_score = high_score_;
}

/**
 * @brief SnakeModel destructor
 */
SnakeModel::~SnakeModel() {
  int heightField = static_cast<int>(Field::height);

  for (int i = 0; i < heightField; ++i) delete[] gameField_[i];
  delete[] gameField_;
}

/**
 * @brief Game info structure initialization
 */
GameInfo_t SnakeModel::gameInfoInit() {
  GameInfo_t gameInfo;

  gameInfo.field = gameField_;
  gameInfo.next = nullptr;

  gameInfo.high_score = 0;
  gameInfo.score = 0;
  gameInfo.level = 1;
  gameInfo.speed = defineTime(gameInfo.level);

  gameInfo.pause = 0;

  return gameInfo;
}

/**
 * @brief Reset game info structure
 */
void SnakeModel::resetGameInfo() {
  gameInfo_.high_score = -1;
  gameInfo_.score = -1;
  gameInfo_.level = -1;
}

/**
 * @brief Setting startup settings
 */
void SnakeModel::startGame() {
  gameOver_ = false;

  gameInfo_.high_score = high_score_;
  gameInfo_.score = score_;
  gameInfo_.level = level_;
}

/**
 * @brief Reset game settings
 */
void SnakeModel::resetGame() {
  gameOver_ = true;

  score_ = 0;
  level_ = 1;

  gameInfo_.high_score = high_score_;
  gameInfo_.score = score_;
  gameInfo_.level = level_;
  gameInfo_.speed = defineTime(level_);

  clearGameField();
  snake_.reset();
  apple_ = {4, 7};
}

/**
 * @brief User input accepts a user action as input
 * @param action User action
 * @param hold Hold action
 * @see UserAction_t
 *
 * @details Is the entry point into the game logic
 */
void SnakeModel::userInput(UserAction_t action, bool hold) {
  for (int i = 0, iterations_num = 1; i < iterations_num; ++i) {
    switch (state_) {
      case State::Launch:

        if (action == UserAction_t::Terminate) {
          saveHighScore("records/records", high_score_);
          return;
        }

        if (action == UserAction_t::Start && key_ == ENTER) {
          startGame();
          state_ = State::Spawn;
          iterations_num++;
        }
        break;

      case State::Spawn:

        removeSnake();
        putSnake();
        spawnApple();
        putApple();
        state_ = State::Moving;
        break;

      case State::Moving:

        resetGameInfo();
        actionProcessing(action, hold);
        if (state_ == State::Attaching) iterations_num++;
        break;

      case State::Attaching:

        if (isAppleCollision()) {
          appleEating();
          state_ = State::Spawn;
          iterations_num++;
          if (snake_.size() >= 200) {
            saveHighScore("records/records", score_);
            state_ = State::Win;
            break;
          }
          state_ = State::Spawn;
          break;
        }

        // isWallCollision() || isInnerCollision()
        state_ = State::GameOver;
        iterations_num++;
        break;

      case State::GameOver:

        resetGame();
        state_ = State::Launch;
        break;

      case State::Win:

        removeSnake();
        putSnake();
        break;

      default:
        break;
    }
  }

  gameInfo_.field = gameField_;
  lastKey_ = key_;
}

/**
 * @brief Action processing
 * @param action User action
 * @param hold Hold action
 */
void SnakeModel::actionProcessing(UserAction_t action, bool hold) {
  if (gameInfo_.pause && (action != Pause && action != Terminate)) return;

  switch (action) {
    case UserAction_t::Up:
      snake_.setDirection(Direction::Up);
      break;
    case UserAction_t::Left:
      snake_.setDirection(Direction::Left);
      break;
    case UserAction_t::Right:
      snake_.setDirection(Direction::Right);
      break;
    case UserAction_t::Down:
      snake_.setDirection(Direction::Down);
      break;
    case UserAction_t::Action:  // BOOST
      break;
    case UserAction_t::Pause:
      gameInfo_.pause = !gameInfo_.pause;
      return;
    case UserAction_t::Terminate:
      saveHighScore("records/records", high_score_);
      return;
    case UserAction_t::Start:
      break;
  }

  if (hold && action != UserAction_t::Action && key_ != -1)
    hold_counter++;
  else
    hold_counter = 0;

  if (isTurn(action) && lastKey_ != key_) hold_counter = 0;

  if (hold_counter > 2 && hold_counter % 6 != 0) return;

  removeSnake();
  snake_.move();

  if (!isCollision())
    putSnake();
  else
    state_ = State::Attaching;
}

/**
 * @brief Clear game field
 */
void SnakeModel::clearGameField() {
  int heightField = static_cast<int>(Field::height);
  int widthField = static_cast<int>(Field::width);

  for (int i = 0; i < heightField - 1; ++i)
    std::fill(gameField_[i] + 1, gameField_[i] + widthField - 1, ' ');
}

/**
 * @brief Check if there is an apple collision
 * @return True if there is an apple collision
 */
bool SnakeModel::isAppleCollision() {
  return (snake_[0].x == apple_.x && snake_[0].y == apple_.y);
}

/**
 * @brief Check if there is a wall collision
 * @return True if there is a wall collision
 */
bool SnakeModel::isWallCollision() {
  int heightField = static_cast<int>(Field::height);
  int widthField = static_cast<int>(Field::width);

  return (snake_[0].x < 1 || snake_[0].x > widthField - 2) ||
         (snake_[0].y < 0 || snake_[0].y > heightField - 2);
}

/**
 * @brief Check if there is an inner collision
 * @return True if there is an inner collision
 */
bool SnakeModel::isInnerCollision() {
  for (int i = 1; i < snake_.size(); ++i)
    if (snake_[0].y == snake_[i].y && snake_[0].x == snake_[i].x) return true;

  return false;
}

/**
 * @brief Check if there is a collision
 */
bool SnakeModel::isCollision() {
  return isAppleCollision() || isWallCollision() || isInnerCollision();
}

/**
 * @brief Put snake on the field
 */
void SnakeModel::putSnake() {
  for (int i = 1; i < snake_.size(); ++i)
    gameField_[snake_[i].y][snake_[i].x] = FigureSymbol::FigureSym + 3;

  gameField_[snake_[0].y][snake_[0].x] =
      FigureSymbol::FigureSym + 6;  // light green
}

/**
 * @brief Remove snake from the field
 */
void SnakeModel::removeSnake() {
  for (int i = 0; i < snake_.size(); ++i)
    gameField_[snake_[i].y][snake_[i].x] = ' ';
}

/**
 * @brief Put apple on the field
 */
void SnakeModel::putApple() {
  gameField_[apple_.y][apple_.x] = FigureSymbol::FigureSym + 1;
}

/**
 * @brief Remove apple from the field
 */
void SnakeModel::removeApple() { gameField_[apple_.y][apple_.x] = ' '; }

/**
 * @brief Spawn apple new position
 */
void SnakeModel::spawnApple() {
  int heightField = static_cast<int>(Field::height);
  int widthField = static_cast<int>(Field::width);

  Point freeSpace[210] = {0, 0};
  int freeSpaceCount = 0;

  for (int i = 0; i < heightField - 1; ++i)
    for (int j = 1; j < widthField - 1; ++j) {
      if (gameField_[i][j] == ' ') {
        freeSpace[freeSpaceCount].x = j;
        freeSpace[freeSpaceCount].y = i;
        freeSpaceCount++;
      }
    }

  int randomIndex = rand() % freeSpaceCount;
  apple_ = freeSpace[randomIndex];
}

/**
 * @brief Apple eating logic
 */
void SnakeModel::appleEating() {
  removeApple();
  snake_.addSegment();
  score_++;

  if (score_ > high_score_) {
    high_score_ = score_;
    gameInfo_.high_score = high_score_;
  }

  if (score_ % 5 == 0) {
    if (level_ < 10) level_++;

    gameInfo_.level = level_;
    gameInfo_.speed = defineTime(level_);
  }

  gameInfo_.score = score_;
}

/**
 * @brief Define time for timer
 * @param time Time
 */
int SnakeModel::defineTime(int time) {
  int n = 0;

  if (time <= 5)
    n = 24;
  else if (time <= 9)
    n = 23;
  else if (time <= 10)
    n = 25;

  return 600 - time * n;
}

/**
 * @brief Checks if the action is a turn
 * @param action User action
 * @return True if the action is a turn
 */
bool SnakeModel::isTurn(UserAction_t action) {
  return action >= UserAction_t::Left && action <= UserAction_t::Down;
}

/**
 * @brief Update current state of the game
 * @return Copied structure of game information
 * @see GameInfo_t
 *
 * @details The view uses a structure for rendering
 */
GameInfo_t SnakeModel::updateCurrentState() { return gameInfo_; }

/**
 * @brief Set key for cuurent input
 * @param key Input key
 */
void SnakeModel::setKey(int key) { key_ = key; }

/**
 * @brief Get last input key
 * @return Last key
 */
int SnakeModel::getLastKey() { return lastKey_; }

/**
 * @brief Get current state of the game
 * @return Current state
 * @see State
 */
State SnakeModel::getState() { return gameOver_ ? State::GameOver : state_; }

/**
 * @brief Create new matrix
 * @param height Height
 * @param width Width
 * @return New matrix
 */
int **SnakeModel::newMatrix(int height, int width) {
  int **field = new int *[height];

  for (int i = 0; i < height; ++i) field[i] = new int[width];

  return field;
}

/**
 * @brief Save high score to the file
 * @param path Path to the file
 * @param high_score High score
 */
void saveHighScore(const char *path, int high_score) {
  mkdir("records", 0777);

  std::ofstream file(path);

  if (!file.is_open()) return;

  file << "HighScore = " << high_score;

  file.close();
}

/**
 * @brief Get high score from the file
 * @param path Path to the file
 * @return High score
 */
int getHighScore(const char *path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    return 0;
  }

  std::string line;
  int high_score = 0;

  while (std::getline(file, line)) {
    if (line.find("HighScore = ") != std::string::npos) {
      int n = sscanf(line.c_str(), "HighScore = %d", &high_score);
      if (n < 1) high_score = 0;

      break;
    }
  }

  file.close();
  return high_score;
}
}  // namespace s21