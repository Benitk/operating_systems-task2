#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

static int fd[2];
void SigHandler(int sig) ;
void child() ;
void parent(pid_t child_pid) ;

int main() {
   pid_t pid;

   if(pipe(fd) == -1){
        perror("pipe failed");
        exit(1);
    }

    signal(SIGUSR1, SigHandler);
    pid = fork();

   switch(pid){
      case -1 : perror("fork failed") ;
                exit(1) ;
      case 0  : child() ;
                exit(0) ;
      default: parent(pid) ;
                exit(0) ;
   }

   //close pipe
    close(fd[0]);
    close(fd[1]);
    return 0 ; 
}  
   
void child() {
   int i;
   printf("sleep 5 sec to prevent deadlock\n");

   
   sleep(5);  //gives parent time get to pause

    int number = 0; // child sent write first to pipe
    write(fd[1], &number, sizeof(number));

   for (i=0; i < 3; i++) {
      kill(getppid(), SIGUSR1) ;
      pause() ;       // until a signal
   }
    sleep(1);
    printf("child terminating\n");
}

void parent(pid_t child_pid) {
   int i;

   printf("pid of parent = %d, pid of child = %d\n", getpid(), child_pid) ;
   for (i=0; i < 3; i++) {
      pause();                     // until u get a signal
      kill(child_pid, SIGUSR1) ;
   }
   int status;
   wait(&status);
   printf("parent terminating\n");
}

void SigHandler(int sig) {
    signal(SIGUSR1, SigHandler) ;
    int number;
    read(fd[0], &number, sizeof(number));
    printf("num = %d\n", number);
    sleep(1);
    number++;
    write(fd[1], &number, sizeof(number));
}

