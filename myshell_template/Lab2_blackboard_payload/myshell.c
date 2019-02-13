/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2019
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

/**
 * Must support these commands:
 *      - cd        
 *      - clr       *
 *      - dir       
 *      - environ   *
 *      - echo      
 *      - help      
 *      - pause     *
 *      - quit      *
 * 
 **/

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

void printShellLineStart() {
    char cwd[BUFFER_LEN];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("\n\e[1;32mseshell\e[1;31m@\e[1;34m%s 😎  \e[5;32;40m> \e[0m", cwd);
    } else {
        perror("getcwd() error");
    }
}

int main(int argc, char *argv[]) {
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = {0};
    char command[BUFFER_LEN] = {0};
    char arg[BUFFER_LEN] = {0};

    // Parse the commands provided using argc and argv

    printShellLineStart();
    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        char* token;
        // Grabs the first token, the command  
        printf("[%s]", &buffer);
        sscanf(buffer, "%s\n", &command); 
        if (command == "") {
            break;
        }
        token = strtok(command, " ");
        // printf("\e[1;95m%s\e[0m\n", token);        

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(token, "cd") == 0) {
            token = strtok(buffer, " ");
            token = strtok(NULL, " ");
            sscanf(token, "%s\n", token);
            // printf("directory = [%s]\n", token);
            if (chdir(token) != 0) {
                perror("cannot cd");
            }
        } else if (strcmp(token, "dir") == 0 || strcmp(token, "ls") == 0) {
            DIR *d;
            struct dirent *directory;
            d = opendir(".");
            if(d) {
                while((directory = readdir(d)) != NULL) {
                    if (directory->d_type == 4) {
                        printf("\033[0;34m");
                    } else if(directory->d_type == 8) {
                        printf("\033[0;36m");
                    }
                    printf("%s\e[0m\n", directory->d_name);
                }
                closedir(d);
            }
        } else if (strcmp(token, "environ") == 0) {
            extern char **environ;
            int i = 0;
            while (environ[i]) { printf("%s\n", environ[i++]); }
        } else if (strcmp(token, "clear") == 0) {
            printf("\033[2J\033[1;1H");
            ftruncate(1,0);
        } else if (strcmp(token, "quit") == 0 || strcmp(token, "exit") == 0) {
            printf("Tanks for barking vit SES!\nGOOT BYE!\n");
            return EXIT_SUCCESS;
        } else if (strcmp(token, "pause") == 0) {
            char st[BUFFER_LEN];
            printf("Paused! ... Press Enter to continue.");
            fgets(st,20,stdin);
        } else if (strcmp(token, "help") == 0) {
            printf("Please try entering something like: command [args]\n");
        } else {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
        printShellLineStart();
        buffer[0] = '\0';
    }   
    return EXIT_SUCCESS;
}



