#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"
#include "state_utils.c"
#include "save.c"

int main(int argc, char **argv)
{
    gameStats Stats;
    Game *game = start_new_game();
    while (game->state == TURN){
        call_state(game);
    }
    call_state(game);

    /** free malloc */
    free_game(game);

    return 0;
}

/**  EOF **/
