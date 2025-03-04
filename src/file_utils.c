#ifndef FILE_UTILS_C
#define FILE_UTILS_C

#include "../include/main.h"
#include "../include/file_utils.h"

#define MAX_WORDS 1000
#define BUFFER_SIZE 1024

/**
 * @brief 
 * This function reads from a file <array_size> number of words, and returns a string array (char**) of length <array_size> with first <array_size> words as elements.
 * 
 * Pre-condition: array_size <= 1000, memory allocated to string_array and the string pointers in the array has to be freed.
 * 
 * @param filename char* 
 * @param array_size int
 * @return char** 
 */
char **file_to_string_array(char *filename, int array_size)
{
    int i = 0;
    char buffer[BUFFER_SIZE];
    char *token;
    char **string_array;
    char *delimiters = " ,.-_!?;:\n\t\"\'()";
    FILE *f = fopen(filename, "r");

    if (!f)
    {
        perror("file_utils: Error: could not open file.\n");
        return NULL;
    }

    if (array_size > MAX_WORDS)
    {
        array_size = MAX_WORDS;
    }

    if (!(string_array = (char **)malloc(sizeof(char *) * (array_size + 1))))
    { 
        perror("file_utils: Error: Memory allocation failed.");
        fclose(f);
        return NULL;
    }

    while (i < array_size && fgets(buffer, BUFFER_SIZE, f))
    {
        token = strtok(buffer, delimiters);
        while (token != NULL && i < array_size)
        {
            string_array[i] = (char *)malloc(strlen(token) + 1);
            if (!string_array[i])
            {
                perror("file_utils: Memory allocation failed");
                free_string_array(string_array, i);
                fclose(f);
                return NULL;
            }
            strcpy(string_array[i++], token);
            token = strtok(NULL, delimiters);
        }
    }

    string_array[i] = NULL;
    fclose(f);
    return string_array;
}

/**
 * @brief 
 * Frees the memory allocated to a string array with <len> number of string pointers.
 * 
 * @param string_array char**
 * @param len int
 */
void free_string_array(char **string_array, int len){
    int i;
    for (i = 0; i < len; i++){
        free(string_array[i]);
    }
    free(string_array);
}

#endif
/**  EOF **/
