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

// Mode 1 (full path given):
void fullPathGiven(char *path, char **argv)
{
    if (access(path, F_OK | X_OK) == 0)
    {
        // File exists and is executable! Can run!

        // 1) Run in foreground: Execute the path using fork() and execv() as you learned in class.
        // The call to execv() requires the full path to the executable, which the user already gave you.

        // 2) Run in background: If the last character in a valid command is an & symbol, the command is to be
        // run in the background. This means that you’ll see dsh> being re-displayed immediately by the parent
        // (dsh) process. If the child process prints to the screen, it’ll interleave its outputs into the terminal.
    }
    else
    {
        // https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
        printf("\033[31mError: %s not found!\033[0m\n", path); // i love lucas
        // returns to main
    }
}

void fullPathConstruction()
{
    // Mode 2 (full path construction): This case triggers when the input does not start with a /.
    // Now we’ve got some work to do before we can even fork and exec! We need find the true location
    // of the given command, and we’ll use the following steps:

    // 1) First, we’ll check to see if the executable file can be found in the current working directory.
    // That is, the location of where your shell thinks you’re in. Look into using getcwd(), defined in unistd.h.
    // Concatenate the user’s input to the value of the current working directory, and see if it exists.
    // If not, then move on to the next step.
    // For instance, if I typed ls2 and my current working directory is /home/dchiu, then the first place my
    // program would be /home/dchiu/ls2. Of course, this file may or may not exist… read on!

    // 2) If the executable is found in the current working directory, then execute it and we’re done! If it
    // cannot be found in the current working directory, then there are other paths where it can be found.
    // These paths are stored in the environment variable PATH.

    // For example, a PATH might hold this value:
    // /opt/local/bin:/opt/local/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin
    // Basically, what you’re seeing here is a :-delimited string that separates all the different locations to
    // look for an executable file. Therefore, you need to split this string by :s, and concatenate the user’s
    // input to the end of each token.

    // Again, if I typed ls2, then the first location to try is /opt/local/bin/ls2, the second place to try is
    // /opt/local/sbin/ls2, and so on. As soon as you detect that a full path to the executable exists, then try
    // to run it and be done! Once you’ve tried all the paths in the environment variable, then you can output
    // a Command not found error message and reprompt for the next command.
}