#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "logger.h"

#define LOG_FILE "filemanager.log"

void log_operation(const char* operation, const char* path, int result) {
    time_t now;
    char timestamp[26];
    char log_message[1024];
    int fd;

    // Zaman damgası oluştur
    time(&now);
    ctime_r(&now, timestamp);
    timestamp[24] = '\0';  // \n karakterini kaldır

    // Log mesajı oluştur
    snprintf(log_message, sizeof(log_message),
        "[%s] Operation: %s, Path: %s, Result: %s\n",
        timestamp, operation, path,
        result ? "SUCCESS" : "FAILED");

    // Log dosyasını aç (yoksa oluştur, varsa sonuna ekle)
    fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd != -1) {
        write(fd, log_message, strlen(log_message));
        close(fd);
    }
}
