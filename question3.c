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
	int pid;
	int status;
	
	while(1)
{
		
		/* Reading user command */
		/* The STIN_FILENO preprocessor is defined with the value of stdout, which is 0.*/
		/* One can read up to 1024 characters*/
		int r = read(STDIN_FILENO,command, 1024); 						
		
		/* Handling shell output */
		
		/* Case where the user presses Ctrl+D*/
		/* This case is the only one where no characters are read*/
		/* We exit the shell using the exit() function, taking EXIT_SUCCESS as an argument to indicate if the program has terminated successfully*/
		if (r == 0) 
		{ 
			write(STDOUT_FILENO,"\n"out,sizeof(out)+1);
			exit(EXIT_SUCCESS);
		}
	
		r = read(STDIN_FILENO,command,1024); //reading of the command entered. We can't read more than 1024 characters
		char *cmd=malloc(r*sizeof(char));//Allocates the memory to store the command 
		cmd=strncpy(cmd,command,r-1);
		
		/* In the case the user enter "exit"*/
		/*The last character that the user will enter is "Enter"*/
		command[r-1]='\0';//Replacement of "Enter" touch with the NULL character
		
			if(strncmp("exit",command,4)==0)//Replacement of the previous character with the chain "exit". If they are equal the strncmp return 0
			{
				write(STDOUT_FILENO,out,sizeof(out));
				exit(EXIT_SUCCESS);
			}
		
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
