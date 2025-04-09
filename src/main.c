#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"
#include "state_utils.c"
#include "../include/gui.h"

void run_game(void){
    Stats *stats = (Stats *)malloc(sizeof(Stats));
    Game *game;
    
    game = start_screen(stats);
    call_state(game, stats);

    /* free stats */
    free_stats(stats);
}

int main(int argc, char **argv)
{
    run_game();
    return 0;
}


/**  EOF **/
