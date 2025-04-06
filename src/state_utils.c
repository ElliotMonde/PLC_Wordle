#ifndef STATE_UTILS_C
#define STATE_UTILS_C
#include "../include/main.h"
#include "../include/state_utils.h"
#include "../include/file_utils.h"
#include "../include/gui.h" 
#include <string.h>
#include <stdbool.h>

#define MAX_TURNS 6

void change_state(Game *game, int state)
{
    game->state = state;

    switch (state)
    {
    case START:
        print_welcome();  // <--- Terminal banner
        break;

    case NEW_GAME:
        start_new_game(game);  // <--- This already sets state = TURN
        break;

    case TURN:
    {
        char *guess = malloc(sizeof(char) * (game->chosen_word->len + 2));
        int *result;
        bool is_correct;

        while (game->turn <= MAX_TURNS)
        {
            printf("\nAttempt %d of %d\n", game->turn, MAX_TURNS);
            printf("Enter your guess: ");

            fgets(guess, game->chosen_word->len + 2, stdin);
            guess[strcspn(guess, "\n")] = 0;

            if ((int)strlen(guess) != game->chosen_word->len)
            {
                printf("Please enter a %d-letter word.\n", game->chosen_word->len);
                continue;
            }

            result = check_guess(guess, game->chosen_word->val, game->chosen_word->len);
            print_guess_feedback(guess, result, game->chosen_word->len);  // <--- use GUI

            is_correct = true;
            for (int i = 0; i < game->chosen_word->len; i++)
            {
                if (result[i] != 2)
                {
                    is_correct = false;
                    break;
                }
            }

            free(result);

            if (is_correct)
            {
                change_state(game, WIN);
                break;
            }

            game->turn++;
        }

        if (!is_correct)
        {
            change_state(game, LOSE);
        }

        free(guess);
        break;
    }

    case WIN:
        print_win_message();  // <--- use GUI
        break;

    case LOSE:
        print_game_over(game->chosen_word->val);  // <--- use GUI
        break;

    case SAVE:
        break;

    case LOAD:
        break;
    }
}

void start_new_game(Game *game)
{
    char *buffer;
    char **string_arr;
    while (1)
    {
        while (1)
        {
            puts("Input relative-path of text file to load words from:\n");
            buffer = get_filepath();
            if (buffer != NULL)
            {
                buffer[strcspn(buffer, "\n")] = 0;
                if (isFileValid(buffer)){
                    break;
                }
            }
        }
        string_arr = file_to_string_array(buffer, 1000);
        free(buffer);
        remove_banned_words(&string_arr);

        if (array_len(string_arr) > 0)
        {
            game->chosen_word = (Chosen_Word *)malloc(sizeof(Chosen_Word));
            game->chosen_word->val = strdup(get_random_word(string_arr));
            game->chosen_word->len = dynamic_string_len(game->chosen_word->val);
            free_string_array(string_arr, array_len(string_arr));
            game->turn = 1;
            game->state = TURN;
            return; /** has valid word, choose random valid word, return */
        }
    }
}

#endif
/** EOF **/
