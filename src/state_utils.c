#ifndef STATE_UTILS_C
#define STATE_UTILS_C
#include "../include/main.h"
#include "../include/state_utils.h"
#include "../include/file_utils.h"

void change_state(Game *game, int state)
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
        break;
    case SAVE:
        /** save game, then return to previous/next state */
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
