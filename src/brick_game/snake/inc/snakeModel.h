/**
 * @file
 * @brief Header file for SnakeModel
 */

#ifndef SNAKE_H
#define SNAKE_H

#ifdef __cplusplus

#include <fstream>
#include <iostream>
#include <vector>

#include "../../../components/Interfaces/IModel.h"

extern "C" {
#endif

#include <sys/stat.h>

#ifdef __cplusplus
}
#endif

namespace s21 {

/**
 * @brief Save high score to the file
 * @param path Path to the file
 * @param high_score High score
 */
void saveHighScore(const char* path, int high_score);

/**
 * @brief Get high score from the file
 * @param path Path to the file
 * @return High score
 */
int getHighScore(const char* path);

/**
 * @brief Enum for game field
 */
enum class Field : int {
  height = 21,  ///< Height of the game field
  width = 12    ///< Width of the game field
};

/**
 * @brief Enum for direction of the snake
 */
enum class Direction : int {
  Up = 0,  ///< Up
  Right,   ///< Right
  Down,    ///< Down
  Left     ///< Left
};

/**
 * @brief Structure for coordinates
 */
struct Point {
  int y;  ///< Y coordinate
  int x;  ///< X coordinate
};

/**
 * @brief Class for Snake model
 * @see IModel
 */
class SnakeModel : public IModel {
  /**
   * @brief Class for snake
   */
  class Snake {
    ///! @brief Snake
    std::vector<Point> snake_;

    ///! @brief Direction
    Direction direction_;

   public:
    /**
     * @brief Snake constructor
     * @param count Size of the snake
     */
    Snake(int count);

    /**
     * @brief Snake destructor
     */
    ~Snake();

    /**
     * @brief Bringing the snake to its initial state
     */
    void reset();

    /**
     * @brief Setting the direction of the snake
     * @param direction Direction
     */
    void setDirection(Direction direction);

    /**
     * @brief Moving the snake one step
     */
    void move();

    /**
     * @brief Adding a segment to the snake tail
     */
    void addSegment();

    /**
     * @brief Getting the size of the snake
     * @return Size of the snake
     */
    int size() const;

    /**
     * @brief Getting the coordinates of the snake segment
     * @return Coordinates
     */
    const Point& operator[](int index) const;
  };

  //! @brief Current state
  State state_;

  //! @brief Game field matrix
  int** gameField_;

  //! @brief Game info structure
  GameInfo_t gameInfo_;

  //! @brief Score
  int score_;

  //! @brief High score
  int high_score_;

  //! @brief Level
  int level_;

  //! @brief Snake
  Snake snake_;

  //! @brief Apple
  Point apple_;

  //! @brief Key for user input
  int key_;

  //! @brief Last key for user input
  int lastKey_;

  //! @brief Flag for game over
  bool gameOver_;

  //! @brief Clicks counter
  int hold_counter = 0;

 public:
  /**
   * @brief SnakeModel constructor
   */
  SnakeModel();

  /**
   * @brief SnakeModel destructor
   */
  ~SnakeModel() override;

  /**
   * @brief User input accepts a user action as input
   * @param action User action
   * @param hold Hold action
   * @see UserAction_t
   *
   * @details Is the entry point into the game logic
   */
  void userInput(UserAction_t action, bool hold) override;

  /**
   * @brief Update current state of the game
   * @return Copied structure of game information
   * @see GameInfo_t
   *
   * @details The view uses a structure for rendering
   */
  GameInfo_t updateCurrentState() override;

  /**
   * @brief Set key for cuurent input
   * @param key Input key
   */
  void setKey(int new_key) override;

  /**
   * @brief Get last input key
   * @return Last key
   */
  int getLastKey() override;

  /**
   * @brief Get current state of the game
   * @return Current state
   * @see State
   */
  State getState() override;

 private:
  /**
   * @brief Game info structure initialization
   */
  GameInfo_t gameInfoInit();

  /**
   * @brief Action processing
   * @param action User action
   * @param hold Hold action
   */
  void actionProcessing(UserAction_t action, bool hold);

  /**
   * @brief Setting startup settings
   */
  void startGame();

  /**
   * @brief Reset game settings
   */
  void resetGame();

  /**
   * @brief Reset game info structure
   */
  void resetGameInfo();

  /**
   * @brief Remove snake from the field
   */
  void removeSnake();

  /**
   * @brief Put snake on the field
   */
  void putSnake();

  /**
   * @brief Remove apple from the field
   */
  void removeApple();

  /**
   * @brief Put apple on the field
   */
  void putApple();

  /**
   * @brief Spawn apple new position
   */
  void spawnApple();

  /**
   * @brief Apple eating logic
   */
  void appleEating();

  /**
   * @brief Clear game field
   */
  void clearGameField();

  /**
   * @brief Check if there is a collision
   * @return True if there is a collision
   */
  bool isCollision();

  /**
   * @brief Check if there is an apple collision
   * @return True if there is an apple collision
   */
  bool isAppleCollision();

  /**
   * @brief Check if there is a wall collision
   * @return True if there is a wall collision
   */
  bool isWallCollision();

  /**
   * @brief Check if there is an inner collision
   * @return True if there is an inner collision
   */
  bool isInnerCollision();

  /**
   * @brief Checks if the action is a turn
   * @param action User action
   * @return True if the action is a turn
   */
  bool isTurn(UserAction_t action);

  /**
   * @brief Define time for timer
   * @param time Time
   */
  int defineTime(int time);

  /**
   * @brief Create new matrix
   * @param height Height
   * @param width Width
   * @return New matrix
   */
  int** newMatrix(int height, int width);
};
}  // namespace s21

#endif