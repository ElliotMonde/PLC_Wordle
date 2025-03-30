#ifndef SAVE_H
#define SAVE_H

typedef struct{
    int totalWins;
    int totalLosses;
    int streak;
}gameStats;

void newStats(gameStats * Stats);

void saveStats(gameStats * Stats, const char * fileName);

int loadStats(gameStats * Stats, const char * fileName);

#endif