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

void set_board_start(char board[8][8]) {
  char start_board[8][8] = {
  // board is 2d array of characters representing each type of piece.
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

int make_move(char board[8][8], char *command) {
  // decode command string
  int is_capture = 0;
  int destination_char_index = 2;
  int destination_int_index = 3;

  // source location
  int source_char = command[0] - 'a' + 1; // convert char a-h to int 1-8
  int source_int = command[1] - '0';
  
  // invalid source location condition
  if (source_char > 8 || source_int > 8 || source_char < 1 || source_int < 1) {
    return -1;
  }

  // if command is --x-- it is a capture
  if (command[2] == 'x') {
    is_capture = 1;
    // update indexes for destination chars
    destination_char_index = 3;
    destination_int_index = 4;
  }

  // destination location
  int destination_char = command[destination_char_index] - 'a' + 1; // convert char a-h to int 1-8
  int destination_int = command[destination_int_index] - '0';

  // invalid destination location condition
  if (destination_char > 8 || destination_int > 8 || destination_char < 1 || destination_int < 1) {
    return -1;
  }

  printf("%d %d %d %d", source_char, source_int, destination_char, destination_int);
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