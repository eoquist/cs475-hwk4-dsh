/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
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

	// As soon as dsh starts, repeatedly provide the user with prompt : 'dsh> '
	printf("dsh> ");
	while (fgets(cmdline, MAXBUF, stdin) != NULL)
	{
		cmdline[strcspn(cmdline, "\n")] = '\0'; // handles stdin \n
		printf("this is your input: .%s.\n", cmdline);

		// sexy "built-in commands" that may get moved elsewhere
		if (strcmp(cmdline, "exit") == 0)
		{
			free(cmdline);
			exit(0); // 1 = failure
		}

		int* numTok = (int*)malloc(sizeof(int));
		char **cmdArr = split(cmdline, delim,numTok); // byte lost here when exiting after cmdarr stuff malloc'd
		

		// print out all the tokens
		int i = 0;
		while (cmdArr[i] != NULL)
		{
			printf("token #%d: %s\n", i, cmdArr[i]);
			// check "/" and "cd" and redo "pwd" and "exit"
			i++;
		}

		printf("dsh> ");

		// free
		for (i = 0; i < *numTok; i++)
		{
			free(cmdArr[i]);
		}
		free(cmdArr);
	}
	free(cmdline);
	return 0;
}