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

void run_game(){
    Stats *stats = (Stats *)malloc(sizeof(Stats));
    Game *game = NULL;
    int play_again = 1;
    char input;
    
    while (play_again) {
        game = start_game(stats);

        while (game->state == TURN)
        {
            call_state(game, stats);
        }
        call_state(game, stats);

        /* Ask if user wants to play again */
        printf("\nWould you like to play again? (y/n): ");
        scanf(" %c", &input);
        /* Clear extra characters in the input buffer from scanf */
        while (getchar() != '\n');

        play_again = (input == 'y' || input == 'Y');
    }

    /* free malloc */
    free_game(game, stats);
}

int main(int argc, char **argv)
{
    run_game();
    return 0;
}


/**  EOF **/
