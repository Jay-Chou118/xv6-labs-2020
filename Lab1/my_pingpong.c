#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char* argv[]){
    int p[2];
    char buf[16];

    pipe(p);

    int pid = fork();
    if(pid != 0){
        printf("Parent\n");
        // close(p[0]);
        write(p[1], "hello", sizeof("hello")-1);
        // close(p[1]);
        wait(0);
        read(p[0],buf,5);
        printf("Parent read %s \n",buf);
        // close(p[0]);
    } else {
        printf("Child\n");
        // close(p[1]);
        read(p[0],buf,5);
        printf("Child read %s \n",buf);
        // close(p[0]);
        write(p[1], "world", 5);
        // close(p[1]);
    }
    exit(0);
}