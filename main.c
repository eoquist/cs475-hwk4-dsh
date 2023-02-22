/*
 * main.c
 *
 * I am the over-commenter
 *  Created on: Feb 20 2023
 *      Author: eoquist
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "dsh.h"

int main(int argc, char **argv)
{
	char *cmdline = (char *)malloc(MAXBUF * sizeof(char)); // stores user input from commmand line
	char *delim = " ";

	// user input time bb
	printf("dsh> ");
	while (fgets(cmdline, MAXBUF, stdin) != NULL)
	{
		cmdline[strcspn(cmdline, "\n")] = '\0'; // byebye \n

		// handles empty input
		if (strlen(cmdline) == 0)
		{
			printf("dsh> ");
			continue;
		}

		// sexy "built-in command" 
		if (strcmp(cmdline, "exit") == 0)
		{
			free(cmdline);
			cmdline = NULL;
			exit(0);
		}


		// Malloc
		int *numTok = malloc(sizeof(int));
		char **cmdArr = split(cmdline, delim, numTok); 

		// sexy "built-in command(s)" plural 
		if(cmdline[0] == '/'){
			fullPathGiven(*numTok,cmdArr,cmdline);
			printf("dsh> ");
			continue;
		} 
		else if (strcmp(cmdline, "cd") == 0)
		{
			char* path = cmdArr[1];
			if(path == NULL){
				chdir(getenv("HOME"));
			} 
			else{
				chdir(path); // !!! errors if path not found?
			}
			printf("dsh> ");
			continue;
		}
		else if(strcmp(cmdline, "pwd") == 0)
		{ 
			char tmp[MAXBUF];
			printf("%s\n", getcwd(tmp, sizeof(tmp)));
			printf("dsh> ");
			continue;
		}
		else
		{
			fullPathConstruction(*numTok, cmdArr, cmdline);
			printf("dsh> ");
			continue;
		}

		printf("dsh> ");

		// freeing stuff
		for (int i = 0; i < *numTok; i++){free(cmdArr[i]);cmdArr[i]=NULL;}
		free(numTok);
		free(cmdArr);
		numTok = NULL;
		cmdArr = NULL;
	}
	free(cmdline);
	cmdline = NULL;
	printf("funni\n");
	// run badapple here
	// add the binary main to this folder and make sure you hide the binary in gitignore
	return 0;
}