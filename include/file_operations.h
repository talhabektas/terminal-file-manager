#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

int copy_file(const char* source, const char* dest);  // kopyalama
int move_file(const char* source, const char* dest);  // taşıma
int remove_file(const char* path);                    // silme
int display_file(const char* path);                   // içerik gösterme
int search_file(const char* dir, const char* name);   // dosya arama

#endif