#ifndef SAVE_C
#define SAVE_C

#include "../include/main.h"
#include "../include/file_utils.h"
#include "../include/save.h"

Game *load_from_save_file(char *filepath, Stats* stats)
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

    fread(&stats->wins, sizeof(int), 1, f);
    fread(&stats->losses, sizeof(int), 1, f);
    fread(&stats->streak, sizeof(int), 1, f);

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

void save_to_file(Game* game, Stats* stat){

    int i;

    if (game->filepath != NULL)
    {
        FILE *f = fopen(game->filepath, "wb");
        if (!f){
            perror("save_to_file: unable to open file.");
        }

        fwrite(&stat->wins, sizeof(int), 1, f);
        fwrite(&stat->losses, sizeof(int), 1, f);
        fwrite(&stat->streak, sizeof(int), 1, f);

        fwrite(&game->state, sizeof(int), 1, f);
        fwrite(&game->turn, sizeof(int), 1, f);

        fwrite(&game->chosen_word->len, sizeof(int), 1, f);
        fwrite(game->chosen_word->val, sizeof(char), game->chosen_word->len, f);

        for (i = 0; i < game->turn; i++){
            fwrite(game->guessed_words[i], sizeof(char) * (game->chosen_word->len + 1), 1, f);
        }
        
        fclose(f);
    }
}

/*

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
