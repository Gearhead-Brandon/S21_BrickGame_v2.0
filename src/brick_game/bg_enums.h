/*!
    @file
    @brief Tetris defines
*/
#ifndef DEFINES_H
#define DEFINES_H

/// Game borders
typedef enum {

  FieldRows = 23,   ///< Rows of the field
  FieldCols = 12,   ///< Columns of the field
  LeftBorder = 1,   ///< Left border
  RightBorder = 11  ///< Right border

} Borders;

/// Figure symbol
typedef enum {

  FigureSym = '*'  ///< Figure symbol

} FigureSymbol;

/// Keys
typedef enum {

  ArrowUp = 0403,     ///< Up key
  ArrowDown = 0402,   ///< Down key
  ArrowLeft = 0404,   ///< Left key
  ArrowRight = 0405,  ///< Right key
  ENTER = '\n',       ///< Enter key
  QUIT = 'q',         ///< Quit key
  PAUSE = 'p',        ///< Pause key
  ACTION = ' ',       ///< Rotation key

} Keys;

/// State of the game
typedef enum {

  Launch,     ///< Game launch state
  Spawn,      ///< Spawning a new figure
  Moving,     ///< Moving a figure
  Shifting,   ///< Shifting a figure
  Attaching,  ///< Connecting a figure to another
  GameOver,   ///< Game over
  Win         ///< Game win

} State;

/// Unicode symbols
typedef enum {

  ArrowDown_Uni = L'\U0001F817',         ///< ⬇️
  ArrowRight_Uni = L'\U0001F816',        ///< ➡️
  ArrowLeft_Uni = L'\U0001F814',         ///< ⬅️
  Pause_Uni = L'\u23F8',                 ///< ⏸️
  Fire_Uni = L'\U0001F525',              ///< 🔥
  OutputFigureBlock_Uni = L'\U0001F793'  ///< 🞓

} UnicodeSymbols;

/// Figure colors
typedef enum {

  Red = 1,
  Yellow,
  Green,
  Blue,
  Magenta,
  Cyan,
  White

} Colors;

#endif