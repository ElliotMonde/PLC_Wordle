#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"

int main(int argc, char **argv)
{
    /** just a demo of the current utility functions: feel free to remove */
    
    int hashcode, array_size = 11;
    int i;

    char filename[100];
    char **string_array = file_to_string_array(requestFile(filename), array_size);

    /* char *filename = "../test_inp.txt";
    char **string_array = file_to_string_array(filename, array_size); */
    
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
    printf("length: %d\n", array_len(string_array));
    while (string_array[i])
    {
        to_lower(string_array[i]);
        hashcode = hash_f(string_array[i]);
        printf("%s : %d\n", string_array[i], hashcode);
        i++;
    }
    free_string_array(string_array, array_len(string_array));
    return 0;
}

/**
 * @brief 
 * Function to request a valid file from the user. will return the filename param if valid
 * 
 * @param filename const char*
 * @return char* 
 */
char* requestFile(char *filename) {
    int isValid = 0;

    /* Keep prompting the user until a valid file is provided */
    while (!isValid) {
        printf("Enter the file name (path to file) for the wordle game: ");
        scanf("%s", filename);

        if (isFileValid(filename)) {
            isValid = 1; /* Set the flag to exit the loop */
            printf("Valid file.\n");
            /* additional: prompt player to load save */
        } else {
            printf("Invalid file. Please provide a valid file.\n");
        }
    }

    return filename;
}

/**  EOF **/
