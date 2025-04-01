#ifndef SAVE_C
#define SAVE_C

#include "../include/main.h"
#include "../include/file_utils.h"
#include "../include/state_utils.h"
#include "../include/save.h"

void newGame(saveFile * playerFile){
    playerFile->totalWins = 0;
    playerFile->totalLosses = 0;
    playerFile->streak = 0;
    playerFile->gameInstance = (Game *) malloc(sizeof(Game));
    playerFile->gameInstance = start_new_game();
}

void saveGame(saveFile * playerFile, const char * fileName){
    FILE * sFile = fopen(fileName,"wb");
    if (!sFile){
        perror("Invalid Save File Name");
        return;
    }
    fwrite(playerFile,sizeof(saveFile),1,sFile);
    fclose(sFile);
}

int loadGame(saveFile * playerFile, const char * fileName){
    FILE * sFile = fopen(fileName,"rb");
    if (!sFile){
        perror("Invalid Save File Name");
        return 0;
    }
    fread(playerFile,sizeof(saveFile),1,sFile);
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

Game * getGameInstance(saveFile * playerFile){
    return playerFile->gameInstance;
}

void freeGameInstance(saveFile *playerFile) {
    if (!playerFile) return;
    if (playerFile->gameInstance) {
        free(playerFile->gameInstance);
        playerFile->gameInstance = NULL;
    }
}
#endif