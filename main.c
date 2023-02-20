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
	char cmdline[MAXBUF]; // stores user input from commmand line
	cmdline[0] = '\0';
	char *line = (char *)malloc(MAXBUF);
	int boo = 1;

	strcpy(line, "  abc def  ");
	strcpy(line, trim(line));
	free(line);

	char endCondition = '\n';

	// As soon as dsh starts, it should repeatedly provide the user with a command - line prompt : 'dsh> ' while ((cmdline[0] != endCondition))
	while (boo == 1)
	{
		printf("dsh> ");

		// handles stdin \n
		if (fgets(cmdline, MAXBUF, stdin) != NULL)
		{
			line[strcspn(line, "\n")] = '\0';
		}

		if (cmdline[0] != endCondition)
		{
			// Once you have the input line, you should trim it (that is, remove all preceding and trailing white space).
		}
		else
		{
			printf("\ndsh> ");
		}
		boo = 0;
	}
	return 0;
}

// handle leading and trailing whitespace as well as \n
// https://stackoverflow.com/questions/56218002/how-to-remove-leading-trailing-white-spaces-in-c-without-memory-leak
char *trim(char *str)
{
	char *end;
	while (isspace((unsigned char)*str))
		str++;
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
	{
		end--;
		*end = '\0';
	}
	return (str);
}