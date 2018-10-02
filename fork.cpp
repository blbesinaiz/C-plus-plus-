#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main()
{
	pid_t pid;
	/*fork another process */
	pid = fork();
	
	if( pid < 0)
	/*error occurred */
	{
           fprintf(stderr, "Fork Failed\n");
	   exit(-1);
	}

	else if(pid == 0)
        {
           /*child process */
	  // execl("/bin/ls", "ls\n", NULL);
	     execl("/bin/grep","grep", "fork", "fork.cpp", NULL);
	}

	else
	{
	   /* parent process */
	   /* parent will wait for the child to complete */
	   wait(NULL);
	   printf("Child Complete\n");
	   exit(0);
	}
}
/*****Results****************************
Child Complete
*/
