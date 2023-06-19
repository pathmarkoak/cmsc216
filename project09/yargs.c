/* Honor Pledge: I pledge on my honor that I have not given
   or received any unauthorized assitance on this examination
   or assginment.

   Name: Omkar Pathak
   TerpConnect login ID: omkarp07
   University ID number: 119272961
   Discussion Section Number: 0206

   The purpose of this project is to simulate the UNIX xargs utility; this
   simulation is called yargs. A main function in this file is used to
   simulate the function of yargs; a small utility function free_string_array
   is used to free all of the contents of the pointer to the array of strings
   passed in. This utility function is used to free dynamically-allocated
   memory used in the main function. The primary function of yargs is to
   operate on a target program that is given target arguments, as well as
   standard input. If -n is passed in as input, the progrma prints the
   commands passed in; otherwise, the program executes the target program
   along with the target arguments and standard input passed. This program
   uses the main function arguments argc and argv to capture input passed in.
   Furthermore, C standard input/output and system calls are used throughout
   the main function to simulate xargs.
 */

#include "safe-fork.h"
#include "split.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Function prototype for free_string_array utility function, which takes in
 * an array as input and frees the contents of the argument array, as well as
 * the array itself.
 */
static void free_string_array(char **const array);

/* This main function takes in arguments argc and argv, which are used to
 * capture the command-line arguments used with yargs.c. This function is used
 * to simulate the function of xargs.c. C standard input/output is used to
 * capture and analyze the standard input and comamnd line arguemnts passed
 * into yargs.c. System calls, such as execvp, safe_fork() (an alternative to
 * fork() to prevent fork bombs), and exit()) are used extensively to simulate
 * the function of xargs. If any system calls fail, this is handled
 * accordingly */
int main(int argc, char *argv[]) {
    /* Declaring various variables (and instantiating some to be used
     * throughout the function ) */
    int i = 0;
    int j = 0;
    int k = 0;
    int status, to_print, program_num, number_of_args;
    pid_t child_pid;
    char buffer[10000];
    char **word_array;
    char **target_arguments;
    char **combined_arguments;

    /* If argc is greater than 2, to_print serves as a boolean and serves
     * to determine whether the priting will occur or not. Similarlyl,
     * program_num determines when to start in argv. */
    if (argc >= 2) {
        if (strcmp("-n", argv[1]) != 0) {
            to_print = 0;
            program_num = 1;
        } else {
            to_print = 1;
            program_num = 2;
        }
    }

    /* Setting target_arguments at the start point of program_num in argv, and
     * setting num_arguments accordingly*/
    target_arguments = &argv[program_num];
    number_of_args = argc - program_num;

    /* Reading until the end of input, and continuing simulation of function
     * here*/
    while (fgets(buffer, 10000, stdin)) {
        /* Setting words using split with buffer as an argument */
        word_array = split(buffer);

        /* Creating fork for child process*/
        child_pid = safe_fork();

        if (child_pid == 0) {
            /* Finding last index of words to find last index of words */
            while (word_array[i] != NULL) {
                i++;
            }

            /* As combined arguments is used to hold all of the arguments that
             * the file will have, combined_arguments is
             * dynamically-allocated based on num_arguments plus the number of
             * elements in words plus 1 */
            combined_arguments =
                malloc(sizeof(char *) * (i + 1 + number_of_args));

            /* Then, using two for-loops, combined_arguments is filled based
             * on the contents of target_arguments and words. This is why
             * there are two for loop. */
            for (j = 0; j < number_of_args; j++) {
                combined_arguments[k] = target_arguments[j];
                k++;
            }

            for (j = 0; word_array[j] != NULL; j++) {
                combined_arguments[k] = word_array[j];
                k++;
            }

            /* Finally, the last element of combined_arguments is set to null
             * to match the argument requirements for execvp */
            combined_arguments[k] = NULL;

            /* If -n is equal to zero, the process of program execution
             * continues using execvp, perror, and a call to free_string_array
             * and an exit(255) if there is an error */
            if (to_print == 0) {
                execvp(target_arguments[0], combined_arguments);
                perror("The target program failed");
                free_string_array(word_array);
                exit(255);

                /* Otherwise, the contents of the arguments is printed and the
                 * process exists with exit status 0, as this is necessary.
                 * Then, free_string_array is called on word_array to free the
                 * contents of word_array */
            } else {
                for (j = 0; j < k; j++) {
                    if (j != k - 1) {
                        printf("%s ", combined_arguments[j]);
                    } else {
                        printf("%s\n", combined_arguments[j]);
                    }
                }
                free_string_array(word_array);
                free(combined_arguments);
                exit(0);
            }

            /* If the fork was not able to be done successfully, this is
             * handled by freeing words and exiting with status EXIT_FAILURE
             */
        } else if (child_pid == -1) {
            perror("The fork unfortunately failed.");
            free_string_array(word_array);
            exit(EXIT_FAILURE);

            /* Otherwise, if the fork was done succcessfully, but the wait
             * failed, words is freed and the program exists with exit status
             * EXIT_FAILURE */
        } else {
            if (waitpid(child_pid, &status, 0) == -1) {
                perror("The waitpid system call failed.");
                free_string_array(word_array);
                exit(EXIT_FAILURE);
            }

            /* If the exit does not happen successfully, free_string_array is
             * once again called on words and the process exits with
             * WEXITSTATUS(status) */
            if (WIFEXITED(status) && WEXITSTATUS(status)) {
                free_string_array(word_array);
                exit(WEXITSTATUS(status));
            }
        }
        /* Finally, free_string_array is called on words to free itself and
         * its contents */
        free_string_array(word_array);
    }
    return 0;
}

/* free_string_array is a utility function that takes in an array argument and
 * frees all of the dynamically-allocated memory occupied by this array. This
 * array does modify the pointer passed in by freeing its
 * dynamically-allocated memory, and does not have a return value. */
static void free_string_array(char **const array) {
    int i = 0;

    /* Freeing every element in names, and then names itself*/
    if (array != NULL) {
        while (array[i] != NULL) {
            free(array[i]);
            i++;
        }
        free(array);
    }
}
