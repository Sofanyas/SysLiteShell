# SysLiteShell
SysLiteShell is a lightweight shell written in C. It includes three source code files: 'csapp.h', 'csapp.c', and 'shellex.c', along with a Makefile for compilation.

## Makefile 
The Makefile for SysLiteShell provides a convenient way to compile and manage the project. It includes rules for building the executable, cleaning up generated files, and ensuring a smooth development workflow.

### Requirements
To build and run SysLiteShell, you will need:

- A C compiler (e.g., GCC)
- 'make'

### Usage
To compile SysLiteShell, run the following command:
```
make
```
This will compile the program using the 'gcc' compiler and create an executable file named 'sh257'.

To execute SysLiteShell, use the following command:
```
./sh257
```

To remove the executable and object files, use the following command:
```
make clean
```
This will remove the 'sh257' executable as well as any object files created during compilation.


## Shellex 
Implements the main functionality of a simple shell program. It includes the definition of the main function, which serves as the entry point for the program, as well as auxiliary functions such as eval and builtin_command for command evaluation and built-in command handling. The file enables the execution of shell commands, manages foreground and background processes, and includes functionality for built-in commands like exit, pid, ppid, help, and cd.

### Requirements 
Needs access to the csapp.h header file.

### Usage

```
int main(int argc, char** argv)
```
The main function that initiates the shell program, reads commands from the user, and invokes the evaluation of those commands.

```
void eval(char *cmdline)
```
Evaluates a command line, forks a child process to execute non-built-in commands, and manages foreground and background execution.

```
int builtin_command(char **argv)
```
Checks if the given command is a built-in command (e.g., exit, pid, ppid, help, cd) and executes it.

```
void sigint_handler(int sig)
```
Signal handler for SIGINT (Ctrl+C) that changes the default action to do nothing when SIGINT is signaled.

```
int parseline(char *buf, char **argv)
```
Parses the command line and builds the argument vector (argv). Handles background job execution and returns whether the job should run in the background or foreground.

## Csapp
The files 'csapp.h' and 'csapp.c' were initiated based on the code provided by the textbook "Computer Systems: A Programmer's Perspective, 3/E (CS:APP3e)" authored by Randal E. Bryant and David R. O'Hallaron from Carnegie Mellon University. The original source code can be found at the following website: http://csapp.cs.cmu.edu/3e/code.html. The use and adaptation of this code adhere to the guidelines and permissions provided by the textbook's accompanying materials.

## Credits
Developed by Sofanyas Genene on April 28th, 2023.

## Acknowledgments

This program is developed with gratitude to the authors of "Computer Systems: A Programmer's Perspective, 3/E (CS:APP3e)," Randal E. Bryant and David R. O'Hallaron from Carnegie Mellon University. The starter code provided by the authors, available at http://csapp.cs.cmu.edu/3e/code.html, served as a valuable foundation for this project. Their insightful materials and resources significantly contributed to the development of this software.
