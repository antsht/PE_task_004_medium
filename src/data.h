#ifndef DATA_H
#define DATA_H
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "errors.h"

#define MAX_NAME_LEN 256
#define BUFFER 1024

ErrorCode get_file_path(char *file_path);

int get_file_size(const char *file_path);

int compare_files(const char *file_path_1, const char *file_path_2);

FILE *open_file(const char *db_path, const char *mode);

ErrorCode delete_file(const char *file_path);

#endif