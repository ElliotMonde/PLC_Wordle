#ifndef SAVE_H
#define SAVE_H
#include "game_struct.h"
typedef struct{
    int totalWins;
    int totalLosses;
    int streak;
}save_stats;

void saveGame(save_stats * playerFile, const char * fileName);

void updateStats(save_stats * playerFile, int result);

void free_save_stats(save_stats * playerFile);

Game *load_from_save_file(char *filepath);

#endif
/** EOF **/
