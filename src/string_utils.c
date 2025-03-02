#include <stdio.h>
#include "../include/string_utils.h"

int check_word(char* s, const char** banned_array){
    int i, arr_len = array_len(banned_array);
    for (i = 0; i < arr_len - 1; i++)
    {
        if (!strcmp(s, banned_array[i])){
            return 0;
        }
    }
    return 1;
}

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
        return 1;
    }
}

int array_len(const char** arr){
    int i = 0;
    while (strcmp(arr[i], "\0"))
    {
        i++;
    }
    return i;
}

int dynamic_string_len(char *str)
{
    int i = 0;
    while (str[i]){
        i++;
    }
    return i;
}

/** EOF **/
