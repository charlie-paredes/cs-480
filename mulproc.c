#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

      //ints for process Id
      int pid1, pid2;
      int child_status;

      //first child process (testalphabet)
      pid1 = fork();
      if(pid1 <0){
         perror("fork failed");
         exit(1);
      } else if(pid1 == 0){
         //Child process 1
         printf("CHILD <PID: %d> process is executing testalphabet program!\n", getpid());
         execlp("./testalphabet", "./testalphabet", NULL);  // Run testalphabet
         perror("execlp failed");
         exit(1);
      }

      //second child process (testspecial)
       pid2 = fork();
      if (pid2 < 0) {
         perror("fork failed");
         exit(1);
      } else if (pid2 == 0) {
         // Child process 2
         printf("CHILD <PID: %d> process is executing testspecial program!\n", getpid());
         execlp("./testspecial", "./testspecial", NULL);  // Run testspecial
         perror("execlp failed");
         exit(1);
      }
		
      //wait for child processes to finish
      //had to run the testspecial program first to get the correct output
      //since it runs quicker than the testalphabet program
		int status;
      waitpid(pid2, &child_status, 0);
      printf("CHILD <PID: %d> process has done with testspecial program! See the results above!\n", pid2);
      waitpid(pid1, &child_status, 0);
      printf("CHILD <PID: %d> process has done with testalphabet program! See the results above!\n", pid1);
      
       

      return 0;
		
	
	return 0;
	
}
