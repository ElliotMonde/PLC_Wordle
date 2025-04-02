#ifndef SAVE_C
#define SAVE_C

#include "../include/main.h"
#include "../include/file_utils.h"
#include "../include/state_utils.h"
#include "../include/save.h"

void saveGame(saveFile * playerFile, const char * fileName){
    FILE * sFile = fopen(fileName,"wb");
    if (!sFile){
        perror("Invalid Save File Name");
        return;
    }
    fwrite(playerFile,sizeof(saveFile),1,sFile);

    int pathLength = (playerFile->gameInstance.filepath) ? strlen(playerFile->gameInstance.filepath)+1 : 0;
    fwrite(&pathLength,sizeof(int),1,sFile);
    if (pathLength > 0) {
        fwrite(playerFile->gameInstance.filepath, sizeof(char), pathLength, sFile);
    }

    int wordLength = (playerFile->gameInstance.chosen_word->val) ? strlen(playerFile->gameInstance.chosen_word->val)+1 : 0;
    fwrite(&wordLength,sizeof(int),1,sFile);
    if (wordLength > 0) {
        fwrite(playerFile->gameInstance.chosen_word->val, sizeof(char), wordLength, sFile);
    }

    int guessedCount = 0;
    while (playerFile->gameInstance.guessed_words && playerFile->gameInstance.guessed_words[guessedCount]) {
        guessedCount++;
    }
    fwrite(&guessedCount, sizeof(int), 1, sFile);
    for (int i = 0; i < guessedCount; i++) {
        int guessLen = strlen(playerFile->gameInstance.guessed_words[i]) + 1;
        fwrite(&guessLen, sizeof(int), 1, sFile);
        fwrite(playerFile->gameInstance.guessed_words[i], sizeof(char), guessLen, sFile);
    }
    fclose(sFile);
}



int loadGame(saveFile * playerFile, const char * fileName){
    FILE * sFile = fopen(fileName,"rb");
    if (!sFile){
        perror("Invalid Save File Name");
        return 0;
    }
    fread(playerFile,sizeof(saveFile),1,sFile);

    int pathLength;
    fread(&pathLength,sizeof(int),1,sFile);
    if (pathLength >0){
        playerFile->gameInstance.filepath = (char *)malloc(pathLength);
        fread(playerFile->gameInstance.filepath,sizeof(char), pathLength, sFile);
    }

    int wordLength;
    fread(&wordLength,sizeof(int),1,sFile);
    if (wordLength >0){
        playerFile->gameInstance.chosen_word = (Chosen_Word *)malloc(sizeof(Chosen_Word));
        playerFile->gameInstance.chosen_word->val = (char *) malloc(wordLength);
        fread(playerFile->gameInstance.chosen_word->val,sizeof(char), wordLength, sFile);
        playerFile->gameInstance.chosen_word->len = wordLength - 1;
    }

    int guessedCount;
    fread(&guessedCount, sizeof(int), 1, sFile);
    for (int i=0 ; i<guessedCount; i++){
        int guessLen;
        fread(&guessLen, sizeof(int), 1, sFile);
        playerFile->gameInstance.guessed_words[i] = (char *)malloc(guessLen);
        fread(playerFile->gameInstance.guessed_words[i], sizeof(char), guessLen, sFile);
    }
    fclose(sFile);
    return 1;
}



void updateStats(saveFile * playerFile, int result) {
    if (result == 1) { // Win
        playerFile->totalWins++;
        playerFile->streak++;
    } else if (result == 0) { // Loss
        playerFile->totalLosses++;
        playerFile->streak = 0; // Reset streak on loss
    }
}



void freeSaveFile(saveFile *playerFile) {
    if (playerFile->gameInstance.filepath) {
        free(playerFile->gameInstance.filepath);
        playerFile->gameInstance.filepath = NULL;
    }
    if (playerFile->gameInstance.chosen_word) {
        if (playerFile->gameInstance.chosen_word->val) {
            free(playerFile->gameInstance.chosen_word->val);
            playerFile->gameInstance.chosen_word->val = NULL;
        }
        free(playerFile->gameInstance.chosen_word);
        playerFile->gameInstance.chosen_word = NULL;
    }
    if (playerFile->gameInstance.guessed_words) {
        int i = 0;
        while (playerFile->gameInstance.guessed_words[i]) {
            free(playerFile->gameInstance.guessed_words[i]);
            playerFile->gameInstance.guessed_words[i] = NULL;
            i++;
        }
        free(playerFile->gameInstance.guessed_words);
        playerFile->gameInstance.guessed_words = NULL;
    }
}
#endif