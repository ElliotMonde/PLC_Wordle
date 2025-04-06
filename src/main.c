#include "../include/main.h"
#include "file_utils.c"
#include "string_utils.c"
#include "state_utils.c"
#include "save.c"

// int main(int argc, char **argv)
// {
//     saveFile * playerFile = (saveFile *)malloc(sizeof(saveFile));
//     Game * gameObject; // Game Object not recognised cause sate_utils.h not included
//     int newOrLoad = get_user_input();
//     while (newOrLoad == -1){
//         newOrLoad = get_user_input();
//     }
//     if (newOrLoad == 121){ //if "Y", Load Existing File
//         loadGame(playerFile);
//     }
//     else{ //if "N", Load New File
//         newGame(playerFile);
//     }
//     gameObject = getGameInstance(playerFile);
//     while (gameObject->state == TURN){
//         call_state(gameObject);
//     }
//     call_state(gameObject);

//     /** free malloc */
//     free_game(gameObject);

//     return 0;
// }

#define MAX_FILENAME_LEN 100

int main(int argc, char **argv) {
    saveFile playerFile;
    int loadSuccess = 0;
    char fileName[MAX_FILENAME_LEN] = {0};
    printf("Enter the save file name (or press Enter to create a new game): ");
    fgets(fileName, MAX_FILENAME_LEN, stdin);
    fileName[strcspn(fileName, "\n")] = 0; 
    if (strlen(fileName) > 0) {
        FILE *checkFile = fopen(fileName, "rb");
        if (checkFile) {
            fclose(checkFile);
            loadSuccess = loadGame(&playerFile, fileName);
            if (!loadSuccess) {
                printf("Error loading save file. Starting a new game.\n");
                playerFile.gameInstance = *start_new_game();
            }
        } else {
            printf("No existing save file found. Starting a new game.\n");
            playerFile.gameInstance = *start_new_game();
        }
    } else {
        printf("Starting a new game.\n");
        playerFile.gameInstance = *start_new_game();
    }

    Game *game = &playerFile.gameInstance;

    while (game->state == TURN) {
        call_state(game);
        saveGame(&playerFile, fileName); // Autosave
    }

    call_state(game);
    saveGame(&playerFile, fileName);
    freeSaveFile(&playerFile);

    return 0;
}

/**  EOF **/
