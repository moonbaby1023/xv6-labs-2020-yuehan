#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define sizeofPrime 4
void new_pipe_proc(int *leftPipe){// // what should the current process do
    close(leftPipe[1]);
    
    int prime, n=1;
    read(leftPipe[0], &prime, sizeofPrime);
    printf("prime %d\n", prime);

    int flagread;
    flagread = read(leftPipe[0], &n, sizeofPrime);
    if (flagread==0) 
        exit(0);// no more neighbor process is needed, if the left neighbor passes only one number to the current process 
    else if (flagread<0){
        printf("error: read n from the leftpipe\n");
        exit(1);
    }
    else{       
        int rightPipe[2];// create new pipe on the right
        pipe(rightPipe);

        int pid;// create a new child neighbor on the right
        pid = fork();

        if (pid==0){ // what should a new child process do
            new_pipe_proc(rightPipe);
        }
        else if (pid>0){ // what should the current process do after fork
            close(rightPipe[0]);
            do{
                if (n%prime != 0)
                write(rightPipe[1], &n, sizeofPrime);// write into the right pipe
            }while(read(leftPipe[0], &n, sizeofPrime));// read from the left pipe
            close(rightPipe[1]);
            wait((int *)0); // when the left pipe[writeEnd] is closed
            exit(0);
        }
        else{
            printf("error: fork() failed at some child process\n");
            exit(1);
        }
  
    }

}

int main(){
   
    int p[2];
    pipe(p);
    int pid;
    pid = fork();
    if (pid==0){
        new_pipe_proc(p);
        exit(0);
    }
    else if (pid>0){// what the leftmost process should do: 
        close(p[0]);
        for(int i=2; i<36; i++){
            write(p[1], &i, sizeofPrime);           
        }
        close(p[1]);

        wait((int *)0); //Either make your child process wait for its children and don't exit until they've all been waited for or fork all the children from the same process.
        exit(0);
    }
    else{
        printf("error: fork() failed at main process\n");
        exit(1);
    }
    
    printf("haha\n");
    
}