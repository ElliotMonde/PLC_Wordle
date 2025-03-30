#include "../include/main.h"
#include "../include/file_utils.h"
#include "save.h"

void newStats(gameStats * Stats){
    Stats->totalWins = 0;
    Stats->totalLosses = 0;
    Stats->streak = 0;
}

void saveStats(gameStats * Stats, const char * fileName){
    FILE * saveFile = fopen(fileName,"wb");
    if (!saveFile){
        perror("Invalid Save File Name");
        return;
    }
    fwrite(Stats,sizeof(gameStats),1,saveFile);
    fclose(saveFile);
}

int loadStats(gameStats * Stats, const char * fileName){
    FILE * saveFile = fopen(fileName,"rb");
    if (!saveFile){
        perror("Invalid Save File Name");
        return 0;
    }
    fread(Stats,sizeof(gameStats),1,saveFile);
    fclose(saveFile);
    return 1;
}
