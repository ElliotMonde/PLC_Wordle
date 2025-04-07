#ifndef STRING_UTILS_H
#define STRING_UTILS_H
char *banned_two_letter_words[] = {"we", "We", "he", "He", "be", "Be", "is", "Is", "in", "In", "it", "It", "on", "On","of", "Of", "to", "To", "ve", "ll", "re", "as", "As", "at", "At", '\0'};
char *banned_three_letter_words[] = {"she", "She", "are", "Are", "has", "Has", "had", "Had", '\0'};
char *banned_four_letter_words[] = {"have", "Have", "they", "They", "them", "Them", "this", "This", "that", "That", '\0'};
char *banned_five_letter_words[] = {"these", "These", "that", "That", '\0'};

typedef struct {
    char *val;
    int len;
} Chosen_Word;

int check_file_type(char *filename, char* ext);
int check_word(char *s, char **banned_array);
int is_banned_word(char *str);
void remove_banned_words(char ***string_array_ptr);
int array_len(char **arr);
int dynamic_string_len(char *str);
char *get_random_word(char **str);
int random_index(int upperbound_index);
void to_lower(char *s);
int hash_f(char *s);
int *check_guess(char *guess, char *chosen_word, int len);
#endif
/**  EOF **/
