#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EMPTY ' '

#define W_PAWN 'p'
#define W_KNIGHT 'h'
#define W_BISHOP 'b'
#define W_ROOKE 'r'
#define W_QUEEN 'q'
#define W_KING 'k'

#define B_PAWN 'P'
#define B_KNIGHT 'H'
#define B_BISHOP 'B'
#define B_ROOKE 'R'
#define B_QUEEN 'Q'
#define B_KING 'K'

#define BOARD_STRING_LENGTH 1000

void get_start_board(char board[8][8]) {
  char start_board[8][8] = {
    {B_ROOKE, B_KNIGHT, B_BISHOP, B_QUEEN,  B_KING, B_BISHOP, B_KNIGHT, B_ROOKE},
    {B_PAWN,  B_PAWN,   B_PAWN,   B_PAWN,   B_PAWN, B_PAWN,   B_PAWN,   B_PAWN},
    {EMPTY,   EMPTY,    EMPTY,    EMPTY,    EMPTY,  EMPTY,    EMPTY,    EMPTY},
    {EMPTY,   EMPTY,    EMPTY,    EMPTY,    EMPTY,  EMPTY,    EMPTY,    EMPTY},
    {EMPTY,   EMPTY,    EMPTY,    EMPTY,    EMPTY,  EMPTY,    EMPTY,    EMPTY},
    {EMPTY,   EMPTY,    EMPTY,    EMPTY,    EMPTY,  EMPTY,    EMPTY,    EMPTY},
    {W_PAWN,  W_PAWN,   W_PAWN,   W_PAWN,   W_PAWN, W_PAWN,   W_PAWN,   W_PAWN},
    {W_ROOKE, W_KNIGHT, W_BISHOP, W_QUEEN,  W_KING, W_BISHOP, W_KNIGHT, W_ROOKE}
  };

  // Copy elements of start_board into board
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = start_board[i][j];
    }
  }
}

char* get_board_text(char board[8][8]) {
  static char board_display[BOARD_STRING_LENGTH];
  int index = 0;

  for (int k = 0; k < 33; k++) {
    board_display[index++] = '-';
  }
  board_display[index++] = '\n';

  for (int i = 0; i < 8; i++) {
    board_display[index++] = '|';
    board_display[index++] = ' ';
    for (int j = 0; j < 8; j++) {
      board_display[index++] = board[i][j];
      board_display[index++] = ' ';
      board_display[index++] = '|';
      board_display[index++] = ' ';
    }
    board_display[index++] = '\n';
    for (int k = 0; k < 33; k++) {
      board_display[index++] = '-';
    }
    board_display[index++] = '\n';
  }
  board_display[index] = '\0';
  return board_display;
}