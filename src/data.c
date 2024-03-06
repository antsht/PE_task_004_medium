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
    int shift = get_shift_from_key(ENCODE_KEY);
    FILE *pfile = open_file(file_path, "r+");

    char c;
    while ((c = fgetc(pfile)) != EOF) {
        if (isalpha(c)) {
            if (isupper(c)) {
                c = (c - 'A' + shift) % 26 + 'A';
            } else {
                c = (c - 'a' + shift) % 26 + 'a';
            }
            fseek(pfile, -1, SEEK_CUR);
            fputc(c, pfile);
            fseek(pfile, 1, SEEK_CUR);
        }
    }
    fclose(pfile);
    return OK;
}

int get_shift_from_key(const char *key) {
    int shift = 0;
    for (int i = 0; i < (int)strlen(key); i++) {
        if ('a' <= key[i] && key[i] <= 'z')
            shift += key[i] - 'a' + 1;
        else if ('A' <= key[i] && key[i] <= 'Z')
            shift += key[i] - 'A' + 1;
    }
    return shift;
}