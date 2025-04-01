#ifndef FILE_UTILS_C
#define FILE_UTILS_C

#include "../include/main.h"
#include "../include/file_utils.h"
#include "../include/string_utils.h"

#define MAX_WORDS 1000
#define BUFFER_SIZE 1024

// Function to prompt for user input (Y/N)
int get_user_input(void) {
    char selected_input;
    printf("Would you like to load an existing save file? (Y/N) : ");
    
    if (scanf(" %c", &selected_input) != 1) {
        puts("Invalid input. Please enter Y or N.");
        while (getchar() != '\n');
        return -1;
    }

    selected_input = toupper(selected_input);
    if (selected_input != 'Y' && selected_input != 'N') {
        puts("Invalid input. Please enter Y or N.");
        return -1;
    }

    return selected_input;
}

char *get_filepath(void){
    char* filepath = malloc(sizeof(char) * 256);
    if (!filepath){
        perror("Memory allocation failed in file_utils.c.");
        return NULL;
    }
    puts("Input relative-path of text file to load words from:\n");
    if (fgets(filepath, 256, stdin) == NULL){
        perror("Error reading file path. Please ensure filepath is less than 256 characters and valid relative filepath.");
        free(filepath);
        return NULL;
    }

    filepath[strcspn(filepath, "\n")] = 0;
    return filepath;
}

int check_txt_file(char* filename){
    int len = dynamic_string_len(filename);
    int i = 0;
    char file_type[5];
    while (len - 4 + i < len)
    {
        file_type[i] = filename[len - 4 + i];
        i++;
    }
    file_type[i] = '\0';
    return !strcmp(file_type, ".txt");
}

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
        perror("file_utils: Error: could not open file.");
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
            strcpy(string_array[i], token);
            to_lower(string_array[i++]);
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

/**
 * @brief 
 * Function to check if a file is either .pdf or .txt
 * 
 * @param filename const char*
 */
int isFileValid(const char *filename) {
    const char *extensions[] = {".pdf", ".txt", ".doc", ".bin", ".dat", "\0"};
    /*Find the position of the last '.' in the filename */
    const char *dot = strrchr(filename, '.');
    int i = 0;

    if (dot == NULL) {
        return 0; /* No extension found */
    }
    
    while (*extensions[i] != '\0') {
        if (strcasecmp(dot, extensions[i]) == 0) { /* Compare the extension with the expected one */
            FILE *file = fopen(filename, "r"); /* check if the file exists */
            if (file != NULL) {
                fclose(file); /* Close the file if it exists */
                return 1; /* File exists and has a valid extension */
            } else {
                return 0; /* File does not exist or cannot be accessed */
            }
            return 1;
        }
        i++;
    }
    return 0;
}

#endif
/**  EOF **/
