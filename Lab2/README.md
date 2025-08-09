添加系统调用的时候，需要在内核态中处理这些调用。


第二个sysinfo实验的时候
重点函数载于：
```
c
// kernel/sysproc.c
//文件开头加上sysinfo结构体的头文件
#include"sysinfo.h"

// 收集系统信息
uint64
sys_sysinfo(void){
  struct sysinfo info;
  kama freebytes(&info.freemem);//获取空闲内存
  kama procnum(&info.nproc);//获取进程数量
//获取用户虚拟地址uint64 dstaddr;argaddr(0,&dstaddr);
//从内核空间拷贝数据到用户空间
  if (copyout(myproc()->pagetable, dstaddr,(char*)&info, sizeof info)< 0)
    return -1;
  return 0;
}
```
