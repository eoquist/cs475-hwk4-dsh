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
void fullPathGiven(char *path)
{
    if (access(path, F_OK | X_OK) == 0)
    {
        // File exists and is executable! Can run!

        // If the executable is found, then there are two further options for execution:

        // 1) Run in foreground: Execute the path using fork() and execv() as you learned in class.
        // The call to execv() requires the full path to the executable, which the user already gave you.
        // Commands may have an arbitrary number of arguments that follow it, which are delimited by whitespace.
        // You’ll need to input the command line arguments into an array of strings, and pass it along to execv().
        // When running a process in the foreground, the parent process (that is, dsh) must wait() for the child
        // process to finish. Therefore, you would not expect to see the dsh> shell prompt again until the child
        // process terminates. This is the usual mode of execution when you’re on the terminal!

        // 2) Run in background: If the last character in a valid command is an & symbol, it indicates that the
        // command is to be run in the background. In other words, when the shell forks a child, it should not wait
        // for the child to exit. After forking, the OS will commence running the new process concurrently with dsh
        // (and all other processes). This means that you’ll see dsh> being re-displayed immediately by the parent
        // (dsh) process. If the child process prints to the screen, it’ll interleave its outputs into the terminal.
        // This mode is useful when you’re multitasking, and need to spin off a program, but get your command - line
        // right back so you can run other programs !
    }
    else
    {
        // https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
        printf("\033[31mError: %s not found!\033[0m\n", path); // love Lucas

        // Alert user and re-prompt
        main();
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

// Some commands are not meant to invoke another program. Instead, they are to be handled directly by the shell by
// calling functions that you built-in. For example, when a user inputs exit, your shell is not supposed to attempt
// to find an executable named exit in the user’s PATH! In this case, dsh should simply terminate by exiting the loop.
// These special commands are called “builtins.”

// Here is a list of built-in commands that David shell needs to support.
//     exit should exit dsh.
//     pwd should print the current working directory. Look into getcwd(), defined in unistd.h.
//     cd [path] should change the current working directory to the optionally given path. If path is not given, then dsh
//         should change the working directory to the user’s home directory, stored in the environment variable HOME. Look into the chdir() function, defined in unistd.h.