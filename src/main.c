#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"
#include "state_utils.c"
#include "save.c"

int main(int argc, char **argv)
{
    saveFile * playerFile = (saveFile *)malloc(sizeof(saveFile));
    Game * gameObject; // Game Object not recognised cause sate_utils.h not included
    int newOrLoad = get_user_input();
    while (newOrLoad == -1){
        newOrLoad = get_user_input();
    }
    if (newOrLoad == 121){ //if "Y", Load Existing File
        loadGame(playerFile);
    }
    else{ //if "N", Load New File
        newGame(playerFile);
    }
    gameObject = getGameInstance(playerFile);
    while (gameObject->state == TURN){
        call_state(gameObject);
    }
    call_state(gameObject);

    /** free malloc */
    free_game(gameObject);

    return 0;
}

/**  EOF **/
