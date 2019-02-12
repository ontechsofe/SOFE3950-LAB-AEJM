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
 *      - clr
 *      - dir
 *      - environ
 *      - echo
 *      - help
 *      - pause
 *      - quit
 * 
 **/

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here
// char* tokenizeString(char* inputString, int numArgs) {
//     char* token;
//     const char *args[numArgs];
//     // Grabbing the first token - e.g. First Argument
//     token = strtok(inputString, " ");
//     while (token != NULL) {
//         args[i] = strtok(inputString, " ");        
//     }
//     return args;
// }

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
        sscanf(buffer, "%s\n", &command); 
        token = strtok(command, " ");
        printf("\e[1;95m%s\e[0m\n", token);        

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(token, "cd") == 0) {
            token = strtok(buffer, " ");
            token = strtok(NULL, " ");
            chdir(token);
        } else if (strcmp(token, "dir") == 0) {
            DIR *d;
            struct dirent *directory;
            d = opendir(".");
            if(d) {
                while((directory = readdir(d)) != NULL) {
                    int dirType = 0;
                    sscanf(directory->d_type, "%d", )
                    printf("\n%d\n", directory->d_type);
                    if (directory->d_type == 4) {
                        printf("\033[0;34m");
                    } else if(directory->d_type == 8) {
                        printf("\033[0;36m");
                    }
                    printf("%s\t%d\e[0m\n", directory->d_name, directory->d_type);
                }
                closedir(d);
            }
        } else if (strcmp(token, "environ") == 0) {
            extern char **environ;
            int i = 0;
            while (environ[i]) {
                printf("%s\n", environ[i++]);
            }
        } else if (strcmp(token, "help") == 0){
            printf("Please try entering something like: command [args]\n");
        } else if (strcmp(token, "quit") == 0) {
            printf("Tanks for barking vit SES!\nGOOT BYE!\n");
            return EXIT_SUCCESS;
        } else if (strcmp(token, "pause") == 0){
            //String test;
            //while (1){
            //if (scanf(%s, %test) == 0){
            // break;
            //}
            //}
        } else {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
        printShellLineStart();
    }   
    return EXIT_SUCCESS;
}
