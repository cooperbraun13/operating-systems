/*
Cooper Braun
CPSC-346-01
Project 3
10/14/2025
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h> // for isdigit

#define MAX_LINE 80    // 80 chars per line, per command, should be enough
#define MAX_COMMANDS 9 // size of history

char history[MAX_COMMANDS][MAX_LINE]; // the array used to store history commands
char display_history[MAX_COMMANDS][MAX_LINE];
// the array used for "printf" to display history nicely. Remove special characters like "\n" or "\0"

int command_count = 0;
int history_start = 0; // index of the oldest entry in the circular buffer

/**
 * Add the most recent command to the history.
 */

void addtohistory(char inputBuffer[])
{

  // update array"history": add the command to history, strcpy(str1,str2);
  /*
  Keep a circular buffer of size MAX_COMMANDS.
  When command_count < MAX_COMMANDS: append at (history_start + command_count) % MAX_COMMANDS
  When full: overwrite the oldest (at history_start) and advance history_start
  */
  int index;
  if (command_count < MAX_COMMANDS)
  {
    index = (history_start + command_count) % MAX_COMMANDS;
    command_count++;
  }
  else
  {
    index = history_start;                              // overwrite oldest
    history_start = (history_start + 1) % MAX_COMMANDS; // advance oldest
  }

  // store raw command (including any newline that may still be present here)
  strcpy(history[index], inputBuffer);

  // update array"display_history": remove characters like '\n', '\0' in order to display nicely
  /*
  Build a printable version without trailing newline.
  Copy until '\0' but skip '\n' (and '\r' just in case).
  */
  {
    size_t di = 0;
    for (size_t si = 0; inputBuffer[si] != '\0' && di + 1 < MAX_LINE; ++si)
    {
      char c = inputBuffer[si];
      if (c == '\n' || c == '\r')
      {
        continue; // drop newlines
      }
      display_history[index][di++] = c;
    }
    display_history[index][di] = '\0';
  }

  return;
}

/*
the setup function below will not return any value, but it will just: read
in the next command line; separate it into distinct arguments (using blanks as
delimiters), and set the args array entries to point to the beginning of what
will become null-terminated, C-style strings.
*/

int setup(char inputBuffer[], char *args[], int *background)
{
  int length;         // number of characters in the command line
  int i;              // loop index for accessing inputBuffer array
  int command_number; // index of requested command number

  // define your local variables here
  int argIndex = 0; // next free slot in args[]
  int inToken = 0;  // flag to mark beginning of each arg string
  *background = 0;  // reset background flag each call

  // read what the user enters on the command line
  do
  {
    printf("osh>");
    fflush(stdout);
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
  } while (inputBuffer[0] == '\n'); // swallow newline characters

  if (length == 0)
    exit(0); // ^d was entered, end of user command stream

  if ((length < 0))
  {
    perror("error reading the command");
    exit(-1); // terminate with error code of -1
  }

  /**
   * Check if they are using history
   */

  // fill in your code here Part II, if the user input is to repeat some history commands
  if (inputBuffer[0] == '!')
  {
    // a) check whether there is no history
    if (command_count == 0)
    {
      printf("no commands in history.\n");
      return 1; // keep shell running and prompt again
    }

    // b) "!!" -> most recent command
    if (inputBuffer[1] == '!')
    {
      // most recent index in circular buffer
      int idx = (history_start + command_count - 1) % MAX_COMMANDS;
      // replace inputBuffer with the most recent history command
      strncpy(inputBuffer, history[idx], MAX_LINE - 1);
      inputBuffer[MAX_LINE - 1] = '\0';
      length = (int)strlen(inputBuffer);
      // echo the command per spec
      printf("%s", display_history[idx]);
      printf("\n");
    }
    // c) "!N" where N is a digit for the Nth most recent command
    else if (isdigit((unsigned char)inputBuffer[1]) && inputBuffer[2] == '\n')
    {
      int N = inputBuffer[1] - '0';
      if (N <= 0 || N > command_count || N > MAX_COMMANDS)
      {
        printf("no such command in history.\n");
        return 1; // keep shell running
      }
      int idx = (history_start + command_count - N) % MAX_COMMANDS;
      strncpy(inputBuffer, history[idx], MAX_LINE - 1);
      inputBuffer[MAX_LINE - 1] = '\0';
      length = (int)strlen(inputBuffer);
      // echo the command per spec
      printf("%s", display_history[idx]);
      printf("\n");
    }
    else
    {
      // invalid history recall form
      printf("no such command in history.\n");
      return 1; // keep shell running
    }
  }

  /*
  Add the command to the history
  */
  // fill in your code here Part II, add the following line for PartII
  addtohistory(inputBuffer);

  /*
  Parse the contents of inputBuffer
  */

  for (i = 0; i < length; i++)
  {
    // examine every character in the inputBuffer

    switch (inputBuffer[i])
    {
    case ' ':
    case '\t': // argument separators
      // replace whitespace with '\0' to terminate current arg string
      inputBuffer[i] = '\0';
      inToken = 0; // next non-space begins a new argument
      break;

    case '\n': // should be the final char examined
      // replace newline with '\0' to end last argument
      inputBuffer[i] = '\0';
      args[argIndex] = NULL; // no more arguments to this command
      break;

    default: // some other character
      /*
      args[i] is a pointer to a string, its value is the address of the first charater of that string
      You want to track the location of the beginning character of each string.
      The location is the first character, which is not ' ', not '\t', and not '\n'
      You also need check "&". If '&' is detected, setup background flag.
      */
      if (inputBuffer[i] == '&')
      {
        *background = 1;       // mark background execution
        inputBuffer[i] = '\0'; // do not include '&' in args
        inToken = 0;
      }
      else if (!inToken)
      {
        args[argIndex++] = &inputBuffer[i]; // start of a new argument
        inToken = 1;
      }
      // else still inside a token, so keep scanning
      break;

    } // end of switch
  } // end of for

  /*
  Here you finish parsing the input.
  There is one more thing to assure. If we get '&', make sure you don't enter it in the args array
  */

  args[argIndex] = NULL; // ensure NULL termination for execvp

  return 1;

} // end of setup routine

int main(void)
{
  char inputBuffer[MAX_LINE];   // buffer to hold the command entered
  int background;               // equals 1 if a command is followed by '&'
  char *args[MAX_LINE / 2 + 1]; // command line (of 80) has max of 40 arguments
  pid_t child;                  // process id of the child process

  // define your local variables here, at the beginning of your program
  int shouldrun = 1;

  while (shouldrun)
  { // program terminates normally inside setup

    background = 0;

    shouldrun = setup(inputBuffer, args, &background); // get next command

    // fill in your code here Part I
    /*
    if the user typed in "exit", the shell program will return (or terminate).
    Call strncmp(str1,str1,count). The function call will return 0 if str1 == str2.
    "count" is the number of characters we use to compare.
    */
    if (strncmp(inputBuffer, "exit", 4) == 0 && (inputBuffer[4] == '\0'))
    {
      return 0; // terminates shell
    }

    // fill in your code here Part II
    /* if the user typed in "history", the shell program will display the history commands.
     * you will use "printf" to print the display_history
     * after you display all the array, this command is done.
     * Your program should go to read again, which means calling the "setup" function.
     */

    if (shouldrun)
    {

      // creates a duplicate process!
      // here fill in your code
      /*
      pid < 0, it is an error
      pid == 0, it is the child process. use the system call execvp(args[0],args);
      pid > 0, it is the parent. Here you need consider it is foreground or background
      */
      child = fork();

      if (child < 0)
      {
        perror("fork failed");
        continue;
      }
      else if (child == 0)
      {
        // child: replace with requested program
        execvp(args[0], args);
        // if execvp returns, an error occurred
        perror("execvp failed");
        _exit(1);
      }
      else
      {
        // parent: wait for child if foreground, otherwise immediately reprompt
        if (background == 0)
        {
          // foreground: wait until child completes
          if (waitpid(child, NULL, 0) < 0)
          {
            perror("waitpid failed");
          }
        }
        else
        {
          // background: do not wait
          printf("[background pid %d]\n", child);
          fflush(stdout);
        }
      }
    }
  }

  return 0;
}
