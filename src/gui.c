#include <stdio.h>
#include "../include/gui.h"

#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define GREY    "\033[0;37m"

void print_welcome() {
    printf("========== WORDLE GAME ==========\n");
    printf("Green: Correct | Yellow: Wrong place | Grey: Not in word\n");
    printf("=================================\n");
}

void print_guess_feedback(const char* guess, const int* result, int len) {
    for (int i = 0; i < len; i++) {
        if (result[i] == 2)
            printf(GREEN "%c " RESET, guess[i]);
        else if (result[i] == 1)
            printf(YELLOW "%c " RESET, guess[i]);
        else
            printf(GREY "%c " RESET, guess[i]);
    }
    printf("\n");
}

void print_game_over(const char* answer) {
    printf("\n❌ Game Over! The word was: %s\n", answer);
}

void print_win_message() {
    printf("\n🎉 " GREEN "You guessed the word! Congratulations!" RESET "\n");
}
