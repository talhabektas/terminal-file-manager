#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

int list_directory(const char* path);  // ls benzeri komut
int create_directory(const char* path); // mkdir
int remove_directory(const char* path); // rmdir
int is_directory_empty(const char* path); // dizin boş mu kontrolü

#endif