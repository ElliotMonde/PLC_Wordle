#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include "string_utils.h"
typedef struct
{
    int wins;
    int losses;
    int streak;
    char *filepath; /* save-file path for loading?*/
} Stats;
typedef struct
{
    int state;
    int turn;
    Chosen_Word *chosen_word;
    char **guessed_words;
} Game;

#endif
/** EOF **/
