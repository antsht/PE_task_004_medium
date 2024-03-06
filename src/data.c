#include "data.h"

ErrorCode get_file_path(char *file_path) {
    if (scanf("%256s", file_path) != 1) {
        return INVALID_INPUT;
    }
    if (access(file_path, F_OK) != 0) {
        return IO_ERROR;
    }
    return OK;
}

int get_file_size(const char *file_path) {
    FILE *pfile = open_file(file_path, "rb");
    fseek(pfile, 0, SEEK_END);
    int size = ftell(pfile);
    fclose(pfile);
    return size;
}

int compare_files(const char *file_path_1, const char *file_path_2) {
    if (get_file_size(file_path_1) != get_file_size(file_path_2)) {
        return -1;
    }
    FILE *pfile_1 = open_file(file_path_1, "rb");
    FILE *pfile_2 = open_file(file_path_2, "rb");

    char c1, c2;
    while ((c1 = fgetc(pfile_1)) && (c2 = fgetc(pfile_2)) && c1 == c2) {
        if (feof(pfile_1) && feof(pfile_2)) {
            fclose(pfile_1);
            fclose(pfile_2);
            return 0;
        }
    }
    fclose(pfile_1);
    fclose(pfile_2);
    return -1;
}

FILE *open_file(const char *db_path, const char *mode) {
    FILE *pfile = fopen(db_path, mode);
    if (pfile == NULL) {
        puckxit();
    }
    return pfile;
}

ErrorCode delete_file(const char *file_path) {
    if (remove(file_path) != 0) {
        return IO_ERROR;
    }
    return OK;
}

ErrorCode encrypt_file(const char *file_path) {
    FILE *pfile = open_file(file_path, "r+");

    char c;
    char *key = ENCODE_KEY;
    char *key_current_position = key;
    int shift = 0;
    while ((c = fgetc(pfile)) != EOF) {
        if (isalpha(c) && c != ' ') {
            if (islower(*key_current_position))
                shift = *key_current_position - 'a';
            else if (isupper(*key_current_position))
                shift = *key_current_position - 'A';
            if (*(++key_current_position) == '\0') key_current_position = key;
            if (isupper(c)) {
                c = (c - 'A' + shift) % 26 + 'A';
            } else {
                c = (c - 'a' + shift) % 26 + 'a';
            }
            fseek(pfile, -1, SEEK_CUR);
            fputc(c, pfile);
        }
    }
    fclose(pfile);
    return OK;
}
