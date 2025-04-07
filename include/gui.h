#ifndef GUI_H
#define GUI_H
#include "game_struct.h"

void print_welcome(void);
void print_guess_feedback(char *guess, Chosen_Word* chosen_word);
void print_game_over(void);
void print_win_message(void);

#endif
/** EOF **/
