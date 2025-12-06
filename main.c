#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dirent.h"
#include <unistd.h>

// ====================== FUNCTION HEADERS ======================

void list_files(const char *path);

void create_folder(const char *path);

void create_file(const char *path);

void delete_file_or_folder(const char *path);

void rename_file_or_folder(const char *old_path, const char *new_path);

void clear_screen();

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ====================== MAIN ======================

int main() {
    char path[256];
    int choice;

    while (1) {
        clear_screen();
        printf("\033[38;5;208m");
        printf(" _______  ___   ___      _______    __   __  _______  __    _  _______  _______  _______  ______ \n"  
"|       ||   | |   |    |       |  |  |_|  ||   _   ||  |  | ||   _   ||       ||       ||    _ |  \n"
"|    ___||   | |   |    |    ___|  |       ||  |_|  ||   |_| ||  |_|  ||    ___||    ___||   | ||  \n"
"|   |___ |   | |   |    |   |___   |       ||       ||       ||       ||   | __ |   |___ |   |_||_ \n"
"|    ___||   | |   |___ |    ___|  |       ||       ||  _    ||       ||   ||  ||    ___||    __  |\n"
"|   |    |   | |       ||   |___   | ||_|| ||   _   || | |   ||   _   ||   |_| ||   |___ |   |  | |\n"
"|___|    |___| |_______||_______|  |_|   |_||__| |__||_|  |__||__| |__||_______||_______||___|  |_|\n"
);
        printf("\n                                      === Simple File Manager ===\n");
        printf("\033[0m");
        printf("1. List files/folders\n");
        printf("2. Create folder\n");
        printf("3. Create file\n");
        printf("4. Delete file/folder\n");
        printf("5. Rename file/folder\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        flush_input();

        switch (choice) {
            case 1:
                printf("Enter path: ");
                scanf("%s", path);
                flush_input();
                list_files(path);
                break;
            case 2:
                printf("enter folder path: ");
                scanf("%s",path);
                flush_input();
                printf("Enter folder name to create: ");
                scanf("%s", path);
                flush_input();
                create_folder(path);
                break;
            case 3:
                printf("enter file path: ");
                scanf("%s",path);
                flush_input();
                printf("Enter file name to create: ");
                scanf("%s", path);
                flush_input();
                create_file(path);
                break;
            case 4:
                printf("Enter file/folder to delete: ");
                scanf("%s", path);
                flush_input();
                delete_file_or_folder(path);
                break;
            case 5:
                char old_path[256],new_path[256];
                printf("Enter current name: ");
                scanf("%s", old_path);
                flush_input();
                printf("Enter new name: ");
                scanf("%s", new_path);
                flush_input();
                rename_file_or_folder(old_path,new_path);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
    }

    return 0;
}

// ====================== FUNCTION BODIES (EMPTY) ======================

void list_files(const char *path) {
    struct dirent *de;
    DIR *dr = opendir(path);

    if(!dr){
        printf("could not find the dircetory\n");
        return;
    }

    printf("contents of %s:\n",path);
    while ((de = readdir(dr)) != NULL)
        printf("%s\n", de->d_name);

    closedir(dr);
}

void create_folder(const char *path) {
    int check = mkdir(path);

    if (check == 0) {
        printf("Folder created successfully!\n");
    }
    else {
        printf("Failed to create folder.\n");
    }
}

void create_file(const char *path) {
    FILE *fptr = fopen(path, "w");
    if (fptr != NULL) {
        printf("File created successfully!\n");
        fclose(fptr);
    } else {
        perror("Could not create file");
    }
}

void delete_file_or_folder(const char *path) {
    if (remove(path) == 0) {
        printf("removed successfully");
    }
    else if (rmdir(path) == 0) {
        printf("removed folder");
    }
    else{
        printf("colud not remove successfully %s\n",path);
    }
}

void rename_file_or_folder(const char *old_path, const char *new_path) {
    if (rename(old_path,new_path) == 0) {
        printf("renamed");
    } else{
        printf("could not rename");
    }
}

void clear_screen() {
    system("cls");
}

