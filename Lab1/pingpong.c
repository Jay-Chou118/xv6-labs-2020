#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"  

int main(int argc, char **argv){
    
    int pp2c[2], pc2p[2];
    pipe(pp2c);
    pipe(pc2p);

    if (fork() != 0){
        write(pp2c[1], "man", 3);
        char buf[3];
        read(pc2p[0], &buf, 3);
        // printf("%d: received pong, data: %.*s\n", getpid(), n, buf);  // 5. 子进程收到数据，read 返回，输出 pong
        printf("%d: received ping\n", getpid());
		    wait(0);
    }else { // child process
		char buf[3];
		read(pp2c[0], &buf, 3); // 3. 子进程读取管道，收到父进程发送的字节数据
		// printf("%d: received ping, data: %.*s\n", getpid(), n, buf);  // 输出数据
    printf("%d: received pong\n", getpid());
		write(pc2p[1], &buf, 3); // 4. 子进程通过 子->父 管道，将字节送回父进程
	}
	exit(0);
}