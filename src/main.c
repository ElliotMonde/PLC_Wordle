#include <stdio.h>
#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"

int main(int argc, char **argv)
{
    int array_size = 10;
    char *filename = "../test_inp.txt";
    char **string_array = file_to_string_array(filename, array_size);
    int i;
    
    printf("1 means word is valid, 0 means word is invalid.\n");
    for (i = 0; i < array_size; i++)
    {
        if (!string_array[i])
        {
            break;
        }
        printf("%s : %d\n", string_array[i], is_banned_word(string_array[i]));
    }

    free_string_array(string_array, array_size);
    return 0;
}

/**  EOF **/
