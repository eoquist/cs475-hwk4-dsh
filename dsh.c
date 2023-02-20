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

// TODO: Your function definitions (declarations in dsh.h)
void execution(char *path)
{
    if (access(path, F_OK | X_OK) == 0)
    {
        // File exists and is executable! Can run!
    }
    else
    {
        // No good! File doesn't exist or is not executable!
        // Alert user and re-prompt
    }
}