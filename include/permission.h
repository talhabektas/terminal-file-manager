#ifndef PERMISSIONS_H
#define PERMISSIONS_H

int change_permissions(const char* path, mode_t mode); // chmod
int display_permissions(const char* path);             // izinleri göster

#endif
