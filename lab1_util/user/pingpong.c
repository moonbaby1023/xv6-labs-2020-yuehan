#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h" // for fork(), pipe(), etc...

int main(int argc, char* argv[])
{
    int p_p2c[2], p_c2p[2]; // file descripters: p0 for input pipe; p1 for the output pipe
    pipe(p_p2c);
    pipe(p_c2p);

    int pid;
    pid = fork();

    if (pid == 0)// child: receive, print ping
    {
        char cbuf;// child's read buffer
        int flagr;
        flagr = read(p_p2c[0], &cbuf, 1);
        if (flagr==1)
            printf("%d: received ping\n", getpid());
        else
        {
            printf("error: ping read\n");
            exit(1);
        }

        int flagw;
        flagw = write(p_c2p[1], "2", 1);
        close(p_c2p[1]);
        if (flagw != 1)
        {
            printf("error: ping write\n");
            exit(1);
        }
    }
    else if(pid > 0) // parent: send, receive, print pong
    {
        int flagw;
        flagw = write(p_p2c[1], "1", 1);
        close(p_p2c[1]);
        if (flagw != 1)
        {
            printf("error: ping write\n");
            exit(1);
        }

        char pbuf;// parent's read buffer
        int flagr;
        flagr = read(p_c2p[0], &pbuf, 1);
        if (flagr==1)
            printf("%d: received pong\n", getpid());
        else
        {
            printf("error: pong read\n");
            exit(1);
        }
    }
    else
    {
        printf("fork error\n");
        exit(1); // void exit(int status), int wait(int* status);
    }
        
   
    
    exit(0);
}