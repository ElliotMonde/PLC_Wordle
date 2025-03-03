#include <stdio.h>
#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"

int main(int argc, char **argv)
{
    /** just a demo of the current utility functions: feel free to remove */
    int array_size = 10;
    char *filename = "../test_inp.txt";
    char **string_array = file_to_string_array(filename, array_size);
    int i;
    printf("0 means word is valid, 1 means word is invalid.\n");
    for (i = 0; i < array_size; i++)
    {
        if (!string_array[i])
        {
            break;
        }
        printf("%s : %d\n", string_array[i], is_banned_word(string_array[i]));
    }
    remove_banned_words(&string_array);

    printf("\nAfter removing banned words:\n");
    i = 0;
    printf("length: %d\n", array_len(string_array));
    while (string_array[i])
    {
        printf("%s\n", string_array[i]);
        i++;
    }
    free_string_array(string_array, array_len(string_array));
    return 0;
}

/**  EOF **/
