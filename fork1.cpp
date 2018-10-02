#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
	int a = 0;
	int b = 1;
	int n = a + b;
	int val = atoi(argv[1]);

	printf("You entered a sequence of %d\n", val);	
	pid_t pid;
	//fork another process 
	pid = fork();
	
	if( pid < 0)
	//error occurred 
	{
  	   fprintf(stderr, "Fork Failed\n");
	   exit(-1);
	}

	else if(pid == 0)
        {
           //child process 
	   printf("Child executing Fibonacci Sequence: \n");
	   for(int i =0; i < val; i++)
	   {
		n = a+b;
		printf("%d ", n);
		a = b;
		b = n;
	   }
	}
	
	else
	{
	   // parent process 
	   // parent will wait for the child to complete 
	   wait(NULL);
	   printf("Child Complete\n");
	   exit(0);
	}
}
