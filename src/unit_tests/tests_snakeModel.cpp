#include "tests_entry.h"

void printField(int **field);
void moveHead(s21::Point &head, UserAction_t action);
void fieldByPass(s21::SnakeModel *model, int count);

class SnakeTest : public ::testing::Test {
 protected:
  s21::SnakeModel *model;

  void SetUp() override { model = new s21::SnakeModel(); }
  void TearDown() override { delete model; }
};

TEST_F(SnakeTest, Constructor) {
  // Act
  GameInfo_t gameInfo = model->updateCurrentState();
  int height = gameInfo.field[0][0];
  int width = gameInfo.field[1][0];

  gameInfo.field[0][0] = 0;
  gameInfo.field[1][0] = 0;

  // Assert
  EXPECT_EQ(height, static_cast<int>(s21::Field::height));
  EXPECT_EQ(width, static_cast<int>(s21::Field::width));

  EXPECT_TRUE(gameInfo.high_score == 0 || gameInfo.high_score == 196);
  EXPECT_EQ(gameInfo.score, 0);
  EXPECT_EQ(gameInfo.level, 1);
  EXPECT_EQ(gameInfo.pause, 0);
  EXPECT_EQ(gameInfo.speed, 576);

  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j) {
      if (((j == 0 || j == 11) || i == height - 1))
        EXPECT_EQ(gameInfo.field[i][j], '\0');
      else
        EXPECT_EQ(gameInfo.field[i][j], ' ');
    }

  EXPECT_EQ(model->getState(), State::Launch);
}

TEST_F(SnakeTest, LaunchStage) {
  // Act
  model->setKey(Keys::PAUSE);
  UserAction_t action = UserAction_t::Pause;
  bool hold = false;
  model->userInput(action, hold);

  action = UserAction_t::Start;
  model->userInput(action, hold);

  action = Terminate;
  model->userInput(action, hold);

  std::string filePath = "records/records";
  std::ifstream file(filePath);

  if (file.is_open()) {
    std::string line;
    int high_score = 0;

    while (std::getline(file, line)) {
      if (line.find("HighScore = ") != std::string::npos) {
        sscanf(line.c_str(), "HighScore = %d", &high_score);
        EXPECT_TRUE(high_score == 0 || high_score == 196);
        break;
      }
    }

    file.close();
    std::filesystem::remove(filePath);
    std::filesystem::remove(filePath.substr(0, filePath.find_last_of("/")));
  }

  // Assert
  EXPECT_EQ(model->getLastKey(), Keys::PAUSE);

  // Act
  action = Start;
  model->setKey(Keys::ENTER);
  model->userInput(action, hold);

  // Assert
  EXPECT_EQ(model->getState(), State::Moving);
}

TEST_F(SnakeTest, SpawnStage) {
  // Act
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;

  model->userInput(action, hold);

  GameInfo_t gameInfo = model->updateCurrentState();
  int height = gameInfo.field[0][0];
  int width = gameInfo.field[1][0];

  int isApple = 0;

  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j)
      if (gameInfo.field[i][j] == 43) {
        isApple = 1;
        break;
      }

  // Assert
  EXPECT_EQ(model->getState(), State::Moving);
  EXPECT_EQ(isApple, 1);

  for (int i = 2; i < 6; ++i) EXPECT_TRUE(gameInfo.field[7][i] >= FigureSym);
}

TEST_F(SnakeTest, MovingForward) {
  // Act
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;

  model->userInput(action, hold);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, hold);
  model->userInput(UserAction_t::Down, hold);
  hold = true;

  for (int i = 0; i < 6; i++) model->userInput(UserAction_t::Down, hold);

  model->setKey(Keys::ArrowRight);
  model->userInput(UserAction_t::Right, hold);

  GameInfo_t gameInfo = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getState(), State::Moving);

  EXPECT_TRUE(gameInfo.field[10][5] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[11][5] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[12][5] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[12][6] >= FigureSym);

  // Act
  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Left, false);

  // Assert
  EXPECT_TRUE(gameInfo.field[11][5] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[12][5] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[12][6] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[12][7] >= FigureSym);

  // Act
  model->setKey(Keys::ArrowUp);
  model->userInput(UserAction_t::Up, false);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, false);

  // Assert
  EXPECT_TRUE(gameInfo.field[12][6] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[12][7] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[11][7] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[10][7] >= FigureSym);

  // Act
  model->setKey(Keys::ArrowRight);
  model->userInput(UserAction_t::Right, false);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, false);

  model->setKey(Keys::ArrowUp);
  model->userInput(UserAction_t::Up, false);

  // Assert
  EXPECT_TRUE(gameInfo.field[10][7] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[10][8] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[11][8] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[12][8] >= FigureSym);

  // Act
  model->setKey(Keys::ArrowDown);

  for (int i = 0; i < 4; i++) model->userInput(UserAction_t::Down, true);

  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Left, false);

  model->setKey(Keys::ArrowRight);
  model->userInput(UserAction_t::Right, false);

  // Assert
  EXPECT_TRUE(gameInfo.field[14][8] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[15][8] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[15][7] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[15][6] >= FigureSym);

  // Act
  model->setKey(Keys::ACTION);
  model->userInput(UserAction_t::Action, false);

  // Assert
  EXPECT_TRUE(gameInfo.field[15][8] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[15][7] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[15][6] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[15][5] >= FigureSym);
}

TEST_F(SnakeTest, PauseWithTerminate) {
  // Act
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;

  model->userInput(action, hold);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, hold);
  model->userInput(UserAction_t::Down, hold);
  hold = true;

  model->setKey(Keys::PAUSE);
  model->userInput(UserAction_t::Pause, hold);

  GameInfo_t gameInfo_first = model->updateCurrentState();

  model->setKey(Keys::ArrowRight);
  model->userInput(UserAction_t::Right, hold);

  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Left, hold);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, hold);

  GameInfo_t gameInfo_second = model->updateCurrentState();
  int height = gameInfo_second.field[0][0];
  int width = gameInfo_second.field[1][0];

  // Assert
  EXPECT_EQ(model->getState(), State::Moving);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      EXPECT_EQ(gameInfo_first.field[i][j], gameInfo_second.field[i][j]);
    }
  }

  // Act
  model->setKey(Keys::PAUSE);
  model->userInput(UserAction_t::Pause, false);

  model->setKey(-1);
  model->userInput(UserAction_t::Start, false);

  GameInfo_t gameInfo_third = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getState(), State::Moving);

  for (int i = 7; i < 11; i++)
    EXPECT_TRUE(gameInfo_third.field[i][5] >= FigureSym);

  // Act
  model->setKey(Keys::PAUSE);
  model->userInput(UserAction_t::Pause, false);

  model->setKey(-1);
  model->userInput(UserAction_t::Start, false);

  model->setKey(QUIT);
  model->userInput(UserAction_t::Terminate, false);

  std::string filePath = "records/records";
  std::ifstream file(filePath);

  if (file.is_open()) {
    std::string line;
    int high_score = 0;

    while (std::getline(file, line)) {
      if (line.find("HighScore = ") != std::string::npos) {
        sscanf(line.c_str(), "HighScore = %d", &high_score);
        EXPECT_EQ(high_score, 0);
        break;
      }
    }

    file.close();
    std::filesystem::remove(filePath);
    std::filesystem::remove(filePath.substr(0, filePath.find_last_of("/")));
  }
}

TEST_F(SnakeTest, FieldBypass) {
  // Act
  fieldByPass(model, 5);

  GameInfo_t gameInfo = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getState(), State::Moving);

  EXPECT_TRUE(gameInfo.field[0][1] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[1][1] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[2][1] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[3][1] >= FigureSym);
}

TEST_F(SnakeTest, GameOverStageWithWallCollision) {
  // Act
  model->setKey(Keys::ENTER);
  UserAction_t action = UserAction_t::Start;
  bool hold = false;

  model->userInput(action, hold);

  model->setKey(Keys::ArrowUp);
  model->userInput(UserAction_t::Up, hold);
  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Left, hold);

  for (int i = 0; i < 12; i++) model->userInput(UserAction_t::Left, true);

  GameInfo_t gameInfo = model->updateCurrentState();
  int height = gameInfo.field[0][0];
  int width = gameInfo.field[1][0];

  // Assert
  EXPECT_EQ(model->getState(), State::GameOver);

  for (int i = 0; i < height - 1; ++i)
    for (int j = 1; j < width - 1; ++j) EXPECT_EQ(gameInfo.field[i][j], ' ');

  // Act
  model->setKey(Keys::ENTER);
  action = UserAction_t::Start;
  hold = false;
  model->userInput(action, hold);

  model->setKey(Keys::ArrowRight);
  model->userInput(UserAction_t::Right, true);

  model->setKey(-1);
  for (int i = 0; i < 5; i++) model->userInput(UserAction_t::Start, true);

  gameInfo = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getState(), State::GameOver);

  // Act
  model->setKey(Keys::ENTER);
  action = UserAction_t::Start;
  hold = false;
  model->userInput(action, hold);

  model->setKey(Keys::ArrowUp);
  model->userInput(UserAction_t::Up, true);

  model->setKey(-1);
  for (int i = 0; i < 7; i++) model->userInput(UserAction_t::Start, true);

  gameInfo = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getState(), State::GameOver);

  // Act
  model->setKey(Keys::ENTER);
  action = UserAction_t::Start;
  hold = false;
  model->userInput(action, hold);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, true);

  model->setKey(-1);
  for (int i = 0; i < 12; i++) model->userInput(UserAction_t::Start, true);

  gameInfo = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getState(), State::GameOver);
}

TEST_F(SnakeTest, InnerCollision) {
  // Act
  fieldByPass(model, 1);

  GameInfo_t gameInfo = model->updateCurrentState();

  // Assert
  EXPECT_EQ(model->getState(), State::Moving);

  EXPECT_TRUE(gameInfo.field[0][1] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[1][1] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[2][1] >= FigureSym);
  EXPECT_TRUE(gameInfo.field[3][1] >= FigureSym);

  // Act
  model->setKey(Keys::ArrowRight);
  model->userInput(UserAction_t::Right, false);

  model->setKey(Keys::ArrowDown);
  model->userInput(UserAction_t::Down, false);

  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Left, false);

  // Assert
  EXPECT_EQ(model->getState(), State::GameOver);
}

TEST(getHighCoreTest, getHighScore) {
  // Act
  int high_score = s21::getHighScore("test_records/records");

  // Assert
  EXPECT_EQ(high_score, 12);

  // Act
  high_score = s21::getHighScore("test_records/invalid_records");

  // Assert
  EXPECT_EQ(high_score, 0);

  // Act
  high_score = s21::getHighScore("test_records/notexist_records");

  // Assert
  EXPECT_EQ(high_score, 0);

  // Act
  high_score = s21::getHighScore("test_records/wrongformat_records");

  // Assert
  EXPECT_EQ(high_score, 0);
}

TEST_F(SnakeTest, WinStage) {
  // Act
  fieldByPass(model, 210);

  GameInfo_t gameInfo = model->updateCurrentState();
  int height = static_cast<int>(s21::Field::height);
  int width = static_cast<int>(s21::Field::width);
  int counter = 0;

  for (int i = 0; i < height - 1; i++) {
    for (int j = 1; j < width - 1; j++) {
      if (gameInfo.field[i][j] >= FigureSym) counter++;
    }
  }

  // Assert
  EXPECT_EQ(model->getState(), State::Win);
  EXPECT_TRUE(counter >= 199);
}

void printField(int **field) {
  int height = static_cast<int>(s21::Field::height);
  int width = static_cast<int>(s21::Field::width);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (field[i][j] > 33)
        std::cout << "* "
                  << " ";
      else
        std::cout << field[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void moveHead(s21::Point &head, UserAction_t action) {
  switch (action) {
    case UserAction_t::Right:
      head.x += 1;
      break;
    case UserAction_t::Down:
      head.y += 1;
      break;
    case UserAction_t::Left:
      head.x -= 1;
      break;
    case UserAction_t::Up:
      head.y -= 1;
      break;
    default:
      break;
  }
}

void fieldByPass(s21::SnakeModel *model, int count) {
  model->setKey(Keys::ENTER);
  model->userInput(UserAction_t::Start, false);

  model->setKey(Keys::ArrowLeft);
  model->userInput(UserAction_t::Up, false);
  model->userInput(UserAction_t::Left, false);

  for (int i = 0; i < 3; i++) model->userInput(UserAction_t::Start, false);

  model->userInput(UserAction_t::Up, false);

  for (int i = 0; i < 5; i++) model->userInput(UserAction_t::Start, false);

  GameInfo_t gameInfo = model->updateCurrentState();
  int height = gameInfo.field[0][0];
  int width = gameInfo.field[1][0];

  for (int i = 0; i < count; i++) {
    UserAction_t action = UserAction_t::Right;

    s21::Point head{0, 1};

    for (int i = 0, n = 4; i < height - 1; i++) {
      if (i != 0 && (head.x == 10 || head.x == 2)) {
        model->setKey(Keys::ArrowDown);
        model->userInput(UserAction_t::Down, false);
        moveHead(head, UserAction_t::Down);
      }

      if (head.x == 1 || head.x == 2 || head.x == 10) {
        model->setKey(action == UserAction_t::Right ? Keys::ArrowRight
                                                    : Keys::ArrowLeft);
        model->userInput(action, false);
        moveHead(head, action);
      }

      for (int j = 0; j < width - n; j++) {
        if (model->getState() == State::Win) {
          height = 0;
          count = 0;
          break;
        }

        model->setKey(-1);
        model->userInput(Start, false);
        moveHead(head, action);
      }

      action = (action == UserAction_t::Right) ? UserAction_t::Left
                                               : UserAction_t::Right;
      n = 5;
    }

    model->userInput(UserAction_t::Start, false);
    model->userInput(UserAction_t::Up, false);

    for (int i = 0; i < 18 && height; i++)
      model->userInput(UserAction_t::Start, false);
  }
}

/*
   /*\-> -> -> -> -> -> |
    * |  <- <- <- <- <- V
    * V -> -> -> -> ->->|
    * ..................V
      ...................
      ...................
    A ...................
    | ...................
    A ...................
    | <- ....... <- <- <-
*/