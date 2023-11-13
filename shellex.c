/* $begin shellmain */
#include "csapp.h"
#define MAXARGS   128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv); 

void sigint_handler(int sig){   // declares SIGINT handler
	// changes default action to do nothing when SIGINT is signaled 
}

int main(int argc, char** argv) 
{
	char cmdline[MAXLINE]; /* Command line */

	// calls upon sigint_handler() if CTRL +c is an argument
	if (signal(SIGINT, sigint_handler) == SIG_ERR)   {
		unix_error("signal error");
	}

	while (1) {
		/* Read */
		if (argc == 3 && !strcmp(argv[1], "-p")){
			printf("%s> ", argv[2]);
		}else{
			printf("sh257> ");
		}                   
		Fgets(cmdline, MAXLINE, stdin); 
		if (feof(stdin))
			exit(0);

		/* Evaluate */
		eval(cmdline);
	} 
}
/* $end shellmain */

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) 
{
	char *argv[MAXARGS]; /* Argument list execvp() */
	char buf[MAXLINE];   /* Holds modified command line */
	int bg;              /* Should the job run in bg or fg? */
	pid_t pid;           /* Process id */

	strcpy(buf, cmdline);
	bg = parseline(buf, argv); 
	if (argv[0] == NULL)  
		return;   /* Ignore empty lines */

	if (!builtin_command(argv)) { 
		if ((pid = Fork()) == 0) {   /* Child runs user job */
			if (execvp(argv[0], argv) < 0) {
				printf("Execution failed (in fork)\n");
				printf("%s: Command not found.\n", argv[0]);
				exit(1);
			}
		} else{

			/* Parent waits for foreground job to terminate */
			if (!bg) {
				int status;
				if (waitpid(pid, &status, 0) < 0)
					unix_error("waitfg: waitpid error");
				printf("Process exited with status code %d\n", WEXITSTATUS(status));
			}
			else{
				printf("%d %s", pid, cmdline);
			}
		}
	}
	return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
	if (!strcmp(argv[0], "exit")) /* exit command */
		raise(SIGTERM);  
	if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
		return 1;

	// prints pid of shell
	if (!strcmp(argv[0], "pid")) {
		printf("pid: %d\n", getpid());
		return 1;
	}

	// prints ppid of shell
	if (!strcmp(argv[0], "ppid")) {
		printf("ppid: %d\n", getppid());
		return 1;
	}

	// help command 
	if (!strcmp(argv[0], "help")) {
		printf("\n\n**********************************************************************\n");
		printf("Developed by Sofanyas Genene.\n\n"); 
		printf("-p <prompt> at execution time will allow a user defined prompt.\n");
		printf("**********************************************************************\n\n");
		printf("BUILTIN COMMANDS:\n\n");
		printf("exit:       Exits the shell.\n");
		printf("pid:        Prints the process id of the shell.\n");
		printf("ppid:       Prints the parent process id of the shell.\n");
		printf("help:       Prints avalible commands in the shell.\n");
		printf("cd:         Prints current working directory.\n");
		printf("cd <path>:  Changes current working directory to path.\n\n");
		printf("SYSTEM COMMANDS:\n\n");
		printf("For all other commands, please refer to the man pages!\n");
		printf("**********************************************************************\n\n\n");
		return 1;
	}

	// cd command that changes current directory or prints it.
	if (!strcmp(argv[0], "cd")) {
		if (argv[1] == NULL) { // checks if path argument is given

			char cwd[MAXLINE];

			// gets current working directory and stores it in cwd
			// checks for error
			if(getcwd(cwd, MAXLINE) != NULL){
				printf("%s\n", cwd);
				return 1;

			}else{

				printf("Error retrieving current working directory.\n");
				return 1;
			}
		} else { 

			// executes when path argument is given
			// checks for error
			if (chdir(argv[1]) != 0){

				// executes if error when changing working directory
				printf("Error changing current working directory.\n");

			}
			return 1;
		}
	}
	return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
	char *delim;         /* Points to first space delimiter */
	int argc;            /* Number of args */
	int bg;              /* Background job? */

	buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
	while (*buf && (*buf == ' ')) /* Ignore leading spaces */
		buf++;

	/* Build the argv list */
	argc = 0;
	while ((delim = strchr(buf, ' '))) {
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' ')) /* Ignore spaces */
			buf++;
	}
	argv[argc] = NULL;

	if (argc == 0)  /* Ignore blank line */
		return 1;

	/* Should the job run in the background? */
	if ((bg = (*argv[argc-1] == '&')) != 0)
		argv[--argc] = NULL;

	return bg;
}
/* $end parseline */
