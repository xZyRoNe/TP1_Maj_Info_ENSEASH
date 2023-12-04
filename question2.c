#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h> 


/* Definition of the character strings used in the code. */

#define chain "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\nenseash % " 
#define out "Bye bye...\n"
#define prompt "ensea %\n"

/**/

int main(void)
{
	
	char command[1024]="";
	
	write(STDOUT_FILENO,chain,sizeof(chain)); //Display the welcome message
	
	int r;
	int pid;
	int status;
	
	while(1)
	{
		r = read(STDIN_FILENO,command,1024); //reading of the command entered. We can't read more than 1024 characters
		char *cmd=malloc(r*sizeof(char));//Allocates the memory to store the command 
		cmd=strncpy(cmd,command,r-1);
		
		pid=fork(); // creation of a child process similal to the father but with a specific ID
	     
		if (pid ==0) //child process
		{ 	
            write(STDOUT_FILENO, command, sizeof(command));
			execlp(cmd,cmd, NULL); // execlp replaces the current process with a new one specified by the given command
		} 											
		else // Parent process
		{
				wait(&status); // Wait for the child process to finish
		}
			
	}
}
