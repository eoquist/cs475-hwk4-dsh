/*
 * dsh.c
 *
 *  Created on: Feb 18, 2023
 *      Author: eoquist
 */
#include "dsh.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h> // isspace


/***
 * Mode 1 (full path given): Say the user types in the full path to an executable. 
 * You know they typed a full path if their input starts begins with a '/' character! 
 * First, check to see if the given path even exists. 
*/
void fullPathGiven(int argc, char **argv, char *path)
{
    char **cmdArr = argv;
    // printf("path: %s\n",path);

    if (access(path, F_OK | X_OK) == 0)
    {
        char lastChar;
        char* lastTok = cmdArr[argc-1];
        // printf("last tok: .%s.\n",lastTok);

        // sample last valid char
        if (argc > 1 && (strcmp(lastTok, "&") == 0))
        {
            if(0 == fork()){
                argv[argc-1] = NULL; // delete & from argv tokens
                execv(path,argv);
            }
        }
        else
        {
            pid_t childID;
            childID = fork();
            if(childID == 0){
                execv(path,argv);
            }else
            {
                wait(NULL);
            }
        }
    }
    else
    {
        // https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
        printf("\033[31mError: Path %s not found!\033[0m\n", path); // i love lucas
    }
}

/**
 * Mode 2 (full path construction): This case triggers when the input does not start with a /. 
 * We need find the true location of the given command.
*/
void fullPathConstruction(int argc, char **argv, char *path)
{
    // char cwd[MAXBUF];
    char* cwd = malloc(MAXBUF *sizeof(int));
    getcwd(cwd, sizeof(cwd));

    // char tokPath[MAXBUF];
    char* tokPath = malloc(MAXBUF *sizeof(int));

    tokPath = strcat(cwd,argv[0]); 
    printf("post-cat path: %s\n",cwd);

    if (access(tokPath, F_OK | X_OK) == 0) {
        execv(tokPath,argv);
    }
    else {
        //Then there are other paths where the command may be found
        char* envPATH = getenv("PATH");
        char* delim = ":";

        int* numTok = malloc(sizeof(int));
        char** pathArr = split(envPATH, delim, numTok); 

        for(int i = 1; i < *numTok; i++){
            tokPath = strcat(cwd,argv[i]); 
            printf("post-cat path: %s\n",cwd);

            if (access(tokPath, F_OK | X_OK) == 0) {
                execv(tokPath,argv);
            }
            if(i == *numTok -1){
                // only after you’ve tried all the paths in the environment variable
                printf("\033[31mError: Command %s not found!\033[0m\n", argv[0]); // lucas is so cool
            }
        }

        // freeing stuff
		for (int i = 0; i < *numTok; i++){free(pathArr[i]);pathArr[i]=NULL;}
        free(cwd);
        free(tokPath);
		free(numTok);
		free(pathArr);
        cwd = NULL;
        tokPath = NULL;
		numTok = NULL;
		pathArr = NULL;
    }
}

/** Methods splits string into separate tokens delimited by whitespace and */
char **split(char *str, char *delim, int *numTok)
{
    char *token;
    int numToken = 0;
    char *start = str;
    char *end;

    // trim leading and trailing
    while (isspace((unsigned char)*str)){str++;}
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)){end--;}
    *(end + 1) = '\0';

    // counting is for cool people
    while (*start)
    {
        if (*start == *delim){numToken++;}
        start++;
    }
    // offset due to counting delim
    numToken++;

    // malloc -- numToken offset to add NULL
    char **cmdArr = malloc((numToken + 1) * sizeof(char *));
    for (int i = 0; i < numToken; i++)
    {
        cmdArr[i] = (char *)malloc(MAXBUF * sizeof(char));
    }

    // !!!!! how to handle if there's only one token

    // modifies cmdline
    int i = 0;
    token = strtok(str, delim); // strtok vs strtok_r ???
    while (token != NULL)
    {
        strcpy(cmdArr[i], token);
        token = strtok(NULL, delim); // NULL -> continue tokenizing
        i++;
    }
    cmdArr[i] = NULL;

    // return pointers
    *numTok = numToken;
    return cmdArr;
}