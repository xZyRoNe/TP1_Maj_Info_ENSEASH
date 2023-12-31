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
	
	
	/*Display of the welcome message*/
	write(STDOUT_FILENO,chain,sizeof(chain)); 
	write(STDOUT_FILENO,prompt,sizeof(prompt));
	
	
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
		pid_t process_id;
	    process_id = getpid();
	    
		if (pid ==0) //child process
		{ 	printf("pid child %d\n", getpid());
			sleep(20);
            write(STDOUT_FILENO, command, sizeof(command));
			execlp(cmd,cmd, NULL);
			printf("%d", process_id); // execlp replaces the current process with a new one specified by the given command
		} 											
			else // Parent process
			{
				wait(&status); // Wait for the child process to finish
			}
			
		/* Display of the previous command return code */
		/* Exit case */
		if (WIFEXITED(status)){
		char exit_message[100];
                sprintf(exit_message, "enseash [exit:%d]\n ", WEXITSTATUS(status));
                write(STDOUT_FILENO, exit_message, strlen(exit_message));
			}
			
		/* Signal case*/
		else{
		char exit_message[100];
                sprintf(exit_message, "enseash [sign:%d] \n ", WTERMSIG(status));
                write(STDOUT_FILENO, exit_message, strlen(exit_message));
			}
			free(cmd);
		}
		
}


