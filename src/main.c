#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"

int main(int argc, char **argv)
{
    /** just a demo of the current utility functions: feel free to remove */
    int hashcode, array_size = 11;
    char *chosen_word;
    char *guess = (char*) malloc(sizeof(char) * 10);
    int *result;
    char *filename = "../test_inp.txt";
    char **string_array = file_to_string_array(filename, array_size);
    int i;
    puts("0 means word is valid, 1 means word is invalid.\n");
    for (i = 0; i < array_size; i++)
    {
        if (!string_array[i])
        {
            break;
        }
        printf("%s : %d\n", string_array[i], is_banned_word(string_array[i]));
    }

    remove_banned_words(&string_array);
    puts("\nAfter removing banned words: together with hashcode of words\n");
    i = 0;
    while (string_array[i])
    {
        to_lower(string_array[i]);
        hashcode = hash_f(string_array[i]);
        printf("%s : %d\n", string_array[i], hashcode);
        i++;
    }
    chosen_word = strdup(get_random_word(string_array)); /* careful: if chosen_word isn't copied from string_array, then don't free it as they reference the same address.*/
    printf("\nChosen random word: %s .\n", chosen_word);
    scanf("%s", guess);
    result = check_guess(guess, chosen_word, strlen(chosen_word));
    for (i = 0; i < strlen(chosen_word); i++){
        printf("%d,",result[i]);
    }
    puts("\n");
    free(result);
    free(chosen_word);
    free_string_array(string_array, array_len(string_array));
    return 0;
}

/**  EOF **/
