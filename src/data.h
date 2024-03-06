#ifndef DATA_H
#define DATA_H
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "errors.h"

#define MAX_NAME_LEN 256
#define MAX_FILES 256
#define BUFFER 1024
#define ENCODE_KEY "peeredu"

typedef struct {
    char filename[MAX_NAME_LEN];
    long ascii_sum;
} File_t;

typedef struct {
    File_t files[MAX_FILES];
    int files_count;
} Files;

ErrorCode get_file_path(char *file_path);

ErrorCode get_dir_path(char *dir_path);

ErrorCode read_files_in_dir(char *dir_path, Files *files);

ErrorCode ascii_sort_files(Files *files);

ErrorCode rename_files_in_dir(char *dir_path, Files *files);

int compare_files_by_ascii_sum(const void *a, const void *b);

int get_file_size(const char *file_path);

int compare_files(const char *file_path_1, const char *file_path_2);

FILE *open_file(const char *db_path, const char *mode);

ErrorCode delete_file(const char *file_path);

ErrorCode encrypt_file(const char *file_path);

ErrorCode calc_ascii_sum_for_file(char *dir_path, File_t *file);

#endif