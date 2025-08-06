#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void primes(int p[2]){
   int n;
   read(p[0], &n, sizeof(n));
   if(n == -1){
       close(p[0]);
       return;
   }
   printf("prime %d\n", n);
   
   int p2[2];
   pipe(p2);
   int pid = fork();
   if(pid != 0){
    int buf;
    while(read(p[0], &buf, sizeof(buf)) > 0){
        if(buf == -1){
            // 将结束标记传递给下一个进程
            write(p2[1], &buf, sizeof(buf));
            break;
        }
        if(buf % n != 0){
            write(p2[1], &buf, sizeof(buf));
        }
    }
    buf = -1;
    write(p2[1], &buf, sizeof(buf));
    // close(p[1]);
    // close(p2[0]);
    // close(p2[1]);  // 关闭写入端
    wait(0);
    exit(0);

   } else {
    close(p2[1]);  // 关闭写入端
    close(p[0]);
    primes(p2);
   }
}



int main(int argc,char** argv){
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid != 0) {
        close(p[0]);
        for(int i = 2;i <= 35; ++i){
            write(p[1], &i, sizeof(i));
        }
        int i = -1;
        write(p[1],&i,sizeof(i));
    }else{
        close(p[1]);
        primes(p);
        exit(0);
    }
    wait(0);
    exit(0);
}