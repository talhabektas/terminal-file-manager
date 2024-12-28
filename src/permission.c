/*
* permissions.c
* Handles file permission operations using chmod
* and permission display functionality
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "permissions.h"
#include "logger.h"

// Changes file permissions using chmod system call
// mode should be provided in octal format (e.g., 0644)
int change_permissions(const char* path, mode_t mode) {
    if (chmod(path, mode) == -1) {
        printf("İzinler değiştirilemedi: %s\n", path);
        log_operation("change_permissions", path, 0);
        return -1;
    }
    log_operation("change_permissions", path, 1);
    return 0;
}


// Displays file permissions in readable format (e.g., -rwxr-xr-x)
// Shows directory (d), user, group, and others permissions
int display_permissions(const char* path) {
    struct stat file_stat;

    if (stat(path, &file_stat) == -1) {
        printf("Dosya bilgileri alınamadı: %s\n", path);
        log_operation("display_permissions", path, 0);
        return -1;
    }

    printf("İzinler: ");
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    log_operation("display_permissions", path, 1);
    return 0;
}

