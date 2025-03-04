#ifndef STRING_UTILS_C
#define STRING_UTILS_C

#include "../include/main.h"
#include "../include/file_utils.h"
#include "../include/string_utils.h"

/**
 * @brief
 * The word that will be guessed in this round.
 */
typedef struct
{
    char *word;
    int len;
} chosen_word;

/**
 * @brief Get a random word from the input string.
 *
 * @param str char**
 * @return char*
 */
char *get_random_word(char **str)
{
    int len = array_len(str);
    return str[random_index(len)];
}

int check_word(char *s, char **banned_array)
{
    int i, arr_len = array_len(banned_array);
    for (i = 0; i < arr_len - 1; i++)
    {
        if (!strcmp(s, banned_array[i]))
        {
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
        return 1;
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
 * @brief
 * The function removes banned words in (char**) string_array. The function takes a string array pointer, which will be pointed to a new string array which has copies of the valid words. The original string array and its strings will have their memory freed.
 *
 * @param string_array char**
 */
void remove_banned_words(char ***string_array_ptr)
{
    int j = 0, i = 0;
    char **holder;

    while ((*string_array_ptr)[i])
    {
        if (!is_banned_word((*string_array_ptr)[i]))
        {
            j++;
        }
        i++;
    }

    if (!(holder = (char **)malloc(sizeof(char *) * (j + 1))))
    {
        perror("string_utils: error allocating memory.");
        return;
    }
    i = 0;
    j = 0;

    while ((*string_array_ptr)[i])
    {
        if (!is_banned_word((*string_array_ptr)[i]))
        {
            holder[j] = strdup((*string_array_ptr)[i]);
            if (!holder[j])
            {
                perror("string_utils: error allocating memory to holder.");
                while (j > 0)
                {
                    free(holder[--j]);
                }
                free(holder);
                return;
            }
            j++;
        }
        i++;
    }
    holder[j] = NULL;
    i = 0;
    while ((*string_array_ptr)[i])
    {
        free((*string_array_ptr)[i]);
        i++;
    }
    *string_array_ptr = holder;
}

/**
 * @brief Returns the number of elements in the string array.
 *
 * @param arr char**
 * @return int
 */
int array_len(char **arr)
{
    int i = 0;
    while (arr[i] && strcmp(arr[i], "\0"))
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
    while (str[i])
    {
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
int random_index(int upperbound)
{
    srand(time(NULL));
    return rand() % upperbound;
}

/**
 * @brief
 * References a string pointer and converts uppercase characters in string to lowercase.
 *
 * @param s char*
 */
void to_lower(char *s)
{
    int i = -1;
    while (s[++i])
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] -= 'A' - 'a';
        }
    }
}

/**
 * @brief
 * The hash function returns an almost-unique hashcode for unique words.
 *
 * @param s char*
 * @return int
 */
int hash_f(char *s)
{
    int i = -1, code = 0;
    while (s[++i])
    {
        code += s[i] * (int)pow(10, i);
    }
    return code;
}

/**
 * @brief Checks the guess against the chosen word. for each letter in guess, if letter exists and is same position in word, 1 is assigned at the index of the output int array.
 * If the letter exists but not the same position in chosen word, 2 is assigned at the index of the output int array. Else 0 is assigned at the index of the output array.
 *
 * 1: correct letter and position,
 *
 * 2: correct letter but incorrect position,
 *
 * 0: wrong letter.
 *
 * @param guess char*
 * @param chosen_word char*
 * @param len int
 * @return int*
 */
int *check_guess(char *guess, char *chosen_word, int len)
{
    int i;
    int store[26];
    int *res = (int *)malloc(sizeof(int) * len);
    for (i = 0; i < 26; i++)
    {
        store[i] = 0;
    }
    for (i = 0; i < len; i++)
    {
        store[chosen_word[i] - 'a']++;
    }
    for (i = 0; i < len; i++)
    {
        if (store[guess[i] - 'a'] > 0)
        {
            res[i] = (chosen_word[i] == guess[i]) ? 1 : 2;
            store[guess[i] - 'a']--;
        }
        else
        {
            res[i] = 0;
        }
    }
    return res;
}

#endif
/** EOF **/
