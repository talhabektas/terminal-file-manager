#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

int copy_file(const char* source, const char* dest);  // copy
int move_file(const char* source, const char* dest);  // move
int remove_file(const char* path);                    // delete
int display_file(const char* path);                   // display
int search_file(const char* dir, const char* name);   // search file

#endif