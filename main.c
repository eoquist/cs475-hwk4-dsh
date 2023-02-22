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
			exit(0); // 1 = failure
		}

		int *numTok = (int *)malloc(sizeof(int));
		char **cmdArr = split(cmdline, delim, numTok); 

		// check "/" and "cd" and redo "pwd"



		printf("dsh> ");

		// freeing stuff
		for (int i = 0; i < *numTok; i++){free(cmdArr[i]);}
		free(numTok);
		free(cmdArr);
	}
	free(cmdline);
	printf("funni\n");
	return 0;
}