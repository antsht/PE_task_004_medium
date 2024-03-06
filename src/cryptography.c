#include "data.h"

int main(void) {
    ErrorCode error;
    char file_path[MAX_NAME_LEN];
    try(error = get_file_path(file_path));
    printf("file_path: %s\n", file_path);
    try(error = encrypt_file(file_path));

    return 0;
}