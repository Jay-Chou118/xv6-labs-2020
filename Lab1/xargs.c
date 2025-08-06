#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define MSGSIZE 16

// echo hello too | xargs echo bye
int main(int argc,char *argv[]){
    //Q1 怎么获取前一个命令的标准化输出（即此命令的标准化输入）
    char buf[MSGSIZE];
    read(0,buf,MSGSIZE);
    //buf = ['h','e','l','l','o',' ','t','o','o','\n']
    // printf("buf : %s\n",buf);
    //Q2 如何获取到自己的命令汗参数
    char *xargv[MAXARG];
    int xargc = 0;
    for(int i =1;i < argc;i++) {
        xargv[xargc++] = argv[i];
    }
    //xargv = ['echo','bye',0]
    char *p = buf;
    for(int i = 0;i < MSGSIZE;i++){
        if(buf[i] == '\n'){
            int pid =fork();//fork之后的子进程会和父进程独立，所以此时的指针p还是指向buf的开头
            if(pid > 0){
                p = &buf[i + 1];
                wait(0);
            }else{
                //Q3 如何使用exec去执行命令
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                xargc++;
                //exec 会实现一个拼接的作用，xargv[0] = echo    
                exec(xargv[0],xargv);
                exit(0);
            }
        }
    }
    wait(0);
    exit(0);
}