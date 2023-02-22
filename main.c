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
#include <ctype.h> // isspace
#include "dsh.h"

int main(int argc, char **argv)
{
	char *cmdline = (char *)malloc(MAXBUF * sizeof(char)); // stores user input from commmand line
	char *delim = " ";

	// As soon as dsh starts, repeatedly provide the user with prompt : 'dsh> '
	printf("dsh> ");
	while (fgets(cmdline, MAXBUF, stdin) != NULL)
	{
		printf("this is your input: %s\n", cmdline);
		// cmdline[strcspn(cmdline, "\n")] = '\0'; // honestly not sure if this does anything

		// sexy "built-in commands"
		if (strcmp(cmdline, "exit") == 0)
		{
			free(cmdline);
			exit(0); // 1 = failure
		}
		else if (strcmp(cmdline, "pwd") == 0)
		{
			// make sure its printing the right working dir AFTER running other methods
			printf("%s\n", getcwd(cmdline, sizeof(cmdline)));
			continue;
			// this looks weird af in valgrind compared to dshSol
		}

		char **cmdArr = split(cmdline, delim);

		// print out all the tokens
		int i = 0;
		while (cmdArr[i] != NULL)
		{
			printf("token #%d: %s\n", i, cmdArr[i]);
			// check "/" and "cd" and redo "pwd" and "exit"
			i++;
		}

		printf("dsh> ");

		// free(cmdline);
	}
	free(cmdline);
	return 0;
}