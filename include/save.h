#ifndef SAVE_H
#define SAVE_H
#include "game_struct.h"

Game *load_from_save_file(char *filepath, Stats* stats);
void save_to_file(Game *game, Stats *stat);

#endif
/** EOF **/
