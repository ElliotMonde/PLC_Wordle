#ifndef SAVE_H
#define SAVE_H

typedef struct{
    int totalWins;
    int totalLosses;
    int streak;
    Game gameInstance;
}saveFile;

void saveGame(saveFile * playerFile, const char * fileName);

int loadGame(saveFile * playerFile, const char * fileName);

void updateStats(saveFile * playerFile, int result);

void freeSaveFile(saveFile * playerFile);

#endif
/** EOF **/
