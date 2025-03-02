#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "../include/file_utils.h"

#define MAX_WORDS 1000
#define BUFFER_SIZE 1024

char **file_to_string_array(char *filename, int array_size)
{
    int j, i = 0;
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
                perror("Memory allocation failed");
                for (j = 0; j < i; j++)
                {
                    free(string_array[j]);
                }
                free(string_array);
                fclose(f);
                return NULL;
            }
            strcpy(string_array[i], token);
            i++;
            token = strtok(NULL, delimiters);
        }
    }

    string_array[i] = NULL;
    fclose(f);
    return string_array;
}
