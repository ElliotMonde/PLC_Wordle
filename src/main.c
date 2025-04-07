#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"
#include "state_utils.c"

int main(int argc, char **argv)
{
    Stats *stats = (Stats *)malloc(sizeof(Stats));
    Game *game = start_game(stats);
    while (game->state == TURN)
    {
        call_state(game, stats);
    }
    call_state(game, stats);

    /** free malloc */
    free_game(game, stats);

    return 0;
}

/**  EOF **/
