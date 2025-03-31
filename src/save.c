#ifndef SAVE_C
#define SAVE_C

#include "../include/main.h"
#include "../include/file_utils.h"
#include "../include/save.h"

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

void updateStats(gameStats *Stats, int result) {
    if (result == 1) { // Win
        Stats->totalWins++;
        Stats->streak++;
    } else if (result == 0) { // Loss
        Stats->totalLosses++;
        Stats->streak = 0; // Reset streak on loss
    }
}
#endif