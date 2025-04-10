#ifndef STATE_UTILS_C
#define STATE_UTILS_C
#include "../include/main.h"
#include "../include/state_utils.h"
#include "../include/file_utils.h"
#include "gui.c"
#include "save.c"

#define MAX_NUM_WORDS 1000

void call_state(Game *game, Stats *stats)
{
    switch (game->state)
    {
    case WIN:
        /** display game stats, save game, back to start on user press */
        win(game, stats);
        break;

    case LOSE:
        /** display game stats, save game, back to start on user press */
        lose(game, stats);
        break;
    case TURN:
        /** prompt user for guess, and checks guess */
        turn(game, stats);
        break;
    }
}

Game *start_game(Stats *stats)
{
    print_welcome();
    return get_user_input() ? new_game() : load_game(stats);
}

Game *load_game(Stats *stats)
{
    Game *game;
    char *load_file_path;
    char *valid_bin_file_extensions[] = {".bin", "\0"};
    while (1)
    {
        load_file_path = load_file(valid_bin_file_extensions, ".bin");
        game = load_from_save_file(load_file_path, stats);
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

    char *save_filepath;
    char **string_arr;
    Game *game = (Game *)malloc(sizeof(Game));

    save_filepath = new_save_file();
    game->filepath = save_filepath;

    while (1)
    {
        string_arr = file_to_string_array(load_file(valid_txt_file_extensions, "text"), MAX_NUM_WORDS);
        remove_banned_words(&string_arr);

        if (array_len(string_arr) > 0)
        {
            game->chosen_word = (Chosen_Word *)malloc(sizeof(Chosen_Word));
            game->chosen_word->val = strdup(get_random_word(string_arr));
            game->chosen_word->len = dynamic_string_len(game->chosen_word->val);
            game->guessed_words = (char **)malloc(sizeof(char *) * game->chosen_word->len);
            free_string_array(string_arr, array_len(string_arr));
            game->turn = 0;
            game->state = TURN;
            /*printf("(for testing only) chosen word: %s\n", game->chosen_word->val);*/
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
void turn(Game *game, Stats *stats)
{ /** check turn number < chosen word len outside */
    int *result;
    char *guess = (char *)malloc(sizeof(char) * (game->chosen_word->len + 1));
    print_welcome();
    display_guesses(game);

    game->turn += 1;
    printf("\n~~~ Turn %d ~~~\n", game->turn);
    printf("\n%d-letter word...\n", game->chosen_word->len);
    printf("\nTurns Left: %d\n", game->chosen_word->len - game->turn);

    puts("Input next guess:");
    if (fgets(guess, game->chosen_word->len + 1, stdin) != NULL)
    {
        if (is_new_guess(guess, game->guessed_words, game->turn))
        {
            game->guessed_words[game->turn - 1] = guess;
        }
        fseek(stdin, 0, SEEK_END);
    };
    result = check_guess(guess, game->chosen_word->val, game->chosen_word->len);
    print_guess_feedback(guess, game->chosen_word);

    save_to_file(game, stats);
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

void win(Game *game, Stats *stats)
{
    stats->wins++;
    stats->streak++;

    save_to_file(game, stats);
    display_win(game);
}

void lose(Game *game, Stats *stats)
{
    stats->losses++;
    stats->streak = 0;

    save_to_file(game, stats);
    display_lose(game);
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
void free_game(Game *game, Stats *stats)
{
    int i = 0;
    free(stats);
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

/**
 * @brief display the previously guessed words and show the correct or partial correctness at each slot.
 *
 * @param game = Game*
 */
void display_guesses(Game *game)
{
    int i;
    for (i = 0; i < game->turn; i++)
    {
        print_guess_feedback(game->guessed_words[i], game->chosen_word);
    }
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
    print_win_message();
    printf("\n🎉 " GREEN "You guessed the word:" RESET " %s!" GREEN " Congratulations!" RESET "\n", game->chosen_word->val);
}
void display_lose(Game *game)
{
    print_game_over();
    printf("\n❌ " RED "Game Over! The word was: " RESET "%s\n", game->chosen_word->val);
}

#endif
/** EOF **/
