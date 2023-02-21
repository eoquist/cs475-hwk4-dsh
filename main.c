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
	char **cmdArr = malloc(MAXARGS * sizeof(char *));
	// :)
	char *cmdline = (char *)malloc(MAXBUF * sizeof(char)); // stores user input from commmand line
	char tmp[MAXBUF];
	const char delim[2] = " ";
	char *token;

	// As soon as dsh starts, repeatedly provide the user with prompt : 'dsh> '
	printf("dsh> ");
	while (fgets(cmdline, MAXBUF, stdin) != NULL)
	{
		cmdline[strcspn(cmdline, "\n")] = '\0'; // honestly not sure if this does anything

		// do you like my "built-in commands"
		if (strcmp(cmdline, "exit") == 0)
		{
			printf("Program exited.");
			free(cmdline);
			exit(0); // success exit
		}
		else if (strcmp(cmdline, "pwd") == 0)
		{
			// make sure its printing the right working dir
			printf("%s\n", getcwd(tmp, sizeof(tmp)));
		}
		else
		{
			// will double print if stdin more than max buff
			// dshSol has stack smashing detected ***
			printf("dsh> ");

			int i = 0;
			token = strtok(cmdline, delim); // strtok vs strtok_r
			while (token != NULL)
			{
				char firstElem = token[0];
				cmdArr[i] = malloc((MAXBUF) * sizeof(char));

				if (strcmp(token, "cd") == 0)
				{
					// if next token doesnt exist then cd to user's home directory
					//		chdir() and getenv()

					// otherwise get next token [path] and change cwd to that OPTIONALLY given path
				}
				if (strcmp(&firstElem, "/") == 0)
				{
					// mode 1 needs to be done

					// get all remaining tokens
					strcpy(cmdArr[i], token); // make sure this is not the "/" token
					i++;

					// make sure that you free(cmdline) before mode 1 is run bc it can call main again
				}
				token = strtok(NULL, delim); // NULL -> continue tokenizing
			}

			for (int j = 0; j < MAXARGS; j++)
			{
				free(cmdArr[j]);
			}
			free(cmdArr);
			exit(1); // failure exit
		}
	}
	free(cmdline);
	return 0;
}