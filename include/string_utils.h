const char *banned_one_letter_words[] = {"a", "A", "d", "D", "i", "I", "s", "S", "\0"};
const char *banned_two_letter_words[] = {"we", "We", "he", "He", "be", "Be", "is", "Is", "in", "In", "on", "On", "ve", "ll", "re", "as", "As", "\0"};
const char *banned_three_letter_words[] = {"she", "She", "are", "Are", "has", "Has", "had", "Had", "\0"};
const char *banned_four_letter_words[] = {"have", "Have", "they", "They", "them", "Them", "this", "This", "that", "That", "\0"};
const char *banned_five_letter_words[] = {"these", "These", "that", "That", "\0"};

int check_word(char *s, const char **banned_array);
int is_banned_word(char *str);
int array_len(const char **arr);
int dynamic_string_len(char *str);

/**  EOF **/
