#ifndef SAVE_C
#define SAVE_C

#include "../include/main.h"
#include "../include/file_utils.h"
#include "../include/save.h"

/*
void saveGame(save_stats *playerFile, const char *fileName)
{
    FILE *sFile = fopen(fileName, "wb");
    if (!sFile)
    {
        perror("Invalid Save File Name");
        return;
    }
    fwrite(playerFile, sizeof(save_stats), 1, sFile);

    int pathLength = (playerFile->gameInstance.filepath) ? strlen(playerFile->gameInstance.filepath) + 1 : 0;
    fwrite(&pathLength, sizeof(int), 1, sFile);
    if (pathLength > 0)
    {
        fwrite(playerFile->gameInstance.filepath, sizeof(char), pathLength, sFile);
    }

    int wordLength = (playerFile->gameInstance.chosen_word->val) ? strlen(playerFile->gameInstance.chosen_word->val) + 1 : 0;
    fwrite(&wordLength, sizeof(int), 1, sFile);
    if (wordLength > 0)
    {
        fwrite(playerFile->gameInstance.chosen_word->val, sizeof(char), wordLength, sFile);
    }

    int guessedCount = 0;
    while (playerFile->gameInstance.guessed_words && playerFile->gameInstance.guessed_words[guessedCount])
    {
        guessedCount++;
    }
    fwrite(&guessedCount, sizeof(int), 1, sFile);
    for (int i = 0; i < guessedCount; i++)
    {
        int guessLen = strlen(playerFile->gameInstance.guessed_words[i]) + 1;
        fwrite(&guessLen, sizeof(int), 1, sFile);
        fwrite(playerFile->gameInstance.guessed_words[i], sizeof(char), guessLen, sFile);
    }
    fclose(sFile);
}

*/

Game *load_from_save_file(char *filepath)
{
    int i;
    FILE *f;
    Game *game = (Game *)malloc(sizeof(Game));
    if (!game)
    {
        perror("load_game: Error allocating memory to game.");
        return NULL;
    }

    f = fopen(filepath, "rb");
    if (!f)
    {
        perror("load_game: Error: could not open file.");
        return NULL;
    }
    fread(&game->state, sizeof(int), 1, f);
    fread(&game->turn, sizeof(int), 1, f);

    game->filepath = filepath;

    game->chosen_word = (Chosen_Word *)malloc(sizeof(Chosen_Word));
    fread(&game->chosen_word->len, sizeof(int), 1, f);

    game->chosen_word->val = (char *)malloc(sizeof(char) * game->chosen_word->len);
    fread(game->chosen_word->val, sizeof(char), game->chosen_word->len, f);

    game->guessed_words = (char **)malloc(sizeof(char *) * game->chosen_word->len);

    for (i = 0; i < game->turn; i++)
    {
        game->guessed_words[i] = (char *)malloc(sizeof(char) * (game->chosen_word->len + 1));
        fread(game->guessed_words[i], sizeof(char) * (game->chosen_word->len + 1), 1, f);
    }

    fclose(f);
    return game;
}

/*

void updateStats(save_stats *playerFile, int result)
{
    if (result == 1)
    {
        playerFile->totalWins++;
        playerFile->streak++;
    }
    else if (result == 0)
    {
        playerFile->totalLosses++;
        playerFile->streak = 0;
    }
}

void free_save_stats(save_stats *playerFile)
{
    if (playerFile->gameInstance.filepath)
    {
        free(playerFile->gameInstance.filepath);
        playerFile->gameInstance.filepath = NULL;
    }
    if (playerFile->gameInstance.chosen_word)
    {
        if (playerFile->gameInstance.chosen_word->val)
        {
            free(playerFile->gameInstance.chosen_word->val);
            playerFile->gameInstance.chosen_word->val = NULL;
        }
        free(playerFile->gameInstance.chosen_word);
        playerFile->gameInstance.chosen_word = NULL;
    }
    if (playerFile->gameInstance.guessed_words)
    {
        int i = 0;
        while (playerFile->gameInstance.guessed_words[i])
        {
            free(playerFile->gameInstance.guessed_words[i]);
            playerFile->gameInstance.guessed_words[i] = NULL;
            i++;
        }
        free(playerFile->gameInstance.guessed_words);
        playerFile->gameInstance.guessed_words = NULL;
    }
}

*/

#endif
/** EOF **/
