#ifndef FILE_UTILS_H
#define FILE_UTILS_H
int get_user_input(void);
char *get_filepath(void);
char **file_to_string_array(char *filename, int array_size);
void free_string_array(char **string_array, int len);
int is_file_valid(const char *filename, char*extensions[]);
char *load_file(char** extensions, char* s_type);
#endif
/** EOF **/
