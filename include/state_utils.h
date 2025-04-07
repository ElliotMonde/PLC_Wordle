#ifndef STATE_UTILS_H
#define STATE_UTILS_H
#include "string_utils.h"

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

typedef struct
{
    int state;
    int turn;
    char *filepath; /* save-file path for loading?*/
    Chosen_Word *chosen_word;
    char **guessed_words;
} Game;

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
