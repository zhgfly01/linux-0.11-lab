/*
 *  linux/lib/write.c
 *
 *  (C) 1991  Linus Torvalds
 */

#define __LIBRARY__
#include <unistd.h>

#if 0

_syscall3(int,write,int,fd,const char *,buf,off_t,count)

#else
int write(int fd,const char * buf,off_t count)
{
    long __res; 
    __asm__ volatile ("int $0x80" 
    	: "=a" (__res) 
    	: "0" (__NR_write),"b" ((long)(fd)),"c" ((long)(buf)),"d" ((long)(count))); 
    if (__res>=0) 
    	return (int) __res; 
    errno=-__res; 
    return -1; 
}
#endif


