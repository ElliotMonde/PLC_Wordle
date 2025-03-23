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

void change_state(Game *game, int new_state);
void start_new_game(Game* game);
void game_start_loop(char* buffer, int j, int max_filepath_length);
#endif
/** EOF **/
