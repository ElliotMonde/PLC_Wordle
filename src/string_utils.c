#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/string_utils.h"

/**
 * @brief Get a random word from the input string.
 *
 * @param str char**
 * @return char* 
 */
char *get_random_word(char **str){
    int len = array_len(str);
    return str[random_index(len)];
}

int check_word(char* s, char** banned_array){
    int i, arr_len = array_len(banned_array);
    for (i = 0; i < arr_len - 1; i++)
    {
        if (!strcmp(s, banned_array[i])){
            return 1;
        }
    }
    return 0;
}

/**
 * @brief 
 * Checks if the input word is a banned word. Returns 0 if not a banned word, else 1.
 * 
 * @param str char*
 * @return int 
 */
int is_banned_word(char *str)
{
    int len = dynamic_string_len(str);
    switch (len)
    {
    case 1:
        return check_word(str, banned_one_letter_words);
    case 2:
        return check_word(str, banned_two_letter_words);
    case 3:
        return check_word(str, banned_three_letter_words);
    case 4:
        return check_word(str, banned_four_letter_words);
    case 5:
        return check_word(str, banned_five_letter_words);
    default:
        return 0;
    }
}

/**
 * @brief Returns the number of elements in the string array.
 * 
 * @param arr char**
 * @return int 
 */
int array_len(char** arr){
    int i = 0;
    while (strcmp(arr[i], "\0"))
    {
        i++;
    }
    return i;
}

/**
 * @brief Returns the number of characters in the string, excluding the '\0' at end of string.
 * 
 * @param str char*
 * @return int 
 */
int dynamic_string_len(char *str)
{
    int i = 0;
    while (str[i]){
        i++;
    }
    return i;
}

/**
 * @brief 
 * Returns a random integer using current time as seed.
 * the input upperbound is excluded from the range of possible return values.
 * @param upperbound int
 * @return int 
 */
int random_index(int upperbound){
    srand(time(NULL));
    return rand() % upperbound;
}

/** EOF **/
