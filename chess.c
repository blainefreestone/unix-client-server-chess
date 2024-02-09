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

#define BOARD_STRING_LENGTH 2000

void set_board_start(char board[8][8]) {
  char start_board[8][8] = {
  // board is 2d array of characters representing each type of piece.
    {W_ROOKE, W_KNIGHT, W_BISHOP, W_QUEEN,  W_KING, W_BISHOP, W_KNIGHT, W_ROOKE},
    {W_PAWN,  W_PAWN,   W_PAWN,   W_PAWN,   W_PAWN, W_PAWN,   W_PAWN,   W_PAWN},
    {EMPTY,   EMPTY,    EMPTY,    EMPTY,    EMPTY,  EMPTY,    EMPTY,    EMPTY},
    {EMPTY,   EMPTY,    EMPTY,    EMPTY,    EMPTY,  EMPTY,    EMPTY,    EMPTY},
    {EMPTY,   EMPTY,    EMPTY,    EMPTY,    EMPTY,  EMPTY,    EMPTY,    EMPTY},
    {EMPTY,   EMPTY,    EMPTY,    EMPTY,    EMPTY,  EMPTY,    EMPTY,    EMPTY},
    {B_PAWN,  B_PAWN,   B_PAWN,   B_PAWN,   B_PAWN, B_PAWN,   B_PAWN,   B_PAWN},
    {B_ROOKE, B_KNIGHT, B_BISHOP, B_QUEEN,  B_KING, B_BISHOP, B_KNIGHT, B_ROOKE}
  };

  // Copy elements of start_board into board
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = start_board[i][j];
    }
  }
}

int is_player_piece(char piece_char, int player_num) {
  char player_pieces[6];
  
  // define which pieces belong to the player based on player_num
  if (player_num == 1) {
    char player_pieces[6] = {'p', 'h', 'b', 'r', 'q', 'k'};
  }
  else if (player_num == 2) {
    char player_pieces[6] = {'P', 'H', 'B', 'R', 'Q', 'K'};
  }
  // error condition
  else {
    return -1;
  }

  for (int i = 0; i < 6; i++) {
    // returns true (1) if piece_char is found in the player_pieces array
    if (player_pieces[i] == piece_char) {
      return 1;
    }
  }

  // returns false if the char is not found in the array
  return 0;
}

int is_valid_move(char board[8][8], int source_char, int source_int, int destination_char, int destination_int) {
  char piece_char = board[source_int-1][source_char-1];

  return 1;
}

int make_move(char board[8][8], char *command, int player_num) {
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

  // update board array with moved piece

  char piece_char = board[source_int-1][source_char-1];       // get piece char from source location

  // not player's piece invalid condition
  if (is_player_piece(piece_char, player_num) == 0) {
    return -1;
  }

  board[source_int-1][source_char-1] = EMPTY;                 // set piece char to empty at source location
  board[destination_int-1][destination_char-1] = piece_char;  // set destination location to piece char from source
}

char* get_board_text(char board[8][8]) {
  static char board_display[BOARD_STRING_LENGTH];
  int index = 0;
  char letters[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

  board_display[index++] = ' ';
  board_display[index++] = ' ';
  for (int k = 0; k < 33; k++) {
    board_display[index++] = '-';
  }
  board_display[index++] = '\n';

  for (int i = 7; i >= 0; i--) {
    board_display[index++] = (char)i + '0' + 1;
    board_display[index++] = ' ';
    board_display[index++] = '|';
    board_display[index++] = ' ';
    for (int j = 0; j < 8; j++) {
      board_display[index++] = board[i][j];
      board_display[index++] = ' ';
      board_display[index++] = '|';
      board_display[index++] = ' ';
    }
    board_display[index++] = '\n';
    board_display[index++] = ' ';
    board_display[index++] = ' ';
    for (int k = 0; k < 33; k++) {
      board_display[index++] = '-';
    }
    board_display[index++] = '\n';
  }
  board_display[index++] = ' ';
  board_display[index++] = ' ';
  for (int i = 0; i < 8; i++) {
    board_display[index++] = ' ';
    board_display[index++] = ' ';
    board_display[index++] = letters[i];
    board_display[index++] = ' ';
  }
  board_display[index++] = '\n';
  board_display[index] = '\0';
  return board_display;
}