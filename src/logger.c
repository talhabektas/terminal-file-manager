/*
* logger.c
* Implements logging functionality for the file manager
* Logs operations with timestamp, operation type, and result
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "logger.h"

#define LOG_FILE "filemanager.log"
// Logs an operation with timestamp and result
// operation: type of operation performed
// path: file or directory path
// result: 1 for success, 0 for failure
void log_operation(const char* operation, const char* path, int result) {
    time_t now;
    char timestamp[26];
    char log_message[1024];
    int fd;

    // Create time 
    time(&now);
    ctime_r(&now, timestamp);
    timestamp[24] = '\0';  // Remove \n character. 

    // Create log messages.
    snprintf(log_message, sizeof(log_message),
        "[%s] Operation: %s, Path: %s, Result: %s\n",
        timestamp, operation, path,
        result ? "SUCCESS" : "FAILED");

    // Open log file.(If not exist create it,otherwise add last)
    fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd != -1) {
        write(fd, log_message, strlen(log_message));
        close(fd);
    }
}


