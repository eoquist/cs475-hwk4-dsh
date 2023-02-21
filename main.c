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
	// int boo = 1;
	// const char delim[2] = " ";
	// char *token;

	// As soon as dsh starts, it should repeatedly provide the user with a command - line prompt : 'dsh> ' while ((cmdline[0] != endCondition))
	// while (boo == 1)
	// {
	printf("dsh> ");

	while (fgets(cmdline, MAXBUF, stdin) != NULL)
	{
		// cmdline[strcspn(cmdline, "\n")] = '\0';
		// printf("yay");

		// cmdline = strtok(cmdline, delim);
		// while (token != NULL)
		// {
		// 	printf(".%s.", token);
		// 	token = strtok(NULL, delim); // NULL -> continue tokenizing
		// }

		if (strcmp(cmdline, "exit") == 0)
		{
			// boo = 0;
			exit(0); // success exit
			printf("Program exited.");
		}
		else
		{
			// will double print if stdin more than max buff
			// use stack smashing detected ***
			printf("dsh> ");
		}
	}
	free(cmdline);
	return 0;
	// }
}