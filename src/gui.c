#include "../include/gui.h"

#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RED "\033[1;31m"
#define BLUE "\033[0;34m"
#define GREY "\033[0;37m"
#define CLEAR_SCREEN "\033[1;1H\033[2J"

void print_welcome(void)
{
    puts(CLEAR_SCREEN);
    puts("====================== WORDLE GAME ======================\n");
    puts("__.  ._.   __. ._____.._____. .____.  .__.    |--_|    ");
    puts("\\ \\  / \\  / /  | ._. | | - _| |  ._ \\  | |    | --|");
    puts(" \\ \\/ _ \\/ /   | |_| | |   \\. | |_|  | | |__. | --| ");
    puts("  \\_./ \\_./    |_____| |_|\\_| | ____/  |_____||___|\n");

    puts("=========================================================\n");
}

void print_guess_feedback(char *guess, Chosen_Word *chosen_word)
{
    int i;
    int *result = check_guess(guess, chosen_word->val, chosen_word->len);
    for (i = 0; i < chosen_word->len; i++)
    {
        switch (result[i])
        {
        case 1:
            printf(GREEN "%c " RESET, guess[i]);
            break;
        case 2:
            printf(YELLOW "%c " RESET, guess[i]);
            break;
        default:
            printf(GREY "%c " RESET, guess[i]);
            break;
        }
    }
    printf("\n");
    for (i = 0; i < chosen_word->len; i++)
    {
        printf(result[i] == 1 ? "- " : "  ");
    }
    puts("\n");
    free(result);
}

void print_game_over(void)
{
    puts(RED "##       ####     ######    ######     ##" RESET);
    puts(RED "##     ##    ##  ##        ##          ##" RESET);
    puts(RED "##     ##    ##  ######   ######       ##" RESET);
    puts(RED "##     ##    ##     ###    ##            " RESET);
    puts(RED "######   ####   ######      ######     ##" RESET);
}

void print_win_message(void)
{

    puts(GREEN "                                       #" RESET);
    puts(GREEN "##    ##     ##  ##  ###    ##        ###" RESET);
    puts(GREEN " ##   ###   ##   ##  ## ##  ##    ###########" RESET);
    puts(GREEN "  ## ## ## ##    ##  ##  ## ##      ######" RESET);
    puts(GREEN "   ##     ##     ##  ##   ####      ### ###" RESET);
    puts(GREEN "                                   ##    ##" RESET);
}
/**  EOF **/
