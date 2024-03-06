#include "data.h"

int main(void) {
    ErrorCode error;
    char file_path_1[MAX_NAME_LEN];
    try(error = get_file_path(file_path_1));
    char file_path_2[MAX_NAME_LEN];
    try(error = get_file_path(file_path_2));
    int result = compare_files(file_path_1, file_path_2);
    if (result == 0) try(error = delete_file(file_path_2));

    return 0;
}