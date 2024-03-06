#include "data.h"

int main(void) {
    ErrorCode error;
    char dir_path[MAX_NAME_LEN];
    try(error = get_dir_path(dir_path));
    Files files;
    files.files_count = 0;
    try(error = read_files_in_dir(dir_path, &files));
    try(error = ascii_sort_files(&files));
    try(error = rename_files_in_dir(dir_path, &files));
    return 0;
}