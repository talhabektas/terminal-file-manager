#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include "directory_ops.h"
#include "logger.h"

int list_directory(const char* path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];

    dir = opendir(path);
    if (dir == NULL) {
        printf("Dizin açılamadı: %s\n", path);
        log_operation("list_directory", path, 0);
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // . ve .. dizinlerini atla
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        if (stat(full_path, &file_stat) < 0)
            continue;

        // Dosya tipini belirle
        char type = '-';
        if (S_ISDIR(file_stat.st_mode)) type = 'd';
        if (S_ISLNK(file_stat.st_mode)) type = 'l';

        // İzinleri göster
        printf("%c%c%c%c%c%c%c%c%c%c %8ld %s\n",
            type,
            (file_stat.st_mode & S_IRUSR) ? 'r' : '-',
            (file_stat.st_mode & S_IWUSR) ? 'w' : '-',
            (file_stat.st_mode & S_IXUSR) ? 'x' : '-',
            (file_stat.st_mode & S_IRGRP) ? 'r' : '-',
            (file_stat.st_mode & S_IWGRP) ? 'w' : '-',
            (file_stat.st_mode & S_IXGRP) ? 'x' : '-',
            (file_stat.st_mode & S_IROTH) ? 'r' : '-',
            (file_stat.st_mode & S_IWOTH) ? 'w' : '-',
            (file_stat.st_mode & S_IXOTH) ? 'x' : '-',
            file_stat.st_size,
            entry->d_name);
    }

    closedir(dir);
    log_operation("list_directory", path, 1);
    return 0;
}

int create_directory(const char* path) {
    if (mkdir(path, 0755) == -1) {
        printf("Dizin oluşturulamadı: %s\n", path);
        log_operation("create_directory", path, 0);
        return -1;
    }
    log_operation("create_directory", path, 1);
    return 0;
}

int remove_directory(const char* path) {
    if (!is_directory_empty(path)) {
        printf("Dizin boş değil: %s\n", path);
        return -1;
    }

    if (rmdir(path) == -1) {
        printf("Dizin silinemedi: %s\n", path);
        log_operation("remove_directory", path, 0);
        return -1;
    }
    log_operation("remove_directory", path, 1);
    return 0;
}

int is_directory_empty(const char* path) {
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(path);
    if (dir == NULL)
        return 1;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            count++;
        if (count > 0)
            break;
    }

    closedir(dir);
    return count == 0;
}