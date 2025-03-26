#ifndef STATE_UTILS_C
#define STATE_UTILS_C
#include "../include/main.h"
#include "../include/state_utils.h"
#include "../include/file_utils.h"

void call_state(Game *game, int state)
{
    switch (state)
    {
    case START:
        /** prompt user to start new game or load save, reject other inputs */
        break;
    case NEW_GAME:
        /** prompt user for file input, reject other inputs */
        break;
    case LOAD:
        /** prompt user for save file, reject other inputs */
        break;
    case WIN:
        /** display game stats, save game, back to start on user press */
        break;
    case LOSE:
        /** display game stats, save game, back to start on user press */
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

Game* start_new_game(void)
{
    char *buffer;
    char **string_arr;
    int num_guesses;
    Game *game = (Game *)malloc(sizeof(Game));

    while (1)
    {
        while (1)
        {
            puts("Input relative-path of text file to load words from:\n");
            buffer = get_filepath();
            if (buffer != NULL)
            {
                buffer[strcspn(buffer, "\n")] = 0;
                if (isFileValid(buffer))
                {
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
            num_guesses = game->chosen_word->len;
            game->guessed_words = (char **)malloc(sizeof(char *) * num_guesses);
            free_string_array(string_arr, array_len(string_arr));
            game->turn = 1;
            game->state = TURN;
            return game; /** has valid word, choose random valid word, return */
        }else{
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
    char *guess = (char *)malloc(sizeof(char) * game->chosen_word->len + 1);
    game->turn += 1;
    while (1){
        display_guesses(game->guessed_words);

        puts("Input next guess:\n");
        if (fgets(guess, game->chosen_word->len + 1, stdin) != NULL && is_new_guess(guess, game->guessed_words)){
            game->guessed_words[game->turn - 1] = guess;
            break;
        };
    }
    result = check_guess(guess, game->chosen_word->val, game->chosen_word->len);

    if (isWin(result, game->chosen_word->len)){
        game->state = WIN;
    }else if (game->turn == game->chosen_word->len){
        game->state = LOSE;
    }
    /** else still state = turn */
}

/**
 * @brief checks if the current guess is fully-correct, if so, returns true, else false.
 * 
 * @param result 
 * @param len 
 * @return int 
 */
int isWin(int *result, int len){
    int i = 0;
    while (i < len)
    {
        if (result[i] != 1){
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
void free_game(Game* game){
    int i = 0;
    free(game->chosen_word->val);
    free(game->chosen_word);
    for (i = 0; i < game->turn; i++){
        free(game->guessed_words[i]);
    }
    free(game);
}

void display_guesses(char **guessed_words){
    /** display the previously guessed words and show the correct or partial correctness at each slot, use check_guess */
}

/**
 * @brief checks if current guessed word has been attempted before.
 * 
 * @param guess 
 * @param guessed_words 
 * @return int 
 */
int is_new_guess(char *guess, char **guessed_words){
    int i, arr_len = array_len(guessed_words);
    for (i = 0; i < arr_len; i++){
        if (!strcmp(guess, guessed_words[i])){
            return 0;
        }
    }
    return 1;
}

#endif
/** EOF **/
