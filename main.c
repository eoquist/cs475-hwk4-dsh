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
	const char delim[2] = " ";
	char *token;
	int numTokens = 0;

	// As soon as dsh starts, repeatedly provide the user with prompt : 'dsh> '
	printf("dsh> ");

	while (fgets(cmdline, MAXBUF, stdin) != NULL)
	{
		cmdline[strcspn(cmdline, "\n")] = '\0'; // honestly not sure if this does anything

		if (strcmp(cmdline, "exit") == 0)
		{
			// boo = 0;
			printf("Program exited.");
			free(cmdline);
			exit(0); // success exit
		}
		else
		{
			// will double print if stdin more than max buff
			// the sol has stack smashing detected *** ?????

			printf("dsh> ");

			// GET LINE OF INPUT ...... does token start with '/' ?
			//		Y -- does file exist?
			//			Y -- fork() and exec()
			//				IF COMMAND ENDS WITH & --> run in bg --> start at new input
			//				ELSE WAIT --> start at new input
			//			N -- command not found error
			//
			//		N -- is the command built in?
			//			Y -- run internal function
			//			N -- split PATH env var by :  ... more paths?
			//				Y -- concat next path with command
			//					if path exists, fork() exec()
			//						IF COMMAND ENDS WITH & --> run in bg --> start at new input
			//						ELSE WAIT
			//					else check for more paths
			//				N -- command not found error

			// strtok vs strtok_r
			token = strtok(cmdline, delim);
			numTokens++;
			while (token != NULL)
			{
				char firstElem = token[0];
				if (strcmp(firstElem, '/') == 0)
				{
					// mode 1 needs to be done
					// make sure that you free(cmdline) before mode 1 is run bc it can call main again
				}
				printf(".%s.", token);		 // testing purposes
				token = strtok(NULL, delim); // NULL -> continue tokenizing
			}
			// :)
			char **cmdArr;
			cmdArr = malloc(numTokens * sizeof(char *));
			for (int i = 0; i < numTokens; i++)
			{
				cmdArr[i] = malloc((maximum_size_of_token + 1) * sizeof(char));
				strcpy(cmdArr[i], the_token_itself[i]);
			}
			exit(1); // failure exit
		}
	}
	free(cmdline);
	return 0;
}