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
    PlayerStats stats;
    loadStats(&stats);

    printf("Welcome to Wordle!\n"); 
    print_welcome(); 
    printStats(&stats);

    // Simulate a game result
    int won;
    printf("Did you win the game? (1=yes, 0=no): ");
    scanf("%d", &won);

    updateStats(&stats, won);

    saveStats(&stats);
    printf("Stats saved. See you next time!\n");

    Game *game;
    char *guess;
    int *result;
    int i;
    game = (Game *)malloc(sizeof(Game));

    start_new_game(game);
    // printf("\nChosen random word: %s\n", game->chosen_word->val);
    // guess = (char *)malloc(sizeof(char) * game->chosen_word->len + 1);
    // fgets(guess, game->chosen_word->len + 1, stdin);
    // result = check_guess(guess, game->chosen_word->val, game->chosen_word->len);
    // printf("%s\n", guess);
    // for (i = 0; i < game->chosen_word->len; i++)
    // {
    //     printf("%d,", result[i]);
    // }
    // puts("\n");

    printf("\nChosen random word: %s\n", game->chosen_word->val); // Dev note: remove in production

    guess = (char *)malloc(sizeof(char) * (game->chosen_word->len + 2)); // +1 newline, +1 null
    bool guessed_correctly = false;

    for (game->turn = 1; game->turn <= MAX_TURNS; game->turn++) {
        printf("\nAttempt %d of %d\n", game->turn, MAX_TURNS);
        printf("Enter your guess: ");

        fgets(guess, game->chosen_word->len + 2, stdin);
        guess[strcspn(guess, "\n")] = 0;

        if ((int)strlen(guess) != game->chosen_word->len) {
            printf("Please enter a %d-letter word.\n", game->chosen_word->len);
            game->turn--;
            continue;
        }

        result = check_guess(guess, game->chosen_word->val, game->chosen_word->len);
        print_guess_feedback(guess, result, game->chosen_word->len);

        guessed_correctly = true;
        for (i = 0; i < game->chosen_word->len; i++) {
            if (result[i] != 2) {
                guessed_correctly = false;
                break;
            }
        }

        free(result);

        if (guessed_correctly) {
            print_win_message();
            break;
        }
    }

    if (!guessed_correctly) {
        print_game_over(game->chosen_word->val);
    }

    /** free malloc */
    free(guess);
    free(result);
    free(game->chosen_word->val);
    free(game->chosen_word);
    free(game);

    return 0;
}

/**  EOF **/
