#include <stdio.h>
#include "../include/main.h"
#include "file_utils.c"

int main(int argc, char** argv){
    int array_size = 10;
    char *filename = "../test_inp.txt";
    char **string_array = file_to_string_array(filename, array_size);
    int i;
    for (i = 0; i < array_size; i++){
        if (!string_array[i]){
            break;
        }
        printf("%s\n", string_array[i]);
    }
        return 0;
}

/**  EOF **/
