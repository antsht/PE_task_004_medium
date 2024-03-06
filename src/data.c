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

ErrorCode get_dir_path(char *dir_path) {
    if (scanf("%256s", dir_path) != 1) {
        return INVALID_INPUT;
    }
    DIR *pdir = opendir(dir_path);
    if (pdir == NULL) {
        return IO_ERROR;
    }
    closedir(pdir);
    return OK;
}

ErrorCode read_files_in_dir(char *dir_path, Files *files) {
    DIR *pdir = opendir(dir_path);
    if (pdir == NULL) {
        return IO_ERROR;
    }
    struct dirent *pdirent;
    while ((pdirent = readdir(pdir)) != NULL) {
        if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0) {
            continue;
        }
        strcpy(files->files[files->files_count].filename, pdirent->d_name);
        calc_ascii_sum_for_file(dir_path, &(files->files[files->files_count]));
        files->files_count++;
        if (files->files_count == MAX_FILES) {
            break;
        }
    }
    closedir(pdir);
    return OK;
}

ErrorCode ascii_sort_files(Files *files) {
    qsort(files->files, files->files_count, sizeof(File_t), &compare_files_by_ascii_sum);
    return OK;
}

int compare_files_by_ascii_sum(const void *a, const void *b) {
    return ((File_t *)a)->ascii_sum - ((File_t *)b)->ascii_sum;
}

ErrorCode rename_files_in_dir(char *dir_path, Files *files) {
    for (int i = 0; i < files->files_count; i++) {
        char new_name[2 * MAX_NAME_LEN];
        sprintf(new_name, "%s/%d_%s", dir_path, i + 1, files->files[i].filename);
        char old_name[2 * MAX_NAME_LEN];
        sprintf(old_name, "%s/%s", dir_path, files->files[i].filename);
        rename(old_name, new_name);
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

ErrorCode calc_ascii_sum_for_file(char *dir_path, File_t *file) {
    char full_name[2 * MAX_NAME_LEN];
    sprintf(full_name, "%s/%s", dir_path, file->filename);
    FILE *pfile = open_file(full_name, "r");
    file->ascii_sum = 0;
    char c;
    while ((c = fgetc(pfile)) != EOF) {
        file->ascii_sum += c;
    }
    fclose(pfile);
    return OK;
}