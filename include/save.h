#ifndef SAVE_H
#define SAVE_H

typedef struct{
    int totalWins;
    int totalLosses;
    int streak;
    Game * gameInstance;
}saveFile;

void newGame(saveFile * playerFile);

void saveGame(saveFile * playerFile, const char * fileName);

int loadGame(saveFile * playerFile, const char * fileName);

void updateStats(saveFile * playerFile, int result);

Game * getGameInstance(saveFile * playerFile);

void freeGameInstance(saveFile * playerFile);

#endif