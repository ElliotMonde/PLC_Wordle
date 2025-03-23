#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"
#include "state_utils.c"

int main(int argc, char **argv)
{
    Game *game;
    char *guess;
    int *result;
    int i;
    game = (Game *)malloc(sizeof(Game));

    start_new_game(game);
    printf("\nChosen random word: %s\n", game->chosen_word->val);
    guess = (char *)malloc(sizeof(char) * game->chosen_word->len + 1);
    fgets(guess, game->chosen_word->len + 1, stdin);
    result = check_guess(guess, game->chosen_word->val, game->chosen_word->len);
    printf("%s\n", guess);
    for (i = 0; i < game->chosen_word->len; i++)
    {
        printf("%d,", result[i]);
    }
    puts("\n");

    /** free malloc */
    free(guess);
    free(result);
    free(game->chosen_word->val);
    free(game->chosen_word);
    free(game);

    return 0;
}

/**  EOF **/
