#ifndef STATE_UTILS_H
#define STATE_UTILS_H
#include "game_struct.h"

enum State
{
    START,
    NEW_GAME,
    LOAD,
    WIN,
    LOSE,
    TURN,
    SAVE
};

void call_state(Game *game);
Game* new_game(void);
Game *start_game(void);
Game *load_game(void);
void turn(Game *game);
int isWin(int *result, int len);
int is_new_guess(char *guess, char **guessed_words, int turns);
void display_guesses(char **guessed_words);
void display_win(Game *game);
void display_lose(Game *game);
void display_start_screen(void);
void free_game(Game *game);
#endif
/** EOF **/
