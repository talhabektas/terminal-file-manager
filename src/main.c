/*
* main.c
* Main program entry point for the file manager
* Handles command-line arguments and dispatches operations
* to appropriate modules
*
* Supported commands:
* - slist: List directory contents
* - screate: Create new file
* - smkdir: Create new directory
* - sremove: Remove file or directory
* - scopy: Copy file
* - smove: Move file
* - sshow: Display file contents
* - ssearch: Search for files
* - schmod: Change file permissions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // for close() operation. 
#include <fcntl.h> 
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

// Prints usage information and available commands
void print_usage() {
    printf("Kullanım:\n");
    printf("  slist <dizin>                : Dizin içeriğini listele\n");
    printf("  screate <dosya>              : Yeni dosya oluştur\n");
    printf("  smkdir <dizin>               : Yeni dizin oluştur\n");
    printf("  sremove <dosya/dizin>        : Dosya veya dizin sil\n");
    printf("  scopy <kaynak> <hedef>       : Dosya kopyala\n");
    printf("  smove <kaynak> <hedef>       : Dosya taşı\n");
    printf("  sshow <dosya>                : Dosya içeriğini göster\n");
    printf("  ssearch <dizin> <isim>       : Dosya ara\n");
    printf("  schmod <dosya> <izinler>     : Dosya izinlerini değiştir\n");
}

// Main program entry point
// Parses command line arguments and executes requested operation
int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    if (strcmp(argv[1], "slist") == 0) {
        if (argc != 3) {
            printf("Kullanım: slist <dizin>\n");
            return 1;
        }
        return list_directory(argv[2]);
    }
    
    else if (strcmp(argv[1], "screate") == 0) {
        if (argc != 3) {
            printf("Kullanım: screate <dosya>\n");
            return 1;
        }
        int fd = creat(argv[2], 0644);
        if (fd == -1) {
            printf("Dosya oluşturulamadı\n");
            return 1;
        }
        close(fd);
        return 0;
    }
    
    else if (strcmp(argv[1], "smkdir") == 0) {
        if (argc != 3) {
            printf("Kullanım: smkdir <dizin>\n");
            return 1;
        }
        return create_directory(argv[2]);
    }
    
    else if (strcmp(argv[1], "sremove") == 0) {
        if (argc != 3) {
            printf("Kullanım: sremove <dosya/dizin>\n");
            return 1;
        }
        return remove_file(argv[2]);
    }
    
    else if (strcmp(argv[1], "scopy") == 0) {
        if (argc != 4) {
            printf("Kullanım: scopy <kaynak> <hedef>\n");
            return 1;
        }
        return copy_file(argv[2], argv[3]);
    }
    
    else if (strcmp(argv[1], "smove") == 0) {
        if (argc != 4) {
            printf("Kullanım: smove <kaynak> <hedef>\n");
            return 1;
        }
        return move_file(argv[2], argv[3]);
    }
    
    else if (strcmp(argv[1], "sshow") == 0) {
        if (argc != 3) {
            printf("Kullanım: sshow <dosya>\n");
            return 1;
        }
        return display_file(argv[2]);
    }
    
    else if (strcmp(argv[1], "ssearch") == 0) {
        if (argc != 4) {
            printf("Kullanım: ssearch <dizin> <isim>\n");
            return 1;
        }
        return search_file(argv[2], argv[3]);
    }
    
    else if (strcmp(argv[1], "schmod") == 0) {
        if (argc != 4) {
            printf("Kullanım: schmod <dosya> <izinler>\n");
            return 1;
        }
        mode_t mode = strtol(argv[3], NULL, 8);
        return change_permissions(argv[2], mode);
    }
    
    else {
        printf("Geçersiz komut: %s\n", argv[1]);
        print_usage();
        return 1;
    }

    return 0;
}