#ifndef STATE_UTILS_C
#define STATE_UTILS_C
#include "../include/main.h"
#include "../include/state_utils.h"
#include "../include/file_utils.h"
#include "save.c"

#define MAX_NUM_WORDS 1000

void call_state(Game *game)
{
    switch (game->state)
    {
    case WIN:
        /** display game stats, save game, back to start on user press */
        display_win(game);
        break;
    case LOSE:
        /** display game stats, save game, back to start on user press */
        display_lose(game);
        break;
    case TURN:
        /** prompt user for guess, and checks guess */
        turn(game);
        break;
    case SAVE:
        /** save game, then return to previous/next state */
        break;
    }
}

Game *start_game(void)
{
    return get_user_input() ? new_game() : load_game();
}

Game *load_game(void)
{
    Game *game;
    char *load_file_path;
    char *valid_bin_file_extensions[] = {"bin", "\0"};
    while (1)
    {
        load_file_path = load_file(valid_bin_file_extensions, ".bin");
        game = load_from_save_file(load_file_path);
        if (game != NULL)
        {
            break;
        }
        puts("Unable to load save from file, please try again or restart program.\n");
    }
    return game;
}

Game *new_game(void)
{
    char *valid_txt_file_extensions[] = {".pdf", ".txt", ".doc", ".bin", ".dat", "\0"};
    char **string_arr;
    int num_guesses;
    Game *game = (Game *)malloc(sizeof(Game));
    /**
     * TODO
     * Create new save file, prompt for relative filepath without extension, if wishes to autosave else continue
     */
    while (1)
    {
        string_arr = file_to_string_array(load_file(valid_txt_file_extensions, "text"), MAX_NUM_WORDS);
        remove_banned_words(&string_arr);

        if (array_len(string_arr) > 0)
        {
            game->chosen_word = (Chosen_Word *)malloc(sizeof(Chosen_Word));
            game->chosen_word->val = strdup(get_random_word(string_arr));
            game->chosen_word->len = dynamic_string_len(game->chosen_word->val);
            num_guesses = game->chosen_word->len;
            game->guessed_words = (char **)malloc(sizeof(char *) * num_guesses);
            free_string_array(string_arr, array_len(string_arr));
            game->turn = 0;
            game->state = TURN;
            printf("(for testing only) chosen word: %s\n", game->chosen_word->val);
            return game; /** has valid word, choose random valid word, return */
        }
        else
        {
            puts("No valid word found from input document.\n");
        }
    }
}

/**
 * @brief To be called while state == TURN, and number of turns < length of chosen word. Prompts for guess and checks correctness before deciding if WIN, LOSE, or continute to next TURN.
 *
 * @param game
 */
void turn(Game *game)
{ /** check turn number < chosen word len outside */
    int *result;
    char *guess = (char *)malloc(sizeof(char) * (game->chosen_word->len + 1));
    game->turn += 1;

    display_guesses(game->guessed_words);
    printf("\n~~~ Turn %d ~~~\n", game->turn);

    puts("Input next guess:\n");
    if (fgets(guess, game->chosen_word->len + 1, stdin) != NULL)
    {
        if (is_new_guess(guess, game->guessed_words, game->turn))
        {
            game->guessed_words[game->turn - 1] = guess;
        }
        fseek(stdin, 0, SEEK_END);
    };
    result = check_guess(guess, game->chosen_word->val, game->chosen_word->len);

    if (isWin(result, game->chosen_word->len))
    {
        game->state = WIN;
    }
    else if (game->turn >= game->chosen_word->len)
    {
        game->state = LOSE;
    }

    /** don't free(guess). the game->guessed_words[i] references it */
    free(result);
    /** else still state = turn */
}

/**
 * @brief checks if the current guess is fully-correct, if so, returns true, else false.
 *
 * @param result
 * @param len
 * @return int
 */
int isWin(int *result, int len)
{
    int i = 0;
    while (i < len)
    {
        if (result[i++] != 1)
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief free all allocated memory to attributes in game, and game itself.
 *
 * @param game
 */
void free_game(Game *game)
{
    int i = 0;
    free(game->filepath);
    free(game->chosen_word->val);
    free(game->chosen_word);
    for (i = 0; i < game->turn; i++)
    {
        free(game->guessed_words[i]);
    }
    free(game->guessed_words);
    free(game);
}

void display_guesses(char **guessed_words)
{
    /** display the previously guessed words and show the correct or partial correctness at each slot, use check_guess */
}

/**
 * @brief checks if current guessed word has been attempted before.
 *
 * @param guess
 * @param guessed_words
 * @return int
 */
int is_new_guess(char *guess, char **guessed_words, int turns)
{
    int i, arr_len = array_len(guessed_words);
    for (i = 0; i < arr_len; i++)
    {
        if (!strcmp(guess, guessed_words[i]))
        {
            return 0;
        }
    }
    return 1;
}

void display_win(Game *game)
{
    /** display win */

    /** placeholder text*/
    puts("Win game!\n");
    printf("Word to guess: %s\n", game->chosen_word->val);
    /** remove placeholder */
}
void display_lose(Game *game)
{
    /** display lose */

    /** placeholder text*/
    puts("Lose game!\n");
    printf("Word to guess: %s\n", game->chosen_word->val);
    /** remove placeholder */
}

void display_start_screen(void)
{
    /** allow user to choose between new game or resume game, and other relevant display text */
}

#endif
/** EOF **/
