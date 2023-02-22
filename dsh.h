/*
 * dsh.h
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

#define MAXBUF 256
#define MAXARGS 50 // arbitrary bc I don't wanna do realloc rn

void fullPathGiven(int argc, char **argv, char *path);
void fullPathConstruction(int argc, char **argv, char *path);
char **split(char *str, char *delim, int* numTok);