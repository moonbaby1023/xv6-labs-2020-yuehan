#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int a2i(const char *s)
{
    int n;

    n = 0;
    while (1)
    {
        if ('0'<=*s && *s<='9')
            n = n*10 + *s++ - '0';
        else if (*s==0)
            return n;
        else
        {
            return -1;// ==-1 means error happend. >=0 means normally working
        }
    }

}

int main(int argc, char *argv[])
{
    if (argc==2)
    {
        char *c;
        c = argv[1];
        int n = 0;
        n = a2i(c);

        if (n>0)
            sleep(n);
        else
            printf("error: you must input a number\nthe process has exited\n");   
    }
    else if (argc<2)
        printf("error: lacking time parameter\nthe process has exited\n");
    else
        printf("error: too many parameters\nthe process has exited\n");

exit(0);
}