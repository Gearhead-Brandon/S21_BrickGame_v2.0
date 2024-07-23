/*!
    @file
    @brief Tetris backend part implementation
*/
#include "../inc/tetris.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../../components/cmatrix/cmatrix.h"

static GameInfo_t gameInfo;
static TetrisGame game;

/*!
  @brief Tetris backend initialization
*/
void TetrisGameInit() {
  game.state = Launch;

  game.clicks = 0;

  game.blocking = 0;

  game.key = 0;

  game.last_key = -1;

  game.move = 0;
}

/*!
    @brief Update current state
    @return Copied structure of game information
*/
GameInfo_t updateCurrentState() { return gameInfo; }

/*!
    @brief Get last pressed key
    @return Last pressed key
*/
int getTetrisLastKey() { return game.last_key; }

/*!
    @brief Get current state
    @return Current state
*/
State getTetrisState() { return game.state; }

/*!
    @brief Initialize game information
*/
void TetrisGameInfoInit() {
  CreateMatrix(FieldRows, FieldCols, &gameInfo.field);

  for (int i = 0; i < FieldRows; i++)
    for (int j = 0; j < FieldCols; j++)
      if ((j == 0 || j == 11) || i == FieldRows - 1)
        gameInfo.field[i][j] = '\0';
      else
        gameInfo.field[i][j] = ' ';

  gameInfo.field[0][0] = FieldRows;  // height
  gameInfo.field[1][0] = FieldCols;

  CreateMatrix(4, 6, &gameInfo.next);

  gameInfo.score = 0;

  gameInfo.high_score = GetHighScore("records/records");

  gameInfo.level = 1;

  gameInfo.speed = defineTetrisTime(gameInfo.level);

  gameInfo.pause = 0;

  SetNextFigure(rand() % 7);

  gameInfo.next[0][5] = rand() % 7;  // next color
}

/*!
    @brief Delete game structure
*/
void DeleteGameInfo() {
  if (gameInfo.field) RemoveMatrix(gameInfo.field, FieldRows);

  if (gameInfo.next) RemoveMatrix(gameInfo.next, 4);
}

/*!
    @brief Assigning symbol matrix elements to spaces
    @param field Field
    @param row1 First row
    @param row2 Last row
    @param col1 First column
    @param col2 Last column
*/
void ClearField(int **field, int row1, int row2, int col1, int col2) {
  for (int i = row1; i <= row2; i++) {
    for (int j = col1; j <= col2; j++) {
      field[i][j] = ' ';
    }
  }
}

/*!
    @brief Removing the current figure from the field
    @param axis Axis
    @param term Term

    Removing the current figure from the field and shifting it to a term.
    Also color field clearing
*/
void ResettingOldFigure(int axis, int term) {
  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = gameInfo.next[0][i];  // x
    y = gameInfo.next[1][i];  // y

    gameInfo.field[x][y] = ' ';

    gameInfo.next[axis][i] += term;
  }
}

/*!
    @brief Checking for cell accessibility after shift
    @return Count of free cells
*/
int CheckingFreePosition() {
  int count = 0;

  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = gameInfo.next[0][i];  // x
    y = gameInfo.next[1][i];  // y

    if (gameInfo.field[x][y] >= ' ' && gameInfo.field[x][y] < FigureSym)
      count++;
  }

  return count;
}

/*!
    @brief Returning the figure back
    @param axis Axis
    @param term Term

    If the field spaces are already occupied, then return the figure back
*/
void ReturnFigureBack(int axis, int term) {
  for (int i = 0; i < 4; i++) gameInfo.next[axis][i] -= term;
}

/*!
    @brief Shifting a piece down the field onto a cell
*/
void FigureDown() {
  if (game.state != Shifting) return;

  bool figure_is_stopped = false;

  ResettingOldFigure(0, 1);

  int number_of_free_positions = CheckingFreePosition();

  if (number_of_free_positions != 4) {
    ReturnFigureBack(0, 1);
    figure_is_stopped = true;
  }

  if (figure_is_stopped) game.state = Attaching;

  TransferFigureToField();
}

/*!
    @brief Takes a new figure from figures.c

    Also color field filling and setting the next figure and her color
*/
void DropFigure() {
  int number = GetNextFigure();

  gameInfo.next[1][5] = gameInfo.next[0][5];

  SetCurrentFigure(number);

  // for (int i = 0, k = 0; (i < 2); i++)
  //   for (int j = 3, f_j = 0; (j < 8); j++, f_j++) {

  //     if (getFigureIndex(number * 2 + i,f_j)) {
  //       gameInfo.next[0][k] = i; // x

  //  	    gameInfo.next[1][k] = j; // y

  //       k++;
  //     }
  //   }

  for (int i = 0, k = 0; (i < 2); i++)
    for (int j = 3, f_j = 0; (j < 7); j++, f_j++) {
      if (gameInfo.next[i + 2][f_j]) {
        gameInfo.next[0][k] = i;

        gameInfo.next[1][k] = j + 1;

        k++;
      }
    }

  number = (rand() % 7);

  SetNextFigure(number);

  gameInfo.next[0][5] = rand() % 7;

  TransferFigureToField();
}

/*!
    @brief Set next figure
    @param next Next figure
*/
void SetNextFigure(int next) {
  gameInfo.next[0][4] = next;

  for (int i = 0, i_ = 2; i < 2; ++i, ++i_)
    for (int j = 1; j < 5; ++j) {
      if (getFigureIndex(next * 2 + i, j))
        gameInfo.next[i_][j - 1] = 1;
      else
        gameInfo.next[i_][j - 1] = 0;
    }
}

/*!
    @brief Get next figure
    @return Next figure
*/
int GetNextFigure() { return gameInfo.next[0][4]; }

/*!
    @brief Set current figure
    @param current Current figure
*/
void SetCurrentFigure(int current) { gameInfo.next[1][4] = current; }

/*!
    @brief Get current figure
    @return Current figure
*/
int GetCurrentFigure() { return gameInfo.next[1][4]; }

/*!
    @brief Transfer figure to field and color to color field
*/
void TransferFigureToField() {
  for (int i = 0, x = 0, y = 0; i < 4; i++) {
    x = gameInfo.next[0][i];
    y = gameInfo.next[1][i];

    gameInfo.field[x][y] = FigureSym + gameInfo.next[1][5];
  }
}

/*!
    @brief Move horizontal
    @param side Left or right
*/
void MoveHorizontal(char *side) {
  int step = (!strcmp(side, "left")) ? -1 : 1;

  ResettingOldFigure(1, step);

  int number_of_free_positions = CheckingFreePosition();

  if (number_of_free_positions != 4) ReturnFigureBack(1, step);

  TransferFigureToField();
}

/*!
    @brief Rotating a figure via the rotation matrix
*/
void Rotate() {
  if (GetCurrentFigure() == 4) return;

  int px = gameInfo.next[0][2];
  int py = gameInfo.next[1][2];

  ResettingOldFigure(0, 0);

  int collision = 0;

  for (int i = 0; i < 4; i++) {
    int x1 = gameInfo.next[0][i];
    int y1 = gameInfo.next[1][i];

    int x2 = px + py - y1;
    int y2 = x1 + py - px;

    if (x2 < 0 || x2 >= FieldRows || y2 < 0 || y2 >= RightBorder ||
        !(gameInfo.field[x2][y2] >= ' ' && gameInfo.field[x2][y2] < FigureSym))
      collision = 1;
  }

  if (!collision)
    for (int i = 0; i < 4; i++) {
      int x1 = gameInfo.next[0][i];
      int y1 = gameInfo.next[1][i];

      gameInfo.next[0][i] = px + py - y1;
      gameInfo.next[1][i] = py - (px - x1);
    }

  TransferFigureToField();
}

/*!
    @brief Checking the end of the game after attaching
*/
void GameOverCheck() {
  for (int i = 0; i < 2; i++)
    for (int j = LeftBorder; j < RightBorder; j++) {
      if (gameInfo.field[i][j] >= FigureSym) {
        game.state = GameOver;
        return;
      }
    }
}

/*!
    @brief Removing filled lines

    Replenishment of points after the destruction of lines
    and shifting the field down a cell
*/
void RemovingFilledLines() {
  int removed_lines = 0, count = 0;

  for (int i = FieldRows - 2; i > 1; i--) {
    for (int j = LeftBorder; j < RightBorder; j++)
      if (gameInfo.field[i][j] >= FigureSym) count++;

    if (count == 10) {
      FieldDown(i);
      removed_lines++;
      i++;
    }

    count = 0;
  }

  ProcessingRemovedLines(removed_lines);
}

/*!
    @brief Increase in points from destroying lines

    Also updating the record and increasing the level with speed
*/
void ProcessingRemovedLines(int removed_lines) {
  int score = 0;

  switch (removed_lines) {
    case 1:
      score = 100;
      break;
    case 2:
      score = 300;
      break;
    case 3:
      score = 700;
      break;
    case 4:
      score = 1500;
      break;
    default:
      break;
  }

  gameInfo.score += score;

  if (gameInfo.score > gameInfo.high_score)
    gameInfo.high_score = gameInfo.score;

  int level_increase = gameInfo.score / 600 + 1;

  if (level_increase > 10) level_increase = 1;

  gameInfo.level = level_increase;
  gameInfo.speed = defineTetrisTime(gameInfo.level);
}

/*!
    @brief Shifting the field down a cell
*/
void FieldDown(int row) {
  for (int i = row; i >= 1; i--)
    for (int j = LeftBorder, c_j = 0; j < RightBorder; j++, c_j++)
      gameInfo.field[i][j] = gameInfo.field[i - 1][j];

  for (int j = LeftBorder; j < RightBorder; j++) gameInfo.field[0][j] = ' ';
}

/*!
    @brief Saving the high score to the file
    @param path Path to the file
*/
void SaveHighScore(const char *path) {
  mkdir("records", 0777);

  FILE *filePointer = fopen(path, "w");

  if (filePointer == NULL) return;

  fprintf(filePointer, "HighScore = %d", gameInfo.high_score);

  fclose(filePointer);
}

/*!
    @brief Getting the high score from the file
    @param path Path to the file
*/
int GetHighScore(const char *path) {
  FILE *filePointer = fopen(path, "r");

  if (filePointer == NULL) return 0;

  char line[256] = {0};

  int high_score = 0;

  while (fgets(line, 256, filePointer) != NULL) {
    if (strstr(line, "HighScore = ") != NULL) {
      int n = 0;
      n = sscanf(line, "HighScore = %d", &high_score);

      if (n < 1) high_score = 0;

      break;
    }
  }

  fclose(filePointer);

  return high_score;
}

/*!
    @brief Restarting the game after game over
*/
void Restart() {
  ClearField(gameInfo.field, 0, FieldRows - 2, LeftBorder, RightBorder - 1);

  gameInfo.score = 0;
  gameInfo.level = 1;
  gameInfo.speed = defineTetrisTime(gameInfo.level);
  gameInfo.pause = 0;
}

/*!
    @brief Attaching stage
*/
void AttachingStage() {
  GameOverCheck();

  if (game.state == GameOver) {
    Restart();
    return;
  }

  RemovingFilledLines();

  game.state = Spawn;
}

/*!
    @brief Processing status after user input
    @param action User action
*/
int StatusProcessing(UserAction_t action) {
  if (game.key == ENTER && (game.state == Launch || game.state == GameOver)) {
    game.state = Spawn;
    game.blocking = 1;
  }

  if (action == Start && game.key != -1) game.blocking = 1;

  if (gameInfo.pause && game.key != PAUSE && game.key != QUIT) return 1;

  game.clicks = (game.clicks == 5) ? 1 : game.clicks + 1;

  return 0;
}

/*!
    @brief Control of the game logic
    @param action User action
    @param hold Flag of hold
*/
void userInput(UserAction_t action, bool hold) {
  // game.key = new_key;
  game.last_key = game.key;

  if (StatusProcessing(action)) return;

  if (game.state == Moving || action == Terminate) {
    actionProcessing(action, hold);

    if (action == Up || action == Terminate) return;

    if (action != Pause) ShiftingProcessing();
  }

  if (game.state == Spawn) {
    DropFigure();
    game.state = Moving;
  }
}

/*!
    @brief Process user input
    @param action User action
    @param hold Hold action
*/
void actionProcessing(UserAction_t action, bool hold) {
  switch (action) {
    case Up:
      break;
    case Action:  // Rotate
      Rotate();
      game.move = 1;
      break;
    case Right:
      MoveHorizontal("right");
      game.move = 1;
      break;
    case Left:
      MoveHorizontal("left");
      game.move = 1;
      break;
    case Down:
      if (hold) gameInfo.speed = defineTetrisTime(gameInfo.level + 1);
      break;
    case Pause:
      // gameInfo.pause = (gameInfo.pause) ? 0 : 1;
      gameInfo.pause = !gameInfo.pause;
      break;
    case Terminate:
      SaveHighScore("records/records");
      return;
    default:
      break;
  }

  if (action == Down && !hold)
    gameInfo.speed = defineTetrisTime(gameInfo.level);
}

/*!
    @brief Processing shifting and state after moving
*/
void ShiftingProcessing() {
  int click = game.clicks % 5;

  game.state = Shifting;

  if ((!game.move || click == 0) && !game.blocking) FigureDown();

  game.blocking = 0;
  game.move = 0;

  if (game.state == Attaching)
    AttachingStage();
  else
    game.state = Moving;
}

/*!
    @brief Define tetris time
    @param level Level
*/
int defineTetrisTime(int level) { return 600 - level * 25; }

/*!
    @brief Set new pressed key
    @param new_key New pressed key
*/
void setKey(int new_key) { game.key = new_key; }