#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"
#include "state_utils.c"
#include "../include/gui.h"
#include <string.h>   // for strcspn
#include <stdbool.h>  // for bool, true, false

#define MAX_TURNS 6

int main(int argc, char **argv)
{
    Stats *stats = (Stats *)malloc(sizeof(Stats));
    Game *game = start_game(stats);
    while (game->state == TURN)
    {
        call_state(game, stats);
    }
    call_state(game, stats);

    if (!guessed_correctly) {
        print_game_over(game->chosen_word->val);
    }

    /** free malloc */
    free_game(game, stats);

    return 0;
}

/**  EOF **/
