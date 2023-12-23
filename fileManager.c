#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h> // Directory Entry
#include <sys/stat.h> // Include for mkdir()

// Function to list all files and directories in the current directory
void listFiles() {
    struct dirent *de;  // Pointer for directory entry 

    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir(".");

    if (dr == NULL) { // opendir returns NULL if couldn't open directory
        printf("Could not open current directory" );
        return;
    }

    // Referencing each directory entry
    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);

    closedir(dr);
}

// Function to change the current working directory
void changeDirectory(const char *path) {
    if (chdir(path) != 0) {
        perror("chdir"); // Print error if chdir fails
    }
}

// Function to move to the outer (parent) directory
void moveToParentDirectory() {
    if (chdir("..") != 0) {
        perror("chdir"); // Print error if chdir fails
    }
}

// Function to print the current working directory
void printWorkingDirectory() {
    char cwd[1024]; // Array to hold the current directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd"); // Print error if getcwd fails
    }
}

// Function to create a new file
void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error in creating file");
        return;
    }
    fclose(file);
    printf("File created successfully: %s\n", filename);
}

// Function to delete a file
void deleteFile(const char *filename) {
    if (remove(filename) != 0) {
        perror("Error in deleting file");
    } else {
        printf("File deleted successfully: %s\n", filename);
    }
}

// Function to rename a file
void renameFile(const char *oldFilename, const char *newFilename) {
    if (rename(oldFilename, newFilename) != 0) {
        perror("Error in renaming file");
    } else {
        printf("File renamed successfully from %s to %s\n", oldFilename, newFilename);
    }
}

// Function to create a new directory
void createDirectory(const char *dirname) {
    if (mkdir(dirname, 0777) != 0) { // 0777 permissions allow read, write, execute for user, group, others
        perror("Error in creating directory");
    } else {
        printf("Directory created successfully: %s\n", dirname);
    }
}

// Function to remove a directory
void removeDirectory(const char *dirname) {
    if (rmdir(dirname) != 0) {
        perror("Error in removing directory");
    } else {
        printf("Directory removed successfully: %s\n", dirname);
    }
}

void displayHelp() {
    printf("Available commands:\n");
    printf("  ls       - List files and directories in the current directory\n");
    printf("  cd [dir] - Change the current directory to [dir]\n");
    printf("  pwd      - Print the current working directory\n");
    printf("  create [filename] - Create a new file named [filename]\n");
    printf("  delete [filename] - Delete the file named [filename]\n");
    printf("  rename [oldname] [newname] - Rename a file from [oldname] to [newname]\n");
    printf("  mkdir [dirname] - Create a new directory named [dirname]\n");
    printf("  rmdir [dirname] - Remove the directory named [dirname]\n");
    printf("  back     - Move to the parent directory\n");
    printf("  exit     - Exit the file manager\n");
    printf("  help     - Display this help information\n");
}

// Main function: Command line interface for file management
int main() {
    char command[256];
    char *token;
    char *rest;

    // Continuous loop for command line interaction
    while (1) {
        printf("filemanager> "); // Command prompt
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("Error reading input\n");
            continue; // Skip to next iteration on input error
        }
        command[strcspn(command, "\n")] = 0; // Remove newline character

        // Tokenize the input command
        rest = command;
        token = strtok_r(rest, " ", &rest);

        // Process the command
        if (token == NULL) {
            continue; // Skip to next iteration if command is empty
        } else if (strcmp(token, "ls") == 0) {
            listFiles();
        } else if (strcmp(token, "exit") == 0) {
            break; // Exit the program
        } else if (strcmp(token, "pwd") == 0) {
            printWorkingDirectory();
        } else if (strcmp(token, "cd") == 0) {
            // Handling 'cd' command
            token = strtok_r(NULL, " ", &rest);
            if (token != NULL) {
                changeDirectory(token);
            } else {
                printf("cd command requires a directory name\n");
            }
        }  else if (strcmp(token, "back") == 0) {
            moveToParentDirectory();
        }  else if (strcmp(token, "create") == 0) {
            // Handling 'create' command
            token = strtok_r(NULL, " ", &rest);
            if (token != NULL) {
                createFile(token);
            } else {
                printf("create command requires a filename\n");
            }
        } else if (strcmp(token, "delete") == 0) {
            // Handling 'delete' command
            token = strtok_r(NULL, " ", &rest);
            if (token != NULL) {
                deleteFile(token);
            } else {
                printf("delete command requires a filename\n");
            }
        } else if (strcmp(token, "rename") == 0) {
            // Handling 'rename' command
            char *oldFilename = strtok_r(NULL, " ", &rest);
            char *newFilename = strtok_r(NULL, " ", &rest);
            if (oldFilename != NULL && newFilename != NULL) {
                renameFile(oldFilename, newFilename);
            } else {
                printf("rename command requires two filenames\n");
            }
        } else if (strcmp(token, "mkdir") == 0) {
            // Handling 'mkdir' command
            token = strtok_r(NULL, " ", &rest);
            if (token != NULL) {
                createDirectory(token);
            } else {
                printf("mkdir command requires a directory name\n");
            }
        } else if (strcmp(token, "rmdir") == 0) {
            // Handling 'rmdir' command
            token = strtok_r(NULL, " ", &rest);
            if (token != NULL) {
                removeDirectory(token);
            } else {
                printf("rmdir command requires a directory name\n");
            }
        } else if (strcmp(token, "help") == 0) {
            displayHelp();
        } else {
            printf("Unknown command\n");
        }
    }

    return 0;
}
