#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"
#include "state_utils.c"
#include "../include/gui.h"

void run_game(void){
    Stats *stats = (Stats *)malloc(sizeof(Stats));
    Game *game;
    char input;
    
    while (1) {
        game = start_screen(stats);
        call_state(game, stats);
        
        /* free malloc for game*/
        free_game(game);

        /* Ask if user wants to play again */
        puts(BLUE"\nWould you like to play again?\n[y] - Play Again\n[n] - Quit Program"RESET);
        input = fgetc(stdin);
        fseek(stdin, 0, SEEK_END);
        if (!(input == 'y' || input == 'Y')){
            break;
        }
    }

    /* free stats */
    free_stats(stats);
}

int main(int argc, char **argv)
{
    run_game();
    return 0;
}

/**  EOF **/
