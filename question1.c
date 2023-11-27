#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h> 


/* Definition of used character list*/

#define chain "Bienvenue dans le Shell ENSEA.\nPour quitter, taper 'exit'.\nenseash % "
#define prompt "ensea %\n"

int main(void){
	/*Display of the welcome message*/
	write(STDOUT_FILENO,chain,sizeof(chain)); 
	write(STDOUT_FILENO,prompt,sizeof(prompt));
	}
