#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "file_operations.h"
#include "logger.h"

#define BUFFER_SIZE 4096

int copy_file(const char* source, const char* dest) {
    int source_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    
    // Kaynak dosyayı aç
    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) {
        printf("Kaynak dosya açılamadı: %s\n", source);
        log_operation("copy_file", source, 0);
        return -1;
    }
    
    // Hedef dosyayı oluştur
    dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        printf("Hedef dosya oluşturulamadı: %s\n", dest);
        close(source_fd);
        log_operation("copy_file", dest, 0);
        return -1;
    }
    
    // Dosyayı kopyala
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            printf("Yazma hatası oluştu\n");
            close(source_fd);
            close(dest_fd);
            log_operation("copy_file", dest, 0);
            return -1;
        }
    }
    
    close(source_fd);
    close(dest_fd);
    log_operation("copy_file", dest, 1);
    return 0;
}

int move_file(const char* source, const char* dest) {
    // Önce rename ile taşıma dene
    if (rename(source, dest) == 0) {
        log_operation("move_file", dest, 1);
        return 0;
    }
    
    // Rename başarısız olursa kopyala-sil yöntemi kullan
    if (copy_file(source, dest) == 0) {
        if (remove_file(source) == 0) {
            log_operation("move_file", dest, 1);
            return 0;
        }
        remove_file(dest); // Kopyalama başarılı ama silme başarısız olduysa kopyayı da sil
    }
    
    log_operation("move_file", dest, 0);
    return -1;
}

int remove_file(const char* path) {
    if (unlink(path) == -1) {
        printf("Dosya silinemedi: %s\n", path);
        log_operation("remove_file", path, 0);
        return -1;
    }
    log_operation("remove_file", path, 1);
    return 0;
}

int display_file(const char* path) {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("Dosya açılamadı: %s\n", path);
        log_operation("display_file", path, 0);
        return -1;
    }
    
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    
    close(fd);
    log_operation("display_file", path, 1);
    return 0;
}

int search_file(const char* dir, const char* name) {
    DIR *dp;
    struct dirent *entry;
    int found = 0;
    
    dp = opendir(dir);
    if (dp == NULL) {
        printf("Dizin açılamadı: %s\n", dir);
        log_operation("search_file", dir, 0);
        return -1;
    }
    
    while ((entry = readdir(dp)) != NULL) {
        if (strstr(entry->d_name, name) != NULL) {
            printf("%s/%s\n", dir, entry->d_name);
            found = 1;
        }
    }
    
    closedir(dp);
    log_operation("search_file", name, found);
    return found ? 0 : -1;
}